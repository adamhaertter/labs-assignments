/* CSC 111 Computer Science 2
   lab 10 stack: stack.h
   Programmer: Tyler Owens, Adam
   Professor: Dr. Lee
   File Created: November 4, 2019
   File Updated: November 4, 2019
*/

#ifndef STACK_H
#define STACK_H

 enum {F,T};

void make_empty(void);                  //Makes stack empty
int is_empty(void);                    //Checks if empty
int is_full(void);                     //Checks if full
void push(int i);                       //Puts a value into stack
int pop(void);                          //Removes value from top of stack

#endif

