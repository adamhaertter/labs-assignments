/* CSC 111 Computer Science 2
   Lab 10 stack: stack1.c
   Programmer: Tyler Owens, Adam Haertter
   Professor: Dr. Lee
   File Created: November 4, 2019
   File Updated: November 4, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define STACK_SIZE 100                                     //max stack size

static int contents[STACK_SIZE];                              //Sets all values as max stack size
static int top = 0;                                           //Clears all the values in stack

static void terminate(const char *message)                    //Stops checking functions in the loop
{
   printf("%s\n", message);                                   //Tells why it failed
   exit(EXIT_FAILURE);                                        //Exits functions
}

void make_empty(void)                                          //Cleans out the stack
{
   top = 0;
}

int is_empty(void)                                             //Checks if the stack is empty or not
{
   return top == 0;
}

int is_full(void)                                              //Checks if stack is full or not
{
   return top ==  STACK_SIZE;
}

void push(int i)                                               //Pushes the value of i onto the top of the stack
{
   if(is_full())                                               //Checks if full first
      terminate("Error in push: stack is full.");
   contents[top++] = i;
}

int pop(void)                                                  //Takes the top value off the stack like a cup stack at mcdonalds
{
   if (is_empty())
      terminate("Error in pop: stack is empty.");
   return contents[--top];
}

