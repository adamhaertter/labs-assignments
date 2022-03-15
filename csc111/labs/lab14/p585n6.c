/* CSC 111 Computer Science 2
   Lab 14: p585n6.c
   Programmer: Scott Bucher, Adam Haertter, Andrew Kress
   Professor: Dr. Lee
   File Created: November 17, 2019
   File updated: November 17, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 10
typedef unsigned char BYTE;

void pBytes(BYTE b[], int bRead, int maxBytes);
void pChars(BYTE c[], int bRead);

int main(int argc, char *argv[])
{

	FILE *file;

	if (argc != 2) {
		printf("Please specify a file.\n");
		exit(EXIT_FAILURE);
	}

	if ((file = fopen(argv[1], "rb")) == NULL) {
		printf("Specified file not found.\n");
		exit(EXIT_FAILURE);
	}

	printf("Offset              Bytes              Characters\n");
	printf("------ -----------------------------  ----------\n");

	BYTE b[MAX];
	int o = 0;
	int bytesRead;
	while ((bytesRead = fread(b, sizeof(BYTE), MAX, file)) > 0) {
		printf("%6d ", o);
		pBytes(b, bytesRead, MAX);
		pChars(b, bytesRead);
		o += MAX;	
	}

    fclose(file);
    return 0;
}

void pBytes(BYTE b[], int bRead, int maxBytes) 
{
	for (int i = 0; i < maxBytes; ++i) {
		if (i >= bRead)
			printf("   ");
		else
			printf("%-3.2X", b[i]);
	}
	printf(" ");
}

void pChars(BYTE c[], int bRead)
{
	for (int i = 0; i < bRead; ++ i) {
		printf("%c", isprint(c[i]) ? c[i] : '.');
	}
	printf("\n");
}
