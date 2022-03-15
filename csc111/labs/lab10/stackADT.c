/* CSC111 Computer Science 2
   Lab 10 - Stack: stackADT.c
   Programmer: Adam Haertter
   Professor: Dr. Lee
   File Created: Nov 6, 2019
   File Updated: Nov 6, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

#define STACK_SIZE 100

struct stack_type {
   int contents[STACK_SIZE];
   int top;
};

static void terminate(const char *message)
{
   printf("%s\n", message);				//Prints error message and kills program
   exit(EXIT_FAILURE);
}

Stack create()
{
   Stack s = malloc(sizeof(struct stack_type));		//Reserves memory for Stack s
   if(s == NULL)					//Terminates if malloc fails
	terminate("Error in create: stack could not be created.");
   s->top = 0;						//Sets top value to 0
   return s;
}

void destroy(Stack s)
{
   free(s);						//Frees s from memory
}

void make_empty(Stack s)
{
   s->top = 0;						//Sets top value to 0, empties stack
}

int is_empty(Stack s)
{
   return s->top == 0;					//Returns whether the top value is 0
}

int is_full(Stack s)
{
   return s->top == STACK_SIZE;				//Returns whether the top value meets STACK_SIZE
}

void push(Stack s, int i)
{
   if(is_full(s))
	terminate("Error in push: stack is full.");	//Terminates if s is full
   s->contents[s->top++] = i;				//Sets content int at the top value to i
}

int pop(Stack s)
{
   if(is_empty(s))
	terminate("Error in pop: stack is empty.");	//Terminates if s is empty
   return s->contents[--s->top];			//Returns value on top of stack
}
