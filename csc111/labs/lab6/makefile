# CSC111 Computer Science II
# Lab 6: makefile
# Programmers: Scott Bucher & Adam Haertter
# Professor: Dr. Lee
# Date Created: Oct 5, 2019
# Date Updated: Oct 5, 2019

#You press the tab key when you see [TAB] in the following makefile
SOURCES = runner.c charlist.c                  #defines the sources
OBJECTS = runner.o charlist.o                  #defines the objects
HEADERS = charlist.h                           #defines the headers
CC = gcc
CFLAGS = -g -Wall

Charplay: $(OBJECTS)                           #defines Charplay build
	$(CC) $(CFLAGS) $(OBJECTS) -o charplay
clean:                                         #defines clean build
	rm -fR *o charplay
