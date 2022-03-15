# CSC111 Computer Science II
# Project 1: Stack & Queue ADT Juggler -  makefile
# Programmers: Adam Haertter
# Professor: Dr. Lee

#You press the tab key when you see [TAB] in the following makefile
SOURCES = sqjuggler.c queue.c stack.c          #defines the sources
OBJECTS = sqjuggler.o queue.o stack.o          #defines the objects

CC = gcc
CFLAGS = -g -Wall

SQJuggler: $(OBJECTS)                          #defines sqjuggler build
	$(CC) $(CFLAGS) $(OBJECTS) -o sqjuggler
clean:                                         #defines clean build
	rm -fR *o sqjuggler
