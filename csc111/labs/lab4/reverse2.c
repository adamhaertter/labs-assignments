/* CSC 111 Computer Science II
   lab 4: reverse2.c
   Programmer: Tyler Owens & Adam Haertter
   Professor: Dr.Lee
   File created: September 16, 2019
   File updated: September 16,2019
*/

#include <stdio.h>

int main()
{
   int i, n;                                    //Declares our values

   printf("How many numbers do you want to reverse? ");      //Asks how many nums to reverse
   scanf("%d", &n);               //Scans for the users number

   int a[n];					//declares the a value

   printf("Enter %d numbers: ", n);              //asks the user to input nums
   for(i = 0; i < n; i++)                      //Loops scaning for nums
      scanf("%d", &a[i]);                        //Repeated function

   printf("In reverse order: ");             //Tells the user its in reverse
   for(i = n - 1; i >= 0; i--)             //Runs the loop backwards
      printf(" %d", a[i]);                          //Prints the nums reverse
   printf("\n");                          //Adds a space for characters

   return 0;
}
