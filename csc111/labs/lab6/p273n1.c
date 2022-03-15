/* CSC111 Computer Science II
   Lab 6: Page 273 Exercise 1
   Programmers: Scott Bucher & Adam Haertter
   Professor: Dr. Lee
   Date Created: Oct 2, 2019
   Date Updated: Oct 2, 2019
*/

#include <stdio.h>

int main()
{
   int a[] = {5, 15, 34, 54, 14, 2, 52, 72}; 		//Initializes the a array
   int *p = &a[1], *q = &a[5];               		//Sets values p & q
   printf("Value of *(p+3) = %d\n", *(p+3)); 		//p+3 accesses slot 4 & dereferences it to equal 14
   printf("Value of *(q-3) = %d\n", *(q-3)); 		//q-3 accesses slot 2 & dereferences it to equal 34
   printf("Value of q-p = %ld\n", q-p);                 //q-p is the distance between q and p which outputs 4
   printf("Value of p-q = %ld\n", p-q);                 //p-q is the distance between p and q which outputs 4
   printf("T/F is p < q: %c\n", p < q ? 'T' : 'F');     //outputs T if the accesss slot p is less than the access slot of q
   printf("T/F is *p < *q: %c\n", *p < *q ? 'T' : 'F'); //outputs T if the value of p is less than the value of q
   printf("Address of p = %p\n", p);                    //outputs the address of p
   printf("Address of q = %p\n", q);                    //outputs the address of q
   printf("Address of a = %p\n", a);                    //outputs the address of a
   printf("Address of a[1]: %p\n", &a[1]);              //outputs the address of a[1]
   printf("Address of a[2]: %p\n", &a[2]);              //outputs the address of a[2]
   printf("Address of a[3]: %p\n", &a[3]);		//outputs the address of a[3]
   printf("Address of a[4]: %p\n", &a[4]);		//outputs the address of a[4]
   printf("Address of a[5]: %p\n", &a[5]);		//outputs the address of a[5]

   return 0;
}
