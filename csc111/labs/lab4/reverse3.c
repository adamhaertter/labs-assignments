/* CSC111 Computer Science II
   Lab 4 Reverse Variations: reverse3.c
   Programmers: Adam Haertter & Tyler Owens
   Professor: Dr. Lee
   File Created: Oct 9, 2019
   File Updated: Oct 9, 2019
*/

#include <stdio.h>

#define N 10				//Defines size of array to create

int main()
{
   int a[N], *p;			//Declares array a and pointer p

   printf("Enter %d numbers: ", N);	//Prompts the user to enter N numbers
   //for(p = a; p < a+N; p++)		//Stores numbers in pointer p and the entries above
   for(p = &a[0]; p < a+N; p++)		//Places p at the start of the array and moves upward
	scanf("%d", p);			//Accepts values to store

   printf("In reverse order:");		//Prints to the screen
   for(p = a+N-1; p >= a; p--)		//Moves pointer p downward back to where it started
	printf(" %d", *p);		//Prints numbers according to pointer p's index
   printf("\n");

   return 0;
}
