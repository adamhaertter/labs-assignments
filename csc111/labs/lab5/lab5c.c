/* CSC111 Computer Science II
 * Lab 5 Array & Pointers: lab5c.c
 * Programmer: Yong Hang Lin & Adam Haertter
 * Professor: Dr. Lee
 * File Created: September 23, 2019
 * File Updated: September 23, 2019
 */

#include <stdio.h>

void swap(int a, int *b);
int main()
{
	int i = 1;
	int j = 2;
	printf("i = %d, j = %d\n", i, j);  //print i=1, j=2
	swap(i, &j);                       //runs swap function
	printf("i = %d, j = %d\n", i, j);  //prints i, j
	return 0;
}
void swap(int a, int *b)                   //b is the only pointer
{
	printf("a = %d, *b = %d\n", a, *b); 
	int temp = a;
	a = *b;                             //swaps a & b
	*b = temp;
	printf("a = %d, *b = %d\n", a, *b);  //prints on screen
}
