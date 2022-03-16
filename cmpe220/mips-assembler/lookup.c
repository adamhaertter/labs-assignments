/* CMPE220 Computer Organization
 * Project 1 MIPS Instruction to Hexadecimal Converter - lookup.c
 * Programmers: Adam Haertter, Trevor Grohowski, Makaylie Lucas
 * Professor: Dr. Briggs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "project1.h"

instr_t instrs[] = {
  {.mnemonic = "ADD", 	.type = PARSE_RTYPE, 	.etype = FMT_RTYPE, .opcode = 0, 	.function = 0x20},
  {.mnemonic = "ADDI", 	.type = PARSE_ITYPE, 	.etype = FMT_ITYPE, .opcode = 0x08, .function = 0},
  {.mnemonic = "ADDIU", .type = PARSE_ITYPE, 	.etype = FMT_ITYPE, .opcode = 0x09, .function = 0},
  {.mnemonic = "ADDU",	.type = PARSE_RTYPE, 	.etype = FMT_RTYPE, .opcode = 0, 	.function = 0x21},
  {.mnemonic = "AND", 	.type = PARSE_RTYPE, 	.etype = FMT_RTYPE, .opcode = 0, 	.function = 0x24},
  {.mnemonic = "ANDI",	.type = PARSE_ITYPE, 	.etype = FMT_ITYPE, .opcode = 0x0c, .function = 0},
  {.mnemonic = "BEQ", 	.type = PARSE_ITYPE, 	.etype = FMT_ITYPE, .opcode = 0x04, .function = 0},
  {.mnemonic = "BNE", 	.type = PARSE_ITYPE, 	.etype = FMT_ITYPE, .opcode = 0x05, .function = 0},
  {.mnemonic = "J", 	.type = PARSE_JTYPE, 	.etype = FMT_JTYPE, .opcode = 0x02, .function = 0},
  {.mnemonic = "JAL", 	.type = PARSE_JTYPE, 	.etype = FMT_JTYPE, .opcode = 0x03, .function = 0},
  {.mnemonic = "JR", 	.type = PARSE_JRTYPE, 	.etype = FMT_RTYPE, .opcode = 0, 	.function = 0x08},
  {.mnemonic = "LBU", 	.type = MEMTYPE, 		.etype = FMT_ITYPE, .opcode = 0x24, .function = 0},
  {.mnemonic = "LHU", 	.type = MEMTYPE, 		.etype = FMT_ITYPE, .opcode = 0x25, .function = 0},
  {.mnemonic = "LI", 	.type = LOAD_TYPE, 		.etype = FMT_LI,	.opcode = 0x09,	.function = 0},
  {.mnemonic = "LL", 	.type = MEMTYPE, 		.etype = FMT_ITYPE, .opcode = 0x30, .function = 0},
  {.mnemonic = "LUI", 	.type = LOAD_TYPE, 		.etype = FMT_ITYPE, .opcode = 0x0f, .function = 0},
  {.mnemonic = "LW", 	.type = MEMTYPE, 		.etype = FMT_ITYPE, .opcode = 0x23,	.function = 0},
  {.mnemonic = "NOR", 	.type = PARSE_RTYPE, 	.etype = FMT_RTYPE, .opcode = 0, 	.function = 0x27},
  {.mnemonic = "OR", 	.type = PARSE_RTYPE, 	.etype = FMT_RTYPE, .opcode = 0, 	.function = 0x25},
  {.mnemonic = "ORI", 	.type = PARSE_ITYPE, 	.etype = FMT_ITYPE, .opcode = 0x0d, .function = 0},
  {.mnemonic = "SLT", 	.type = PARSE_RTYPE, 	.etype = FMT_RTYPE, .opcode = 0, 	.function = 0x2a},
  {.mnemonic = "SLTI", 	.type = PARSE_ITYPE, 	.etype = FMT_ITYPE, .opcode = 0x0a, .function = 0},
  {.mnemonic = "SLTIU", .type = PARSE_ITYPE, 	.etype = FMT_ITYPE, .opcode = 0x0b, .function = 0},
  {.mnemonic = "SLTU", 	.type = PARSE_RTYPE,	.etype = FMT_RTYPE, .opcode = 0, 	.function = 0x2b},
  {.mnemonic = "SLL", 	.type = SHIFT_TYPE, 	.etype = FMT_RTYPE, .opcode = 0, 	.function = 0x00},
  {.mnemonic = "SRL", 	.type = SHIFT_TYPE, 	.etype = FMT_RTYPE, .opcode = 0, 	.function = 0x02},
  {.mnemonic = "SB", 	.type = MEMTYPE, 		.etype = FMT_ITYPE, .opcode = 0x28, .function = 0},
  {.mnemonic = "SC", 	.type = MEMTYPE, 		.etype = FMT_ITYPE, .opcode = 0x38, .function = 0},
  {.mnemonic = "SH", 	.type = MEMTYPE, 		.etype = FMT_ITYPE, .opcode = 0x29, .function = 0},
  {.mnemonic = "SW", 	.type = MEMTYPE, 		.etype = FMT_ITYPE, .opcode = 0x2b, .function = 0},
  {.mnemonic = "SUB", 	.type = PARSE_RTYPE, 	.etype = FMT_RTYPE, .opcode = 0, 	.function = 0x22},
  {.mnemonic = "SUBU", 	.type = PARSE_RTYPE, 	.etype = FMT_RTYPE, .opcode = 0,	.function = 0x23}
};

regs_t regs[] = {
	{.name = "$zero",	.num = "$0",	.index = 0},	
	{.name = "$at",		.num = "$1",	.index = 1},	
	{.name = "$v0",		.num = "$2",	.index = 2},	
	{.name = "$v1",		.num = "$3",	.index = 3},	
	{.name = "$a0",		.num = "$4",	.index = 4},	
	{.name = "$a1",		.num = "$5",	.index = 5},	
	{.name = "$a2",		.num = "$6",	.index = 6},	
	{.name = "$a3",		.num = "$7",	.index = 7},	
	{.name = "$t0",		.num = "$8",	.index = 8},	
	{.name = "$t1",		.num = "$9",	.index = 9},	
	{.name = "$t2",		.num = "$10",	.index = 10},	
	{.name = "$t3",		.num = "$11",	.index = 11},	
	{.name = "$t4",		.num = "$12",	.index = 12},	
	{.name = "$t5",		.num = "$13",	.index = 13},	
	{.name = "$t6",		.num = "$14",	.index = 14},	
	{.name = "$t7",		.num = "$15",	.index = 15},	
	{.name = "$s0",		.num = "$16",	.index = 16},	
	{.name = "$s1",		.num = "$17",	.index = 17},	
	{.name = "$s2",		.num = "$18",	.index = 18},	
	{.name = "$s3",		.num = "$19",	.index = 19},	
	{.name = "$s4",		.num = "$20",	.index = 20},	
	{.name = "$s5",		.num = "$21",	.index = 21},	
	{.name = "$s6",		.num = "$22",	.index = 22},	
	{.name = "$s7",		.num = "$23",	.index = 23},	
	{.name = "$t8",		.num = "$24",	.index = 24},	
	{.name = "$t9",		.num = "$25",	.index = 25},	
	{.name = "$k0",		.num = "$26",	.index = 26},	
	{.name = "$k1",		.num = "$27",	.index = 27},	
	{.name = "$gp",		.num = "$28",	.index = 28},	
	{.name = "$sp",		.num = "$29",	.index = 29},	
	{.name = "$fp",		.num = "$30",	.index = 30},	
	{.name = "$ra",		.num = "$31",	.index = 31}
};

// Use loop and struct to get registers value 
int register_read(char *str) {
    int n = sizeof(regs)/sizeof(regs[0]);
	
	for(int i=0; i < n; i++) {
	    if(strcmp(str, regs[i].name) == 0 || strcmp(str, regs[i].num) == 0){
	        return regs[i].index;
	    }
	}
	return -1;
}

void instruction_read(parsed_t *instruction) {
	// Mnemonic / opcode to digits for function and opcodes
	int n = sizeof(instrs)/sizeof(instrs[0]);
	
	for(int i=0; i < n; i++) {
	    if(strcmp(instruction->opcode, instrs[i].mnemonic) == 0){
	        instruction->instr = instrs[i];
	        instruction->is_valid = true;
	        break;
	    } else {
	        instruction->is_valid = false;
	    }
	}
}