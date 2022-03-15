/* CSC111 Computer Science II
   Parts Database - readline.h
   Programmers: Adam Haertter & Thomas Wolf
   Professor: Dr. Lee
   Date Created: Oct 16, 2019
   Date Updated: Oct 16, 2019
*/

#ifndef READLINE_H
#define READLINE_H

/* read_line:	Skips leading white-space characters, then
 *		reads the remainder of the input line and
 *		stores it in str. Truncates the line if its
 *		length exceeds n. Returns the number of
 *		characters stored.
 */
int read_line(char str[], int n);

#endif
