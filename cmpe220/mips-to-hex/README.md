# MIPS Instruction to Hexadecimal Converter

<img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-plain.svg" height="50">


## Program Description: 

This C program converts any basic MIPS Assembly instruction into its corresponding hexadecimal encoding.
Instructions are inputted through `stdin`, and the hex value will be printed to `stdout`.
All instructions from the <a href="https://inst.eecs.berkeley.edu/~cs61c/resources/MIPS_Green_Sheet.pdf"> MIPS core instruction set </a> are supported.
For the full list of supported instructions, see the table in lookup.c

Additionally, the pseudoinstruction LUI (Load Upper Immediate) is also specially supported, despite not being a core instruction.


<br>

## Co-Authors

- Trevor Grohowski
- Makaylie Lucas


<br>

## How to Compile:

The Makefile will compile the project into an executable called ``project1`` by just typing:

```bash
make 
```

<br>

## How to Run:

No arguments are necessary to run this program. Running the executable can be done through the command line:

```
./project1
```
<br>
Next, enter a MIPS instruction. Registers should be separated by a comma, although whitespace and capitalization does not matter. Some examples of specific formats are shown below:

```mips
R-type example:
add $t0, $t1, $t2

I-type example:
beq $t0, $t1, 5  

J-type examples:
j 0
jr $ra

Memory example:
lw $t0, 5 ($t1) 

Shifting example:
sll $t0, $t1, 5

LUI and ORI:
lui $t0, 5
```

<br>

## Known Bugs:

N/A
