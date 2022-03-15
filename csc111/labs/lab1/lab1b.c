/* CSC111 Computer Science II
 * Lab 1 Getting to Know Linux: lab1b.c
 * Programmer: Adam Haertter
 * Professor: Dr. Lee
 * File Created: Aug 28, 2019
 * File Updated: Aug 28, 2019
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
   int i;
   printf("Input? ");
   scanf("%d", &i);
   printf("What is the value in i? %d \n", i);

   printf("argc? %d\n", argc);
   printf("argv[0]? %s\n", argv[0]);
   printf("argv[1]? %s\n", argv[1]);
   printf("argv[2]? %s\n", argv[2]);
   return 0;
}
