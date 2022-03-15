# CSC111 Computer Science II
# Lab 16 Binary Tree: makefile
# Programmers: Scott Bucher, Adam Haertter
# Professor: Dr. Lee
# Date Created: Nov 25, 2019
# Date Updated: Nov 25, 2019

#You press the tab key when you see [TAB] in the following makefile
SOURCES = airmiles.c                 #defines the sources
OBJECTS = airmiles.o                 #defines the objects

CC = gcc
CFLAGS = -g -Wall

Lab16: $(OBJECTS)                              #defines Lab16 build
	$(CC) $(CFLAGS) $(OBJECTS) -o airmiles
clean:                                         #defines clean build
	rm -fR *o airmiles
