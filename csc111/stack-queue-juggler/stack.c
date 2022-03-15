/* CSC111 Computer Science 2
   Project 1: Stack & Queue ADT Juggler - stack.c
   Programmer: Adam Haertter
   Professor: Dr. Lee
*/

#include <stdio.h>
#include <stdlib.h>
#include "sqjuggler.h"

struct node{
   Item data;
   struct node *next;					//Next node in sequence
};

struct stack_type {
   struct node *top;
};

void terminate(const char *message)
{
   printf("%s\n", message);				//Prints error message and kills program
   exit(EXIT_FAILURE);
}

Stack createStack(int size)
{
   Stack s = malloc(sizeof(struct stack_type));		//Allocates enough memory for Stack s
   if(s == NULL)					//Terminates if s is null
	terminate("Error in createStack: stack could not be created.");
   s->top = NULL;					//Sets top value to null
   return s;
}

void destroyStack(Stack s)
{
   empty_stack(s);					//Empties stack
   free(s);						//Frees stack from memory
}

void empty_stack(Stack s)
{
   while(!stack_is_empty(s))				//Pops stack until empty
	pop(s);
}

int stack_is_empty(Stack s)
{
   return s->top == NULL;				//Checks if top value is null
}

int stack_is_full(Stack s)
{
   return 0;						//Returns false (0), stack is never full
}

void push(Stack s, Item i)
{
   struct node *new_node = malloc(sizeof(struct node));	//Allocates memory for a new node
   if(new_node == NULL)					//Terminates if node is null
	terminate("Error in push: stack is full.");
   new_node->data = i;
   new_node->next = s->top;				//Sets next node value to top of stack
   s->top = new_node;
}

Item pop(Stack s)
{
   struct node *old_top;
   Item i;

   if(stack_is_empty(s))				//Terminates if node is empty
	terminate("Error in pop: stack is empty.");

   old_top = s->top;					//Sets old top to top of stack value
   i = old_top->data;
   s->top = old_top->next;				//Top of stack is now next node from old_top
   free(old_top);					//Frees old top from memory
   return i;						//Returns i as data of old_top
}
