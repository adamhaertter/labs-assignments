/* CSC111 Computer Science 2
   Lab 10 - Stack: stackADT2.c
   Programmer: Adam Haertter
   Professor: Dr. Lee
   File Created: Nov 6, 2019
   File Updated: Nov 6, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "stackADT2.h"

struct stack_type {
   Item *contents;					//Contents are a pointer to Item values
   int top;
   int size;
};

static void terminate(const char *message)
{
   printf("%s\n", message);				//Prints error message and kills program
   exit(EXIT_FAILURE);
}

Stack create(int size)
{
   Stack s = malloc(sizeof(struct stack_type));		//Allocates memory for Stack s
   if(s == NULL)					//Terminates if s is null
	terminate("Error in create: stack could not be created.");
   s->contents = malloc(size * sizeof(Item));		//Allocates memory for contents of s
   if(s->contents == NULL) {
	free(s);					//Frees s from memory and terminates program
	terminate("Error in create: stack could not be created.");
   }
   s->top = 0;						//Empties stack
   s->size = size;
   return s;
}

void destroy(Stack s)
{
   free(s->contents);					//Frees contents of Stack s
   free(s);						//Frees Stack s
}

void make_empty(Stack s)
{
   s->top = 0;						//Empties stack by setting top index to 0
}

int is_empty(Stack s)
{
   return s->top == 0;					//Returns whether top value is 0
}

int is_full(Stack s)
{
   return s->top == s->size;				//Returns whether top of stack equals size of stack
}

void push(Stack s, Item i)
{
   if(is_full(s))					//Terminates program if stack is full
	terminate("Error in push: stack is full.");
   s->contents[s->top++] = i;				//Sets content value at top to i and increments top
}

Item pop(Stack s)
{
   if(is_empty(s))					//Terminates if stack is empty
	terminate("Error in pop: stack is empty.");
   return s->contents[--s->top];			//Returns content value of stack at new top
}
