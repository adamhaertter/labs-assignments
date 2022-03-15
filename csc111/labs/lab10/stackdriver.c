/* CSC 111 Computer Scinence 2
   lab 10 stack: stackdriver.c
   Programmer: Tyler Owens, Adam
   Professor: Dr. Lee
   File Created: Novemeber 4, 2019
   File Updated: Novemeber 4, 2019
*/

#include <stdio.h>
#include "stack1.c"

int main()
{
    make_empty();                                               //Emptys the stack
    if(is_empty())                                              //Checks if the stack is empty
       printf("The stack is empty\n");
    if(is_full())                                               //Checks if the stack is full
       printf("The stack is full\n");

    push(2);                                                  //Pushes 2 into the stack
    printf("Pushed 2 into the stack\n");                        //Prints message confirming
    push(4);                                                  //Pushes 4 into the stack
    printf("Pushed 4 into the stack\n");                        //Prints message confirming
    push(5);                                                  //Pushes 5 into the stack
    printf("Pushed 5 into the stack\n");                        //Prints message confirming

    printf("Poped %d off the stack\n", pop());               //Pops the value 2 of the stack


    return 0;
}
