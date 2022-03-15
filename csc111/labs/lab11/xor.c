/*
 * CSC111 Compter Science II
 * Lab11: xor.c
 * Programmers: Scott Bucher & Adam Haertter
 * Professor: Dr. Lee
 * Date Created: Nov 8, 2019
 * Date Updated: Nov 8, 2019
 */

#include <ctype.h>
#include <stdio.h>

#define KEY '&'

int main()
{
	int orig_char, new_char;

	while ((orig_char = getchar())!= EOF) {			//Assigns getChar() to orig_char if not at EOF
		new_char = orig_char ^ KEY;			//Assigns 1 or 0 to new_char depending on if orig_char and KEY are different
		if (isprint(orig_char) && isprint(new_char))	//Chekcs orig_char and new_char against each other
			putchar(new_char);			//If both true, puts new_char
		else
			putchar(orig_char);			//If false, puts orig_char
	}

	return 0;
}
