/* CSC111 Computer Science II
   Lab 6: runner.c
   Programmer: Scott Bucher & Adam Haertter
   Professor: Dr. Lee
   File Created: Oct 5, 2019
   File Updated: Oct 5, 2019
*/

#include "charlist.h"
#include <stdio.h>

/* A simple main function to play with the functionality in charlist.c */
int main()
{
	char x[10];
	initialize_list(x);
	add_to_list(x, 'c');
	add_to_list(x, 'a');
	add_to_list(x, 't');
	printf("Expect to see cat: ");
	print_list(x);

	delete_from_list(&(x[2]));		//Deletes character at index 2 from the list
	printf("Expect to see ca: ");
	print_list(x);

	int i;
	for(i = 0; i < 7; i++)
	{
		add_to_list(x, 'm'+i);		//Adds letters consecutively after m to the list
	}
	printf("Expect to see camnopqrs: ");
	print_list(x);

	delete_from_list(&(x[4]));		//Deletes character at index 4 from the list
	printf("Expect to see camnpqrs: ");
	print_list(x);

	delete_from_list(&(x[0]));		//Deletes first character from the list
	printf("Expect to see amnpqrs: ");
	print_list(x);

	return 0;
}
