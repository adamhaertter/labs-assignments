/* CSC111 Computer Science II
 * lab 3 Modular Programming - lab3a.c
 * Programmers: Yong Hang Lin & Adam Haertter
 * Professor: Dr. Lee
 * File Created: Sept 30, 2019
 * File Updated: Sept 30, 2019
 */

#include "lab3.h"

int lab3a(int n){
	int i;
	int s = 0;
	for(i = 1; i <= n; i++){   //loop n times
		s = i + s;         //add sum
	}
	return s;                  //return the sum
}
