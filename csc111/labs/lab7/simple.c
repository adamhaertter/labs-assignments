/* CSC111 Computer Science II
   Lab 7 String Example: simple.c
   Programmer: Adam Haertter
   Professor: Dr. Lee
   File Created: Oct 9, 2019
   File Updated: Oct 9, 2019
*/

#include <stdio.h>
#include <string.h>

int main()
{
   int i;
   char *p = "hi, there, weather is good!";

   for(int i=0; i<strlen(p); i++)		//Increases i until it is the length of string p
   {
//	printf("%c\n", *(p+i));			//Prints each consecutive letter on a new line
	printf("%c", p[i]);			//Prints each letter using p as an array
   }
   printf("\n");

   return 0;
}
