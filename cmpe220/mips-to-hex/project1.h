/* CMPE220 Computer Organization
 * Project 1 MIPS Instruction to Hexadecimal Converter - project1.h
 * Programmers: Adam Haertter, Trevor Grohowski, Makaylie Lucas
 * Professor: Dr. Briggs
 */

// Types of parse format types
typedef enum {
    PARSE_RTYPE, PARSE_ITYPE, PARSE_JTYPE, PARSE_JRTYPE, MEMTYPE, SHIFT_TYPE, LOAD_TYPE
} instr_type_t;

// 3 Types of encoded instruction types and 1 special case for LI
typedef enum {
    FMT_RTYPE, FMT_ITYPE, FMT_JTYPE, FMT_LI
} encode_type_t;

// Structure for an Instruction itself
typedef struct {
    char *mnemonic;
    instr_type_t type;
    encode_type_t etype;
    int opcode;
    int function;
} instr_t;

// Structure for the individual Registers
typedef struct {
	char *name;
	char *num;
	int index;
} regs_t;

// Structure for the data breakdown
typedef struct {
    bool is_valid;
    instr_t instr;			// The corresponding instruction
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

// Prototypes by file
int register_read(char *str);
void instruction_read(parsed_t *instruction);

void print_format_error(parsed_t * result);
void print_register_error(parsed_t *result);

unsigned format_rtype(parsed_t *parsed);
unsigned format_itype(parsed_t *parsed);
unsigned format_jtype(parsed_t *parsed);
unsigned format_li(parsed_t *parsed, unsigned *ori);

void parse_string(const char *str, parsed_t *result);
void parse_r_standard(char *str, parsed_t *result);
void parse_i_standard(char *str, parsed_t *result);
void parse_j_standard(char *str, parsed_t *result);
void parse_r_jump(char *str, parsed_t *result);
void parse_memtype(char *str, parsed_t *result);
void parse_shift(char *str, parsed_t *result);
void parse_i_load(char *str, parsed_t *result);
void parse_data(parsed_t *instruction);