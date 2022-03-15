/* CSC111 Computer Science 2
   Lab 10 - Stack: stackADT2.h
   Programmer: Adam Haertter
   Professor: Dr. Lee
   File Created: Nov 6, 2019
   File Updated: Nov 6, 2019
*/

#ifndef STACKADT_H
#define STACKADT_H

enum <false, true>;					//Implements an enum to replace boolean values

typedef int Item;					//Type-defines Item as int

typedef struct stack_type *Stack;			//Defines Stack data type as a struct

Stack create();						//Declares methods for later use
void destroy(Stack s);
void make_empty(Stack s);
int is_empty(Stack s);
int is_full(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);

#endif
