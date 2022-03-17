# MIPS Assembler

<img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-plain.svg" height="50">


## Program Description: 

>This project was originally intended to be part 2 of a 3-project sequence, but stage 3 was never assigned due to time constraints and COVID-19. 

This project is a follow-up to the `mips-to-hex` project. That program converted MIPS instructions to hexadecimal, and this is built off of the foundation of that one.

This C program supports the same instruction set as the previous one, but instead of converting them to hexadecimal, this encodes them as a binary file. 
MIPS instructions are entered through `stdin` again, but instead of printing to stdout, they will be encoded in a binary file which is to be specified to the executable. 
The binary file will remain in the folder if no errors are encountered while entering instructions. 
Otherwise, the file will be deleted.


<br>

## Co-Authors

- Trevor Grohowski
- Makaylie Lucas


<br>

## How to Compile:

The Makefile will compile the project into an executable called ``project2`` by just typing:

```bash
make 
```

<br>

## How to Run:

The first and only argument to this program should be the file to output the binary file in. If no such file exists, it will be created. Running the executable can be done through the command line:

```
./project2 data.dat
```
<br>
As before, enter a MIPS instruction. 
Registers should be separated by a comma, although whitespace and capitalization does not matter. 
Instead of printing hex, the program will convert the instruction to binary data and write it to the target file.

Type `ctrl + d` to end the standard input sequence (indicated by ^D below).

```mips
add $t0, $t1, $t2
jr $ra
and $t0, $t5, $t6
addi $t2, $0, 42
^D
```

If errors are encountered, they will be printed back to stdout.
At the end, the number of errors in the sequence will be tallied up and printed.
To prevent a poorly-assembled or error-ridden file, the binary file specified will be deleted at the end of the standard input sequence if any errors are encountered.

```mips
add $t0, $t1, $t2
sub $t5, $t6, $t6
bad 42
ERROR - INVALID INSTRUCTION
bad 2
ERROR - INVALID INSTRUCTION
add 23
ERROR - INVALID FORMAT
add $t0, $t1, $t2
There were 3 errors.
```

<br>

## Known Bugs:

Being provided no arguments is not handled gracefully and instead results in a Segmentation Fault. 
