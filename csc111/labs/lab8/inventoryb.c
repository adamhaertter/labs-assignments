/* CSC111 Computer Science II
   Parts Database Linked List - inventoryb.c
   Programmers: Adam Haertter & Andrew Kress
   Professor: Dr. Lee
   Date Created: Oct 16, 2019
   Date Updated: Oct 21, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "readline.h"

#define NAME_LEN 25

struct part {					//Defines structure for parts
   int number;
   char name[NAME_LEN+1];
   int on_hand;
   struct part *next;
};

struct part *inventory = NULL;			//Points to first part in database

struct part *find_part(int number);
void insert();
void search();
void update();
void print();

/*
 * main:	Prompts the user to enter an operation code,
 *		then calls a function to perform the requested
 *		action. Repeats until the user enters the
 *		command 'q'. Prints an error message if the user
 *		enters an illegal code.
 */
int main()
{
   char code;
   for(;;) {
	printf("Enter operation code: ");	//Prompts for code input
	scanf(" %c", &code);
	while(getchar() != '\n')		//Skips to the end of the line
	   ;
	switch(code) {
	   case 'i': insert();			//Runs insert() if i was inputted
		     break;
	   case 's': search();			//Runs search() if s was inputted
		     break;
	   case 'u': update();			//Runs update() if u was inputted
		     break;
	   case 'p': print();			//Runs print() if p was inputted
		     break;
	   case 'q': return 0;			//Quits program if q was inputted
	   default:  printf("Illegal code\n");	//Prints error message on invalid input
	}
	printf("\n");
   }
}

/* find_part:	Looks up a part number in the inventory
 *		array. Returns a pointer to the node
 *		containing the part number;  if the part
 *		number is not found, returns NULL.
 */
struct part *find_part(int number)
{
   struct part *p;

   for(p = inventory;
       p != NULL && number > p-->number;
       p = p->next)
	;
   if(p != NULL && number == p->number)		//Checks parameter against values in array
	 return p;				//Returns matching index
   return NULL;					//Returns -1 if there is no match
}

/* insert:	Prompts the user for information about a new
 *		part and then inserts the part into the
 *		inventory list; th elist remains sorted by
 *		part number. Prints an error message and returns
 *		prematurely if the part already exists or the
 *		space could not be allocated for the part.
 */
void insert()
{
   struct part *cur, *prev, *new_node;

   new_node = malloc(sizeof(struct part));		//Allocates memory the size of a struct part
   if(new_node == NULL) {
	printf("Database is full; can't add more parts.\n");
	return;
   }

   printf("Enter part number: ");			//Prompts user to input part number
   scanf("%d", &new_node->number);			//Assigns scanned value to part_number

   for(cur = inventory, prev = NULL;
       cur != NULL && new_node->number > cur->number;
       prev = cur, cur = cur-> next)
	;
   if(cur != NULL && new_node->number == cur->number) {	//Sends part_number to find_part and sees if it exists
	printf("Part already exists.\n");
	free(new_node);					//Releases the memory held by new_node
	return;
   }

   printf("Enter part name: ");				//Prompts user to enter part name
   read_line(new_node->name, NAME_LEN);			//Reads the product name from the line with limit NAME_LEN
   printf("Enter quantity on hand: ");			//Prompts user to enter quantity
   scanf("%d", &new_node->on_hand); 		 	//Scans for input of quantity and updates database

   new_node->next = cur;				//Sets the next part to be the current part
   if(prev == NULL)
	inventory = new_node;
   else
	prev->next = new_node;
}

/* search:	Prompts the user to enter a part number, then
 *		looks up the part in the database. If the part
 *		exists, prints the name and quantity on hand;
 *		if not, prints an error message.
 */
void search()
{
   int number;
   struct part *p;

   printf("Enter part number: ");				//Prompts user to enter a part number
   scanf("%d", &number);					//Scans input and assigns to number
   p = find_part(number);					//Finds part and assigns it to p
   if(p != NULL) {
	printf("Part name: %s\n", p->name);			//Prints part name, if found
	printf("Quantity on hand: %d\n", p->on_hand);		//Prints quantity, if found
   } else
	printf("Part not found.\n");
}

/* update:	Prompts the user to enter a part number.
		Prints an error message if the part doesn't
		exist; otherwise, prompts the suer to enter
		change in quantity on hand and updates the
		database.
 */
void update()
{
   int number, change;
   struct part *p;

   printf("Enter part number: ");				//Prompts user to enter part number
   scanf("%d", &number);					//Scans input and assigns to number
   p = find_part(number);					//Assigns part to struct part p using find_part
   if(p != NULL) {						//If the part exists,
	printf("Enter change in quantity on hand: ");		//Propts user to enter change in quantity
	scanf("%d", &change);					//Scans input and assigns to change variable
	p->on_hand += change;					//Adds change to the quantity variable
   } else
	printf("Part not found.\n");				//Prints error message if part doesn't exist
}

/* print:	Prints a listing of all parts in the database,
		showing the part number, part name, and
		quantity on hand. Parts will appear in
		ascending order.
 */
void print()
{
   struct part *p;

   printf("Part Number	Part Name			"	//Prints organizer headings
	"Quantity on Hand\n");
   for(p = inventory; p != NULL; p = p->next)
	printf("%7d	%-25s%11d\n", p->number,		//Prints contents of each part in inventory
		p->name, p->on_hand);
}
