/* CSC111 Computer Science II
   Lab 9
   Programmers: Adam Haertter & Yong Hang Lin
   Professor: Dr. Lee
   File Created: Oct 28, 2019
   File Updated: Oct 28, 2019
*/

#include <stdio.h>

int sum(int (*f)(int), int start, int end);
int g(int);

int main()
{
   int i, j;

   printf("Input starting number: ");
   scanf("%d", &i);					//Assigns starting value to i
   printf("Input ending number: ");
   scanf("%d", &j);					//Assigns ending value to j

   if(i<j)
   	printf("Sum of squares: %d\n", sum(g,i,j));	//Prints the sum of the squares from i to j
   else
	printf("Error: Starting number less than or equal to ending number\n");
   return 0;
}

int sum(int (*f)(int), int start, int end)
{
  int sum = 0;
  for(int n = start; n <= end; n++)			//n goes from start to end and increments by 1
  {
	sum += (*f)(n);					//Adds return from function (*f)(n) to sum
  }
  return sum;						//Returns sum of function *f for values start to end
}

int g(int x)
{
   return x*x;					//Returns the square of the input
}
