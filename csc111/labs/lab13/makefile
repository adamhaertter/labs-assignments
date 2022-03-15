#CSC111 Computer Science II
#Lab 13: makefile
#Programmers: Adam Haertter
#Professor: Dr. Lee
#File Created: November 13th, 2019
#File Updated: November 13th, 2019

SOURCES = fcopy.c 
OBJECTS = fcopy.o
CC = gcc
CFLAGS = -g -Wall

fcopy: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o fcopy
clean:
	rm -fR *o fcopy
