/* CSC111 Computer Science II
 * Lab 13 Copying a File: fcopy.c
 * Programmer: Adam Haertter
 * Professor: Dr. Lee
 * File Created: Nov 13, 2019
 * File Updated: Nov 13, 2019
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *source_fp, *dest_fp;				//Declares two file pointers
	int ch;

	if(argc!=3){
		fprintf(stderr, "usage: fcopy source dest\n");	//Prints an error if 3 arguments are not present
		exit(EXIT_FAILURE);				//Program terminates
	}

	if((source_fp = fopen(argv[1], "r")) == NULL){		//If the first file cannot be read
		fprintf(stderr, "Can't open %s\n", argv[1]);	//Prints error message
		exit(EXIT_FAILURE);				//Program terminates
	}

	if((dest_fp = fopen(argv[2], "w")) == NULL){		//If the second file cannot be written to
		fprintf(stderr, "Can't open %s\n", argv[2]);	//Prints error message
		fclose(source_fp);				//Closes connection to source file
		exit(EXIT_FAILURE);				//Program terminates
	}

	while((ch = getc(source_fp)) != EOF)			//Runs through every character until end of file
		putc(ch, dest_fp);				//Copies characters into dest_fp

	fclose(source_fp);					//Closes connections to files
	fclose(dest_fp);
	return 0;
}
