/* CSC111 Computer Science II
 * Lab 5 Arrays and Pointers: lab5b.c
 * Programmers: Adam Haertter & Yong Hang Lin
 * Professor: Dr. Lee
 * File Created: September 23, 2019
 * File Updated: September 23, 2019
 */

#include <stdio.h>

void swap(int *a, int *b);

int main()
{
	int i = 1;
	int j = 2;
	printf("before: i = %d, j = %d\n", i, j);	//Prints to the screen
	swap(&i, &j);					//Runs the swap function
	printf("after: i = %d, j = %d\n", i, j);	//Prints to the screen
	return 0;
}

void swap (int *a, int *b)				//Parameters are pointers
{
	printf("before *a = %d, *b = %d\n", *a, *b);	//Prints to the screen
	int temp = *a;
	*a = *b;					//Swaps the pointer values
	*b = temp;
	printf("after: *a = %d, *b = %d\n", *a, *b);	//Prints to the screen
}
