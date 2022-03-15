/* CSC111 Computer Science II
 * Lab 5 Array & Pointers: lab5a.c
 * Programmer: Yong Hang Lin & Adam Haertter
 * Proffesor: Dr. Lee
 * File Created: September 23, 2019
 * File Updated: September 23, 2019
 */

#include <stdio.h>
void swap(int a, int b);
int main()
{
	int i = 1;
	int j = 2;
	printf("i = %d, j = %d\n", i, j);  //prints i, j
	swap(i, j);                        
	printf("i = %d, j = %d\n", i, j);  //i, j did not swap
	return 0;
}
void swap(int a, int b)                    //a = i, b = j
{
	printf("a = %d, b = %d\n", a, b);  //prints a = 1, b = 2
	int temp = a;
	a = b;				   //swap the values
	b = temp;
	printf("a = %d, b = %d\n", a, b);  //prints a = 2, b = 1
}
