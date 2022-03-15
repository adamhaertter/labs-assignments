/* CSC111 Computer Science II
   Lab 10 Stacks: stack2.c
   Programmers: Adam Haertter & Tyler Owens
   Professor: Dr. Lee
   File Created: Nov 4, 2019
   File Updated: Nov 4, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct node {
   int data;
   struct node *next;				//defines the next node in the sequence
};

static struct node *top = NULL;

static void terminate(const char *message)
{
   printf("%s\n", message);			//prints termination message received
   exit(EXIT_FAILURE);
}

void make_empty()
{
   while (!is_empty())
	pop();					//runs pop() when stack isn't empty
}

int is_empty(void)
{
   return top == NULL;				//returns whether the top is null
}

int is_full()
{
   return F;					//returns a false value 0
}

void push(int i)
{
   struct node *new_node = malloc(sizeof(struct node));	//allocates enough space for a new node
   if(new_node == NULL)
	terminate("Error in push: stack is full.");	//prints error message if new node can't exist

   new_node->data = i;
   new_node->next = top;				//shifts new_node up one
   top = new_node;					//shifts new_node to top of stack
}

int pop()
{
   struct node *old_top;				//creates a pointer to the old top node
   int i;

   if(is_empty())
	terminate("Error in pop: stack is empty.")	//terminates function if stack is empty

   old_top = top;
   i = top->data;
   top = top->next;					//shifts next node to the top of stack
   free(old_top);					//frees old_top from memory
   return i;
}
