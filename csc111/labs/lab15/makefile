# CSC111 Computer Science II
# Lab 15 Quicksort: makefile
# Programmers: Scott Bucher, Adam Haertter
# Professor: Dr. Lee
# Date Created: Nov 18, 2019
# Date Updated: Nov 18, 2019

#You press the tab key when you see [TAB] in the following makefile
SOURCES = qsort.c                 #defines the sources
OBJECTS = qsort.o                 #defines the objects

CC = gcc
CFLAGS = -g -Wall

Lab15: $(OBJECTS)                              #defines Lab15 build
	$(CC) $(CFLAGS) $(OBJECTS) -o qsort
clean:                                         #defines clean build
	rm -fR *o qsort
