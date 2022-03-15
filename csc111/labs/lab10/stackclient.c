/* CSC111 Computer Science 2
   Lab 10 - Stack: stackclient.c
   Programmer: Adam Haertter
   Professor: Dr. Lee
   File Created: Nov 6, 2019
   File Updated: Nov 6, 2019
*/

#include <stdio.h>
#include "stackADT.h"

int main()
{
   Stack s1, s2;
   int n;

   s1 = create();					//Creates 2 stacks
   s2 = create();

   push(s1, 1);
   push(s1, 2);						//Pushes values into first stack

   n = pop(s1);						//Pops top value off of first stack
   printf("Popped %d from s1\n", n);			//Prints to the screen
   push(s2, n);						//Pushes n into second stack
   n = pop(s1);
   printf("Popped %d from s1\n", n);
   push(s2, n);

   destroy(s1);						//Destroys s1

   while(!is_empty(s2))
	printf("Popped %d from s2\n", pop(s2));		//Prints popped values while s2 isn't empty

   push(s2, 3);						//Pushes 3 into second stack
   make_empty(s2);					//Empties second stack
   if(!is_empty(s2))
	printf("s2 is empty\n");			//Prints to the screen if s2 is empty
   else
	printf("s2 is not empty\n");			//Prints to the screen if s2 is not empty

   destroy(s2);						//Destroys s2

   return 0;
}
