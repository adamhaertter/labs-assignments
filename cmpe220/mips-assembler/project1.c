/* CMPE220 Computer Organization
 * Project 2 MIPS Instruction to Hexadecimal Converter - project1.c
 * Programmers: Adam Haertter, Trevor Grohowski, Makaylie Lucas
 * Professor: Dr. Briggs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "project1.h"

int main(int argc, char** argv)
{
	char input[100];
	int num_instructions = 0;
	int num_errors = 0;
	
	FILE *fp = fopen(argv[1], "w+"); // write in binary
    int magic = 0x1b162d00;
    int zero =  0x00000000;
    fwrite(&magic, 1, sizeof(magic), fp); //the magic number
	fwrite(&zero, 1, sizeof(zero), fp);
	
    
    while(!feof(stdin)) {
		fgets(input, 100, stdin);
	
		// Is the input over?
		if(feof(stdin)){
			break; //Go to end of main
		}
	
		parsed_t instruction;
		instruction.shamt = "";				// Prevent code from segfaulting on r-type input first
		instruction.is_valid = true;
		parse_string(input, &instruction); 	// Separates the mnemonic from the data
	
		if(instruction.is_valid == false) {
            num_errors++;
            return 0;
		}
	
		instruction_read(&instruction);
		// Is the instruction valid?
		if(instruction.is_valid == false) {
			printf("ERROR - INVALID INSTRUCTION\n");
            num_errors++;
			continue;
        }

	
		parse_data(&instruction);			// Parses second half into values
	
		if(instruction.is_valid == false) {
			// Error printing handled in parse_data
            num_errors++;
			continue;
        } 
	
		unsigned finalized = 0;
		unsigned ori = 0;		//This will only be used in the case of an LI

		// Format the data back into an unsigned integer
		switch(instruction.instr.etype) {
			case FMT_RTYPE:
				finalized = format_rtype(&instruction);
				break;
			case FMT_ITYPE:
				finalized = format_itype(&instruction);
				break;
			case FMT_JTYPE:
				finalized = format_jtype(&instruction);
				break;
			case FMT_LI:
				finalized = format_li(&instruction, &ori);
				break;
		}
		
		// If the instruction is still valid, print it
		if(instruction.is_valid == true) {
			//printf("%08x\n", finalized);
			fwrite(&finalized, 1, sizeof(finalized), fp);
			if(instruction.instr.etype == FMT_LI && ori != 0) {
				//printf("%08x\n", ori);	// LUI will be printed by above print, and this will print ORI
				fwrite(&ori, 1, sizeof(ori), fp);
				num_instructions++;
			}
			num_instructions++;
        }
        else {            
            num_errors++;
        }
	}
		
	if(num_errors > 0) {
		//Get rid of output file when errors are present
		fclose(fp);
		remove(argv[1]);
		printf("There were %d errors.\n", num_errors);
	} else {
		//With no errors, write instruction count to output file and close
		fseek(fp, 4, SEEK_SET);
        fwrite(&num_instructions, 1, sizeof(num_instructions), fp);
	    fclose(fp); 
	}
	
	return 0;
}

// Called after the format is invalid
void print_format_error(parsed_t *result) {
  printf("ERROR - INVALID FORMAT\n");
  result->is_valid = false;
}

// Called after register is invalid
void print_register_error(parsed_t *result) {
  printf("ERROR - INVALID REGISTER\n");
  result->is_valid = false;
}

