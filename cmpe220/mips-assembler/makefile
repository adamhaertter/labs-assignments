# CMPE220 Computer Organization
# Project 2 MIPS Instruction to Hexadecimal Converter - makefile
# Programmers: Adam Haertter, Trevor Grohowski, Makaylie Lucas
# Professor: Dr. Briggs

SOURCES = project1.c parse.c lookup.c format.c    #defines the sources
OBJECTS = project1.o parse.o lookup.o format.o    #defines the objects

CC = gcc
CFLAGS = -g -Wall

Project2: $(OBJECTS)                              #defines Project2 build
	$(CC) $(CFLAGS) $(OBJECTS) -o project2
clean:                                            #defines clean build
	rm -fR *o project2
