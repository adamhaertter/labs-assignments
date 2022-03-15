/* CSC111 Computer Science II
   Lab 2 Conditions & Loops: lab2a.c
   Programmer: Adam Haertter & Scott Bucher
   Professor: Dr. Lee
   File Created: Sep 9, 2019
   File Updated: Sep 9, 2019
*/

#include <stdio.h>
#include <stdlib.h>

//#define N 10									//Defines N as 10

int main(int argc, char **argv)
{
   int N = 0;
   N = atoi(argv[1]); 								//Converts command line input to integer and assigns to N

  // printf("Please enter an integer: "); 					//Prompts the user for an integer
  // scanf("%d", &N);								//Reads an integer value from the  user

   int i;
   int sum = 0;
   for(i=1; i<=N; i++)								//Calculates the sum using a for loop
   {
      sum+=i;
   }

   printf("By adding the numbers, the sum is %d\n", sum);			//Prints sum to the screen
   printf("Using the mathematical formula, the sum is %d\n", (N*(N+1))/2); 	//Prints the answer from the formula

   return 0;
}
