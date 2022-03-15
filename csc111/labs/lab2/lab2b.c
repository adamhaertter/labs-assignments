/* CSC111 Computer Science II
   Lab 2 Conditions & Loops: lab2b.c
   Programmers: Adam Haertter & Scott Bucher
   Professor: Dr. Lee
   File Created: Sep 9, 2019
   File Updated: Sep 9, 2019
*/

#include <stdio.h>

int main()
{
   int N=0;

   printf("Please enter a positive integer: ");		//Prompts the user for an integer
   scanf("%d", &N);

   while(N>1)
   {
      if(!(N%2))
      {
	 printf("%d ", N);
         N/=2;
      } else
      {
	 printf("%d ", N);
         N = (N*3)+1;
      }
   }

   printf("%d\n", N);

   return 0;
}
