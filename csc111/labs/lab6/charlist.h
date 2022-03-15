/* CSC111 Computer Science II
   Lab 6: charlist.h
   Programmer: Scott Bucher & Adam Haertter
   Professor: Dr. Lee
   File Created: Oct 5, 2019
   File Updated: Oct 5, 2019
*/

/* Initialize the array pointed to by p so that it is ready to be a character list */
void initialize_list(char *c);

/* Print our the chracters in the list that p points to */
void print_list(char *c);

/* Add a character to the end of the list that p points to */
void add_to_list(char *p, char x);

/* Delete a character from the list that p points to */
void delete_from_list(char *p);
