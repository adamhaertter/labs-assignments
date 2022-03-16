/* CMPE220 Computer Organization
 * Project 1 MIPS Instruction to Hexadecimal Converter - parse.c
 * Programmers: Adam Haertter, Trevor Grohowski, Makaylie Lucas
 * Professor: Dr. Briggs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "project1.h"

void parse_string(const char *str, parsed_t *result)
{
    int i = 0;
    int state = 0;
    int start = 0;
	char *name;
	char *rest;
		

    while ((str[i] != 0)) {
        switch(state) {
            case 0: // In Whitespace
				if (str[i] == ' ' || str[i] == '\t') state = 0;
				else if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) { 
					state = 1; // The instruction mnemonic has started
					start = i;
				}
					else state = -1; //Throw error
					break;
				// beginning of instruction
            case 1: // In Mnemonic
				if ((str[i] >= 'A') || !(str[i] <= 'Z')) { }  
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
				break;
			default: 
				print_format_error(result);
				return;
		}
		i++;
    }
	
	// Turn instruction into full caps
	for(int i = 0; i < strlen(name); i++) {
	    char caps = toupper(name[i]);
	    name[i] = caps;
	}
	
	// Turn data into full lowercase
	for(i = 0; i < strlen(rest); i++) {
	    char lower = tolower(rest[i]);
	    rest[i] = lower;
	}
	
	result->opcode = name;
	result->data = rest;
}

// "$rd, $rs, $rt  "
void parse_r_standard(char *str, parsed_t *result){
	char *rs = (char *)malloc(6*sizeof(char));
	char *rt = (char *)malloc(6*sizeof(char));
	char *rd = (char *)malloc(6*sizeof(char));
	int i = 0;
    int state = 0;
    int start = 0;
	
	while ((str[i] != 0)) {
        switch(state) {
            case 0:
				//go until you hit a ,
				if(str[i] == ',') {
					state = 1; //Move to next section
					strncpy(rd, &str[start], i);
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error
				break;
			case 1:
				//go through whitespace
				if (str[i] == ' ' || str[i] == '\t') state = 1; 
				else if (str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { 
					state = 2;
					start = i;
				} else state = -1; //Throw error
				break;
			case 2:
				//get second register, go until you hit next ,
				if(str[i] == ',') {
					state = 3; //Move to next section
					strncpy(rs, &str[start], (i - start));
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error
				break;
			case 3:
				//go through next whitespace
				if (str[i] == ' ' || str[i] == '\t') state = 3; 
				else if (str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { 
					state = 4;
					start = i;
				} else state = -1; // Throw error
				break;
			case 4:
				//get third register, go until you hit whitespace or string end
				if(str[i+1] == ' ' || str[i+1] == '\t' || str[i+1] == '\0' || str[i+1] == '\n') {
					strncpy(rt, &str[start], (i + 1 - start));
					i = strlen(str) - 1;
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error
				break;
			default:
			    print_format_error(result);
			    return;
		}
		i++;
    }
	
    // Check for any registers that are left unfilled
	// ex. "ADD $t0" would leave the other registers unfilled, meaning it has an invalid format
    if(strcmp(rs, "") == 0 || strcmp(rt, "") == 0 || strcmp(rd, "") == 0) {
        print_format_error(result);
    }
    
	result->rs = rs;
	result->rt = rt;
	result->rd = rd;
}

// "$rt, $rs, imm  "
void parse_i_standard(char *str, parsed_t *result){
	char *rs = (char *)malloc(6*sizeof(char));
	char *rt = (char *)malloc(6*sizeof(char));
	char *imm = (char *)malloc(6*sizeof(char));
	int i = 0;
    int state = 0;
    int start = 0;
	
	while ((str[i] != 0)) {
        switch(state) {
			case 0:
				//go until you hit a ,
				if(str[i] == ',') {
					state = 1; //Move to next section
					strncpy(rt, &str[start], i);
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error
				break;
			case 1:
				//go through whitespace
				if (str[i] == ' ' || str[i] == '\t') state = 1; 
				else if (str[i] == '$') { 
					state = 2;
					start = i;
				} else state = -1; // Throw error
				break;
			case 2:
				//get second register, go until you hit next ,
				if(str[i] == ',') {
					state = 3; //Move to next section
					strncpy(rs, &str[start], (i - start));
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error
				break;
			case 3:
				//go through next whitespace
				if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-') { 
					state = 4;
					start = i;
				} else if (str[i] == ' ' || str[i] == '\t') state = 3;
				else state = -1; // Throw error
				break;
			case 4:
				//get immediate, go until you hit whitespace or string end
				if(str[i+1] == ' ' || str[i+1] == '\t' || str[i+1] == '\0' || str[i+1] == '\n') {
					state = -2;
					strncpy(imm, &str[start], (i + 1 - start));
				} else if((str[i] >= '0' && str[i] <= '9') || str[i] == '-') { }
				else state = -1; //Throw error
				break;
			case -1:
			    print_format_error(result);
			    return;
		}
		i++;
    }
    
	// Check for any registers that are left unfilled
	if(strcmp(rs, "") == 0 || strcmp(rt, "") == 0 || strcmp(imm, "") == 0) {
        print_format_error(result);
    }
    
	result->rs = rs;
	result->rt = rt;
	result->immediate = imm;
}

// "addr"
void parse_j_standard(char *str, parsed_t *result){
	char *addr = (char *)malloc(10*sizeof(char));
	int i = 0;
	
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
    
	// Check for empty address
	if(strcmp(addr, "") == 0) {
        print_format_error(result);
    }
	
	result->address = addr;
}

// "$rs  "
void parse_r_jump(char *str, parsed_t *result){
	char *rs = (char *)malloc(6*sizeof(char));
	int i = 0;
	
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
	
	// Check for any registers that are left unfilled
	if(strcmp(rs, "") == 0) {
        print_format_error(result);
    }
	
	result->rs = rs;
	result->rd = "$0";
	result->rt = "$0";
}

// "$rt, imm ($rs)  "
void parse_memtype(char *str, parsed_t *result){
	char *rs = (char *)malloc(6*sizeof(char));
	char *rt = (char *)malloc(6*sizeof(char));
	char *imm = (char *)malloc(6*sizeof(char));
	int i = 0;
    int state = 0;
    int start = 0;
	
	// while-switch loop
	while ((str[i] != 0)) {
        switch(state) {
            case 0:
				//go until you hit a ,
				if(str[i] == ',') {
					state = 1; //Move to next section
					strncpy(rt, &str[start], i);
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error
				break;
			case 1:
				//go through whitespace
				if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-') { 
					state = 2;
					start = i;
				} else if (str[i] == ' ' || str[i] == '\t') state = 1; 
				else state = -1; // Throw error
				break;
			case 2:
				//get immediate, go until you hit whitespace
				if(str[i] == ' ' || str[i] == '\t') {
					state = 3;
					strncpy(imm, &str[start], (i - start));
				}
				else if(str[i] == '(') {
					state = 4;
					strncpy(imm, &str[start], (i - start));
					start = i;
				} else if((str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error
				break;
			case 3:
				//go through whitespace, if needed
				if ((str[i] == '(')) { 
					state = 4;
					start = i;
				} else if (str[i] == ' ' || str[i] == '\t') state = 3; 
				else state = -1; // Throw error
				break;
			case 4:
				//get second register, go until you hit next )
				if(str[i] == ')') {
					strncpy(rs, &str[start+1], (i - start - 1));
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else if(str[i] == ' ' || str[i] == '\t') { }
				else state = -1;  //Throw error
				break;
			case -1:
			    print_format_error(result);
			    return;
		}
		i++;
    }
	
	
    // Check for any registers that are left unfilled
	if(strcmp(rs, "") == 0 || strcmp(rt, "") == 0 || strcmp(imm, "") == 0) {
        print_format_error(result);
    }
	
	result->rs = rs;
	result->rt = rt;
	result->immediate = imm;
}

// "$rd, $rt, shamt  "
void parse_shift(char *str, parsed_t *result){
	char *rd = (char *)malloc(6*sizeof(char));
	char *rt = (char *)malloc(6*sizeof(char));
	char *shift = (char *)malloc(6*sizeof(char));
	int i = 0;
    int state = 0;
    int start = 0;
	
	while ((str[i] != 0)) {
        switch(state) {
            case 0:
				//go until you hit a ,
				if(str[i] == ',') {
					state = 1; //Move to next section
					strncpy(rd, &str[start], i);
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error
				break;
			case 1:
				//go through whitespace
				if (str[i] == ' ' || str[i] == '\t') state = 1; 
				else if (str[i] == '$') { 
					state = 2;
					start = i;
				} else state = -1; // Throw error
				break;
			case 2:
				//get second register, go until you hit next ,
				if(str[i] == ',') {
					state = 3; //Move to next section
					strncpy(rt, &str[start], (i - start));
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error
				break;
			case 3:
				//go through next whitespace
				if (str[i+1] >= '0' && str[i+1] <= '9') { 
					state = 4;
					start = i;
				} else if (str[i] == ' ' || str[i] == '\t') state = 3; 
				else state = -1; // Throw error
				break;
			case 4:
				//get immediate, go until you hit whitespace or string end
				if(str[i+1] == ' ' || str[i+1] == '\t' || str[i+1] == '\0' || str[i+1] == '\n') {
					state = -2;
					strncpy(shift, &str[start], (i + 1 - start));
				} else if((str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error
				break;
			case -1:
			    print_format_error(result);
			    return;
		}
		i++;
    }
    
    // Check for any registers that are left unfilled
	if(strcmp(shift, "") == 0 || strcmp(rt, "") == 0 || strcmp(rd, "") == 0) {
        print_format_error(result);
    }
	
	result->rd = rd;
	result->rt = rt;
	result->shamt = shift;
	result->rs = "$0";
}

// "$rt, imm  "
void parse_i_load(char *str, parsed_t *result){
	char *rt = (char *)malloc(6*sizeof(char));
	char *imm = (char *)malloc(6*sizeof(char));
	int i = 0;
    int state = 0;
    int start = 0;
	
	while ((str[i] != 0)) {
        switch(state) {
			case 0:
				//get first register, go until you hit next ,
				if(str[i] == ',') {
					state = 1; //Move to next section
					strncpy(rt, &str[start], (i - start));
				} else if(str[i] == '$' || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) { }
				else state = -1; //Throw error
				break;
			case 1:
				//go through next whitespace
				if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-') { 
					state = 2;
					start = i;
				} else if (str[i] == ' ' || str[i] == '\t') state = 1;
				else state = -1; // Throw error
				break;
			case 2:
				//get immediate, go until you hit whitespace or string end
				if(str[i+1] == ' ' || str[i+1] == '\t' || str[i+1] == '\0' || str[i+1] == '\n') {
					state = -2;
					strncpy(imm, &str[start], (i + 1 - start));
				} else if((str[i] >= '0' && str[i] <= '9') || str[i] == '-') { }
				else state = -1; //Throw error
				break;
			case -1:
			    print_format_error(result);
			    return;
		}
		i++;
    }
	
    // Check for any registers that are left unfilled
	if(strcmp(rt, "") == 0 || strcmp(imm, "") == 0) {
        print_format_error(result);
    }
	
	result->rs = "$0";
	result->rt = rt;
	result->immediate = imm;
}

// Decides which parser method to use based on the parse type of each instruction
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