#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Structures
/********************************/
/********************************/
// encoded number structure types
typedef enum {
    PARSE_RTYPE, PARSE_ITYPE, PARSE_JTYPE, PARSE_JRTYPE, MEMTYPE, SHIFT_TYPE, LOAD_TYPE
} instr_type_t;

// 3 Types of encoded instruction types
typedef enum {
    FMT_RTYPE, FMT_ITYPE, FMT_JTYPE
} encode_type_t;

// instruction structure
typedef struct {
    char *mnemonic;
    instr_type_t type;
    encode_type_t etype;
    int opcode;
    int function;
} instr_t;

// Parser put in own C file after we know it is working
// parsed structure
typedef struct {
    bool is_valid;
    instr_t instr;
    char *opcode;			// The mnemonic
	char *data; 			// The second half of the instruction text
    char *rs;
	char *rt;
	char *rd;
    char *immediate;
    char *address;
    char *shamt;
    char *funct;
} parsed_t;

typedef struct {
	char *name;
	char *num;
	int index;
} regs_t;


/****************************Array for separate file*********************************/
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
  {.mnemonic = "LI", 	.type = LOAD_TYPE, 		.etype = FMT_ITYPE, .opcode = 0x09,	.function = 0},
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

/************************************************************************************/

//Called after format is invalid
void print_format_error(parsed_t *result) {
  printf("ERROR - INVALID FORMAT\n");
  //printf(" %s %s\n", result->opcode, result->data);
  result->is_valid = false;
}

//Called after format is invalid
void print_register_error(parsed_t *result) {
  printf("ERROR - INVALID REGISTER\n");
  //printf(" %s %s\n", result->opcode, result->data);
  result->is_valid = false;
}

/******************Finished**********************************************************/
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
/*********************************************/
void parse_string(const char *str, parsed_t *result)
{
    int i = 0;
    int state = 0;
    int start = 0;
	char *name;
	char *rest;
		

    while ((str[i] != 0)) {
        //printf("STR: Case %d str[i] = %c\n", state, str[i]);
        switch(state) {
            case 0: // In Whitespace
				if (str[i] == ' ' || str[i] == '\t') state = 0;
				else if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) { //not sure if capital
					state = 1; // The instruction mnemonic has started
					start = i;
				}
					else state = -1; // Impromper Mnemonic, throw error
					break;
				// beginning of instruction
            case 1: // In Mnemonic
				if ((str[i] >= 'A') || !(str[i] <= 'Z')) { } //not sure if capital 
				else if(str[i] == ' ' || str[i] == '\t') {
					state = 2;
					name = malloc(i - start + 1);
					strncpy(name, &str[start], (i - start));
					start = i+1;
				} else
					state = -1;
				break;
			case 2: //Splitting off the rest of the instruction
				if (str[i] == ' ' || str[i] == '\t') { state = 2; start = i+1; }
				else { 
					rest = malloc(strlen(str) - i);
					strncpy(rest, &str[start], (strlen(str) - start));
					i = strlen(str) - 1;
				}
					//else state = -1; // Impromper Mnemonic, throw error
				break;
			default: 
				print_format_error(result);
				return;
		}
		i++;
    }
	
	//turn instruction into full caps
	for(int i = 0; i < strlen(name); i++) {
	    char caps = toupper(name[i]);
	    name[i] = caps;
	}
	
	//turn data into full lowercase
	for(i = 0; i < strlen(rest); i++) {
	    char lower = tolower(rest[i]);
	    rest[i] = lower;
	}
	
	result->opcode = name;
	result->data = rest;
	
	//free(rest);
	//free(name);
}




