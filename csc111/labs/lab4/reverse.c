/* CSC111 Computer Science II
   Lab 4: Reversing a Series of Numbers
   Programmers: Adam Haertter & Tyler Owens
   Professor: Dr. Lee
   File Created: Sep 16, 2019
   File Updated: Sep 16, 2019
*/

#include <stdio.h>

#define N 10				//Defines a limit for array size N

int main()
{
   int a[N], i;

   printf("Enter %d numbers: ", N);	//Prints to the screen
   for(i = 0; i < N; i++)
	scanf("%d", &a[i]);		//Accepts an int and adds to the array

   printf("In reverse order:");		//Prints to the screen
   for (i = N - 1; i>=0; i--)
	printf(" %d", a[i]);		//Prints the contents of the array
   printf("\n");			//Prints a new line character

   return 0;
}
