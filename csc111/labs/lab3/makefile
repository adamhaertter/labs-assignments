# CSC111 Computer Science II
# Lab 3 Modular Programming - makefile
# Programmers: Adam Haertter and Yong Hang Lin
# Professor: Dr. Lee
# File Created: Sep 30, 2019
# File Updated: Sep 30, 2019

SOURCES = lab3.c lab3a.c lab3b.c		#Defines source files
OBJECTS = lab3.o lab3a.o lab3b.o
HEADERS = lab3.h				#Includes header file lab3.h
CC = gcc
CFLAGS = -g -Wall				#Flags all Warnings

Lab3: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o lab3
clean:
	rm -fR *o lab3
