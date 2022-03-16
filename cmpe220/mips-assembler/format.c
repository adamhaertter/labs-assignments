/* CMPE220 Computer Organization
 * Project 1 MIPS Instruction to Hexadecimal Converter - format.c
 * Programmers: Adam Haertter, Trevor Grohowski, Makaylie Lucas
 * Professor: Dr. Briggs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "project1.h"

unsigned format_rtype(parsed_t *parsed)
{
    int code = parsed->instr.opcode;
    int rd = register_read(parsed->rd);
    int rs = register_read(parsed->rs);
    int rt = register_read(parsed->rt);
    int shamt = strtol(parsed->shamt, NULL, 0);
    int func = parsed->instr.function;
    
    if (rs == -1 || rd == -1 || rt == -1) {
        print_register_error(parsed);
    }

    return code << 26 | rs << 21 | rt << 16 | rd << 11 | shamt << 6 | func;
}

unsigned format_itype(parsed_t *parsed)
{
    int code = parsed->instr.opcode;
    int rt = register_read(parsed->rt);
    int rs = register_read(parsed->rs);
    int immediate = strtol(parsed->immediate, NULL, 0); 

    //If the immediate is negative, this will remove the first 4 bytes
    if(immediate < 0)
        immediate = immediate^0xFFFF0000;

    if (rs == -1 || rt == -1) {
        print_register_error(parsed);
    }
    
    return code << 26 | rs << 21 | rt << 16 | immediate;
}


unsigned format_jtype(parsed_t *parsed)
{
    int code = parsed->instr.opcode;
    int address = strtol(parsed->address, NULL, 0); 

    return code << 26 | address;

}

// In the case of an LI pseudoinstruction, this function returns the LUI output and writes the ORI output to an input *ori
unsigned format_li(parsed_t *parsed, unsigned *ori)
{
	int immediate = strtol(parsed->immediate, NULL, 0); 
	if(immediate <= 0xFFFF)
		return format_itype(parsed);
	//LI is set up in the table to account for ADDI implementation by default
	
	//ORI
	parsed->opcode = "ORI";		//Load "ORI" into the parsed
	instruction_read(parsed);
	parsed->rs = "$1";			//Loads $at into rs, like in MARS
	sprintf(parsed->immediate, "%d", immediate^0xFFFF0000);
	
	*ori = format_itype(parsed);
	
	//LUI
	immediate = immediate>>16;	// The first 4 bytes are sent to the LUI

	int code = 0x0f; // opcode of LUI
    int rt = 1; // RT is set to $at, like in MARS
	parsed->opcode = "LI";		//Load "LI" back into the parsed
	instruction_read(parsed);
	
    return code << 26 | rt << 16 | immediate;
}