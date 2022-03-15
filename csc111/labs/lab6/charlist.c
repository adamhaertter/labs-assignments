z/* CSC111 Computer Science II
   Lab 6 Pointers and Arrays: charlist.c
   Programmers: Scott Bucher & Adam Haertter
   Professor: Dr. Lee
   Date Created: Oct 5, 2019
   Date Updated: Oct 5, 2019
*/

#include "charlist.h"
#include <stdio.h>
/*
   intialize the array pointed to by p so that it is ready to
   be a character list
*/
void intialize_list(char *p)
{
   *p = '\0';                           //starts the array
}

/*
   print ot the characters in the list
*/
void print_list(char *p)
{
   char *temp = p;
   while (*temp != '\0')                //checks if that spot in the array equals null
   {
        printf("%c", *temp);            //if it doesn't print it out
      temp++;                           //move onto the next spot
   }
   printf("\n");
}

/*
   Add a character to the end of the list
*/
void add_to_list(char *p, char x)
{
   char *temp = p;
   while  (*temp != '\0')               //checks if that spot in the array equals null
   {
       temp++;                         //if it doesn't move on
   }
   *temp = x;
   temp ++;                            //Adds char x onto the end of the array
   *temp = '\0';
}
/* Delete a character from the list */
void delete_from_list(char *p)
{
	char *temp = p; 		//temp is the list at the specified entry sent over
	while(*temp != '\0')		//Runs until temp is a null character (end of array)
	{
	    *temp = *(temp+1);		//Sets the value at the current slot to the value in the next slot
	    temp++;			//Moves temp up by one index slot
	}
	temp++;
	*temp = '\0';			//Makes sure the array ends

}
