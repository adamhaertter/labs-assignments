/* CSC111 Computer Science II
 * Project 1 Stack & Queue ADT Juggler - sqjuggler.c
 * Programmer: Adam Haertter
 * Professor: Dr. Lee
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqjuggler.h"

#define MAX 100

Stack inStack, outStack;
Queue inQueue, outQueue;

int main(int argc, char **argv){
	
	FILE *fp;

	inStack = createStack();				//Initializes stacks and queues
	outStack = createStack();
	inQueue = createQueue();
	outQueue = createQueue();

	char str[MAX];						//Declares str for reading file

	if(argc != 2) {						//Terminates if file is not specified
		printf("Please specify a file.\n");
		exit(EXIT_FAILURE);
	}

	if((fp = fopen(argv[1], "rb")) == NULL){		//Terminates if file cannot be opened
		printf("Specified file not found.\n");
		exit(EXIT_FAILURE);
	}

	while(fgets(str, MAX, fp) != NULL){			//Traces through file fp
		char *val = malloc(MAX*sizeof(int));		//Allocates memory for temporary string val

		if(str[0] == 'a' || str[0] == 'A'){				//Determines 'add' command
			for(int i = 0; i< strlen(str)-4; i++)
				val[i] += str[i+4];		//Retrieves value to add from input file
			add(atoi(val));				//Adds converted string to stack and queue
		}
		else if(str[0] == 'd' || str[0] == 'D'){				//Determines 'delete' command
			del();
		} else						//Otherwise, bypass line
			continue;

		free(val);					//Frees val from memory
	}

	fclose(fp);						//Closes connection to file

	printf("outStack: ");
	while(!stack_is_empty(outStack))			//Pops values from outStack to print them
		printf("%d ", pop(outStack));
	printf("\n");

	printf("outQueue: ");
	while(!queue_is_empty(outQueue))			//Dequeues values from outQueue to print them
		printf("%d ", dequeue(outQueue));
	printf("\n");

	destroyStack(outStack);					//Destroys outStack and outQueue
	destroyQueue(outQueue);

	return 0;
}

void add(int toAdd) {
	push(inStack, toAdd);					//Pushes value into inStack
	enqueue(inQueue, toAdd);				//Enqueues value into inQueue
}

void del(){
	push(outStack, dequeue(inQueue));			//Dequeues front value from inQueue and pushes it into outStack
	enqueue(outQueue, pop(inStack));			//Pops top value from inStack and enqueues it to the end of outQueue
}
