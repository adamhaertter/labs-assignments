/* CSC111 Computer Science II
   Parts Database - readline.c
   Programmers: Adam Haertter & Thomas Wolf
   Professor: Dr. Lee
   Date Created: Oct 16, 2019
   Date Updated: Oct 16, 2019
*/

#include <ctype.h>
#include <stdio.h>
#include "readline.h"

int read_line(char str[], int n)
{
   int ch, i=0;

   while(isspace(ch = getchar()))	//Assigns the value in getchar to ch
	;
   while(ch != '\n' && ch != EOF) {	//While ch is not a new line or end character
	if(i<n)
	   str[i++] = ch;		//Assigns ch to str[i] and increments i
	ch = getchar();
   }
   str[i] = '\0';			//Puts a null char at the end of str to end array
   return i;				//Returns index i value
}