// "$rd, $rs, $rt  "
// This works for sure, tested on its own.
void parse_r_standard(char *str, parsed_t *result){
	char *rs = (char *)malloc(6*sizeof(char));
	char *rt = (char *)malloc(6*sizeof(char));
	char *rd = (char *)malloc(6*sizeof(char));
	int i = 0;
    int state = 0;
    int start = 0;
	//char str[] = "$zero, $at, $9"; //Test String
	
	// while-switch loop
	while ((str[i] != 0)) {
		//printf("Case %d, str[i] = %c\n", state, str[i]);
        switch(state) {
            case 0:
				//go until you hit a ,
				if(str[i] == ',') {
					state = 1; //Move to next section
					strncpy(rd, &str[start], i);
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error invalid reg
				break;
			case 1:
				//go through whitespace
				if (str[i] == ' ' || str[i] == '\t') state = 1; 
				else if (str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { 
					state = 2;
					start = i;
				} else state = -1; // Impromper Mnemonic, throw error
				break;
			case 2:
				//get second register, go until you hit next ,
				if(str[i] == ',') {
					state = 3; //Move to next section
					strncpy(rs, &str[start], (i - start));
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error invalid reg
				break;
			case 3:
				//go through next whitespace
				if (str[i] == ' ' || str[i] == '\t') state = 3; 
				else if (str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { 
					state = 4;
					start = i;
				} else state = -1; // Impromper Mnemonic, throw error
				break;
			case 4:
				//get third register, go until you hit whitespace or string end
				if(str[i+1] == ' ' || str[i+1] == '\t' || str[i+1] == '\0' || str[i+1] == '\n') {
					strncpy(rt, &str[start], (i + 1 - start));
					i = strlen(str) - 1;
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error invalid reg
				break;
			default:
			    print_format_error(result);
			    return;
		}
		i++;
    }
    
    if(strcmp(rs, "") == 0 || strcmp(rt, "") == 0 || strcmp(rd, "") == 0) {
        print_format_error(result);
    }
    
	result->rs = rs;
	result->rt = rt;
	result->rd = rd;
	
	//free(rs); free(rt); free(rd);
}

// "$rt, $rs, imm  "
// Works! Tested; works for single digit
void parse_i_standard(char *str, parsed_t *result){
	char *rs = (char *)malloc(6*sizeof(char));
	char *rt = (char *)malloc(6*sizeof(char));
	char *imm = (char *)malloc(6*sizeof(char));
	int i = 0;
    int state = 0;
    int start = 0;
	//char str[] = "$zero,                               $at, 999"; //Test String
	
	// while-switch loop
	while ((str[i] != 0)) {
		//printf("Case %d, str[i] = %c\n", state, str[i]);
        switch(state) {
			case 0:
				//go until you hit a ,
				if(str[i] == ',') {
					state = 1; //Move to next section
					strncpy(rt, &str[start], i);
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error invalid reg
				break;
			case 1:
				//go through whitespace
				if (str[i] == ' ' || str[i] == '\t') state = 1; 
				else if (str[i] == '$') { 
					state = 2;
					start = i;
				} else state = -1; // Impromper Mnemonic, throw error
				break;
			case 2:
				//get second register, go until you hit next ,
				if(str[i] == ',') {
					state = 3; //Move to next section
					strncpy(rs, &str[start], (i - start));
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error invalid reg
				break;
			case 3:
				//go through next whitespace
				if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-') { 
					state = 4;
					start = i;
				} else if (str[i] == ' ' || str[i] == '\t') state = 3;
				else state = -1; // Impromper Mnemonic, throw error
				break;
			case 4:
				//get immediate, go until you hit whitespace or string end
				if(str[i+1] == ' ' || str[i+1] == '\t' || str[i+1] == '\0' || str[i+1] == '\n') {
					state = -2;
					strncpy(imm, &str[start], (i + 1 - start));
				} else if((str[i] >= '0' && str[i] <= '9') || str[i] == '-') { }
				else state = -1; //Throw error invalid reg
				break;
			case -1:
			    print_format_error(result);
			    return;
		}
		i++;
    }
    
    if(strcmp(rs, "") == 0 || strcmp(rt, "") == 0 || strcmp(imm, "") == 0) {
        print_format_error(result);
    }
    
	result->rs = rs;
	result->rt = rt;
	result->immediate = imm;
	
	//free(rs); free(rt); free(imm);
}

// "addr"
// Works! Tested
void parse_j_standard(char *str, parsed_t *result){
	char *addr = (char *)malloc(10*sizeof(char));
	int i = 0;
	//char str[] = "0x12345678"; //Test String
	
	// while-switch loop
	while ((str[i] != 0)) {
		//get address, go until you hit whitespace or string end
		if(str[i+1] == ' ' || str[i+1] == '\t' || str[i+1] == '\0') {
			strncpy(addr, str, i+1);
			break;
		} else if((str[i] >= '0' && str[i] <= '9') || str[i] == 'x' || (str[i] >= 'a' || str[i] <='f')) { }
		else {
		    print_format_error(result);
			    return;
		}
		i++;
    }
    
    if(strcmp(addr, "") == 0) {
        print_format_error(result);
    }
	
	result->address = addr;
	//free(addr);
}

// "$rs  "
// Works! Tested
void parse_r_jump(char *str, parsed_t *result){
	char *rs = (char *)malloc(6*sizeof(char));
	int i = 0;
	//char str[] = "$at"; //Test String
	
	// while-switch loop
	while ((str[i] != 0)) {
		//go until you hit a ,
		if(str[i+1] == ' ' || str[i+1] == '\t' || str[i+1] == '\0' || str[i+1] == '\n') {
			strncpy(rs, str, i);
		} else if((str[i+1] >= 'A' && str[i+1] <= 'Z') || (str[i+1] >= 'a' && str[i+1] <= 'z') || (str[i+1] >= '0' && str[i+1] <= '9')) { }
		else {
		    print_format_error(result);
			    return;
		}
		i++;
    }
	
    if(strcmp(rs, "") == 0) {
        print_format_error(result);
    }
	
	result->rs = rs;
	result->rd = "$0";
	result->rt = "$0";
	
	//free(rs);
}

// "$rt, imm ($rs)  "
// Works! Tested; works with single digit in both cases
void parse_memtype(char *str, parsed_t *result){
	char *rs = (char *)malloc(6*sizeof(char));
	char *rt = (char *)malloc(6*sizeof(char));
	char *imm = (char *)malloc(6*sizeof(char));
	int i = 0;
    int state = 0;
    int start = 0;
	//char str[] = "$zero, 4($ra)"; //Test String
	
	// while-switch loop
	while ((str[i] != 0)) {
        switch(state) {
            case 0:
				//go until you hit a ,
				if(str[i] == ',') {
					state = 1; //Move to next section
					strncpy(rt, &str[start], i);
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error invalid reg
				break;
			case 1:
				//go through whitespace
				if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-') { 
					state = 2;
					start = i;
				} else if (str[i] == ' ' || str[i] == '\t') state = 1; 
				else state = -1; // Impromper Mnemonic, throw error
				break;
			case 2:
				//get immediate, go until you hit whitespace or string end
				if(str[i] == ' ' || str[i] == '\t') {
					state = 3;
					strncpy(imm, &str[start], (i - start));
				}
				else if(str[i] == '(') {
					state = 4;
					strncpy(imm, &str[start], (i - start));
					start = i;
				} else if((str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error invalid reg
				break;
			case 3:
				//go through whitespace, if needed
				if ((str[i] == '(')) { 
					state = 4;
					start = i;
				} else if (str[i] == ' ' || str[i] == '\t') state = 3; 
				else state = -1; // Impromper Mnemonic, throw error
				break;
			case 4:
				//get second register, go until you hit next )
				if(str[i] == ')') {
					strncpy(rs, &str[start+1], (i - start - 1));
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else if(str[i] == ' ' || str[i] == '\t') { }
				else state = -1;  //Throw error invalid reg
				break;
			case -1:
			    print_format_error(result);
			    return;
		}
		i++;
    }
	
	
    if(strcmp(rs, "") == 0 || strcmp(rt, "") == 0 || strcmp(imm, "") == 0) {
        print_format_error(result);
    }
	
	result->rs = rs;
	result->rt = rt;
	result->immediate = imm;
	
	//free(rs); free(rt); free(imm);
}

// "$rd, $rt, shamt  "
// Works! Tested; works for single digit
void parse_shift(char *str, parsed_t *result){
	char *rd = (char *)malloc(6*sizeof(char));
	char *rt = (char *)malloc(6*sizeof(char));
	char *shift = (char *)malloc(6*sizeof(char));
	int i = 0;
    int state = 0;
    int start = 0;
	//char str[] = "$zero,                               $at, 2"; //Test String
	
	// while-switch loop
	while ((str[i] != 0)) {
        switch(state) {
            case 0:
				//go until you hit a ,
				if(str[i] == ',') {
					state = 1; //Move to next section
					strncpy(rd, &str[start], i);
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error invalid reg
				break;
			case 1:
				//go through whitespace
				if (str[i] == ' ' || str[i] == '\t') state = 1; 
				else if (str[i] == '$') { 
					state = 2;
					start = i;
				} else state = -1; // Impromper Mnemonic, throw error
				break;
			case 2:
				//get second register, go until you hit next ,
				if(str[i] == ',') {
					state = 3; //Move to next section
					strncpy(rt, &str[start], (i - start));
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error invalid reg
				break;
			case 3:
				//go through next whitespace
				if (str[i+1] >= '0' && str[i+1] <= '9') { 
					state = 4;
					start = i;
				} else if (str[i] == ' ' || str[i] == '\t') state = 3; 
				else state = -1; // Impromper Mnemonic, throw error
				break;
			case 4:
				//get immediate, go until you hit whitespace or string end
				if(str[i+1] == ' ' || str[i+1] == '\t' || str[i+1] == '\0' || str[i+1] == '\n') {
					state = -2;
					strncpy(shift, &str[start], (i + 1 - start));
				} else if((str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error invalid reg
				break;
			case -1:
			    print_format_error(result);
			    return;
		}
		i++;
    }
    
    if(strcmp(shift, "") == 0 || strcmp(rt, "") == 0 || strcmp(rd, "") == 0) {
        print_format_error(result);
    }
	
	result->rd = rd;
	result->rt = rt;
	result->shamt = shift;
	result->rs = "$0";
	
	//free(rd); free(rt); free(shift);
}

// "$rt, $rs, imm  "
// Works! Tested; works for single digit
void parse_i_load(char *str, parsed_t *result){
	char *rt = (char *)malloc(6*sizeof(char));
	char *imm = (char *)malloc(6*sizeof(char));
	int i = 0;
    int state = 0;
    int start = 0;
	//char str[] = "$zero,                               $at, 999"; //Test String
	
	// while-switch loop
	while ((str[i] != 0)) {
        switch(state) {
			case 0:
				//get first register, go until you hit next ,
				if(str[i] == ',') {
					state = 1; //Move to next section
					strncpy(rt, &str[start], (i - start));
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error invalid reg
				break;
			case 1:
				//go through next whitespace
				if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-') { 
					state = 2;
					start = i;
				} else if (str[i] == ' ' || str[i] == '\t') state = 1;
				else state = -1; // Impromper Mnemonic, throw error
				break;
			case 2:
				//get immediate, go until you hit whitespace or string end
				if(str[i+1] == ' ' || str[i+1] == '\t' || str[i+1] == '\0' || str[i+1] == '\n') {
					state = -2;
					strncpy(imm, &str[start], (i + 1 - start));
				} else if((str[i] >= '0' && str[i] <= '9') || str[i] == '-') { }
				else state = -1; //Throw error invalid reg
				break;
			case -1:
			    print_format_error(result);
			    return;
		}
		i++;
    }
	
    if(strcmp(rt, "") == 0 || strcmp(imm, "") == 0) {
        print_format_error(result);
    }
	
	result->rs = "$0";
	result->rt = rt;
	result->immediate = imm;
	
	//free(rs); free(rt); free(imm);
}

//PARSE_RTYPE, PARSE_ITYPE, PARSE_JTYPE, PARSE_JRTYPE, MEMTYPE, SHIFT_TYPE
void parse_data(parsed_t *instruction){
	
	instr_type_t decode_method = instruction->instr.type;
	char *str = instruction->data;
	
	switch(decode_method){
		case PARSE_RTYPE:
			parse_r_standard(str, instruction);
			break;
		case PARSE_ITYPE:
			parse_i_standard(str, instruction);
		    break;
		case PARSE_JTYPE:
			parse_j_standard(str, instruction);
		    break;
		case PARSE_JRTYPE:
			parse_r_jump(str, instruction);
		    break;
		case MEMTYPE:
			parse_memtype(str, instruction);
		    break;
		case SHIFT_TYPE:
			parse_shift(str, instruction);
		    break;
		case LOAD_TYPE:
			parse_i_load(str, instruction);
		    break;
	}
}




int main(void)
{
	char input[100];
	//printf("Enter a MIPS instruction:\n");
	
	while(!feof(stdin)) {
	fgets(input, 100, stdin);
	
	if(feof(stdin)){
		return 0;
	}
	
	parsed_t instruction;
	instruction.is_valid = true;
	parse_string(input, &instruction); 	//separate
	
	if(instruction.is_valid == false) {
	    return 0;
	}
	
	// Mnemonic / opcode to digits for function and opcodes
	int n = sizeof(instrs)/sizeof(instrs[0]);
	
	for(int i=0; i < n; i++) {
	    if(strcmp(instruction.opcode, instrs[i].mnemonic) == 0){
	        instruction.instr = instrs[i];
	        instruction.is_valid = true;
	        break;
	    } else {
	        instruction.is_valid = false;
	    }
	}
	
	// Is the instruction valid?
	if(instruction.is_valid == false) {
	    printf("ERROR - INVALID INSTRUCTION\n");
	    continue;
	}
	
	parse_data(&instruction);			//parse second half
	
	if(instruction.is_valid == false) {
	    continue;
	}
	
	unsigned finalized = 0;

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
	}
	
	
	if(instruction.is_valid == true) {
	    printf("%08x\n", finalized);
	}
	}
	return 0;
}