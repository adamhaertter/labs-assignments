/* CSC111 Computer Science 2
   Lab 5: Pointer Example
   Programmer: Adam Haertter
   Professor: Dr. Lee
   File Created: Sep 18, 2019
   File Updated: Sep 18, 2019
*/

#include <stdio.h>

int main()
{
   int z=10;				//Declaration of integer z
   int *i;				//Declaration of pointer i
   i = &z;				//Assignment of pointer to integer

   printf("z-integer: %d\n", z);	//Prints Z to screen
   printf("i-pointer: %d\n", *i);	//Prints I to screen
   printf("z-address: %p\n", &z);
   printf("i-address: %p\n", i);

   return 0;
}
