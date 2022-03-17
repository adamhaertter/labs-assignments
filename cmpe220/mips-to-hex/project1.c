/* CMPE220 Computer Organization
 * Project 1 MIPS Instruction to Hexadecimal Converter - project1.c
 * Programmers: Adam Haertter, Trevor Grohowski, Makaylie Lucas
 * Professor: Dr. Briggs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "project1.h"

int main(void)
{
	char input[100];
	
	while(!feof(stdin)) {
		fgets(input, 100, stdin);
	
		// Is the input over?
		if(feof(stdin)){
			return 0;
		}
	
		parsed_t instruction;
		instruction.shamt = "";				// Prevent code from segfaulting on r-type input first
		instruction.is_valid = true;
		parse_string(input, &instruction); 	// Separates the mnemonic from the data
	
		if(instruction.is_valid == false) {
			return 0;
		}
	
		instruction_read(&instruction);
	
		// Is the instruction valid?
		if(instruction.is_valid == false) {
			printf("ERROR - INVALID INSTRUCTION\n");
			continue;
		}
	
		parse_data(&instruction);			// Parses second half into values
	
		if(instruction.is_valid == false) {
			// Error printing handled in parse_data
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
			printf("%08x\n", finalized);
			if(instruction.instr.etype == FMT_LI && ori != 0) {
				printf("%08x\n", ori);	// LUI will be printed by above print, and this will print ORI
			}
		}
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