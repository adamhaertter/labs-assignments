/* CSC111 Computer Science II
 * Lab 3 Modular Programming - lab3.c
 * Programmers: Adam Haertter and Yong Hang Lin
 * Professor: Dr. Lee
 * File Created: Sep 30, 2019
 * File Updated: Sep 30, 2019
 */

#include <stdio.h>
#include "lab3.h"					//Includes header lab3.h
#define NUM 100

int main()
{
	int s;
	printf("This is Lab3.\n");			//Prints to the screen
	printf("Let's add some integers.\n");		//Prints

	s = lab3a(NUM);					//Runs lab3a(NUM) for s
	printf("lab3a: sum of 1 to %d = %d\n", NUM, s); //Prints
	
	s = lab3b(NUM);					//Runs lab3b(NUM) for s
	printf("lab3b: sum of 1 to %d = %d\n", NUM, s); //Prints

	return 0;
}
