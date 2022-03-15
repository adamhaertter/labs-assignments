# CSC111 Computer Science II
# Lab 11: makefile
# Programmers: Scott Bucher & Adam Haertter 
# Professor: Dr. Lee
# Date Created: Nov 8, 2019
# Date Updated: Nov 8, 2019

#You press the tab key when you see [TAB] in the following makefile
SOURCES = xor.c                   #defines the sources
OBJECTS = xor.o                 #defines the objects

CC = gcc
CFLAGS = -g -Wall

Lab11: $(OBJECTS)                           #defines Lab11 build
	$(CC) $(CFLAGS) $(OBJECTS) -o xor
clean:                                         #defines clean build
	rm -fR *xor
