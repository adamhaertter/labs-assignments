/*
 * CSC111 Computer Sicence II
 * Lab 15 Quick Sort with Pointers: qsortv2.c
 * Programmers: Scott Bucher & Adam Haertter
 * Professor: Dr. Lee
 * File Created: Nov 18, 2019
 * File Updated: Nov 20, 2019
*/

#include <stdio.h>
#include <stdlib.h>

void quicksort(int *a, int *low, int *high);          //Defines the quicksort fucntion (doesn't return a value, only sets it)
int *split(int *a, int *low, int *high);              //Split returns the index of high

int main()
{
	int i, N;

	printf("How many elements would you like to sort? "); //prompt the user for how many integers they will be sorting
		scanf("%d", &N);

	int *a = malloc(N*sizeof(int));			//Allocates a to N integers worth of memory
		
	printf("Enter %d numbers to be sorted: ", N);	//User input
	for (i = 0; i < N; i++){
		scanf("%d", &a[i]);
	}
	
	quicksort(a, a, a+N-1);                        	//Calls quicksort

	printf("In sorted order: ");                   	//Outputs the sorted array
	for (i = 0; i < N; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}

void quicksort(int *a, int *low, int *high)
{
	int *middle;

	if (low >= high) return;			//if low is equal to what high is, or greater than, then this part is sorted and you can return
	middle = split(a, low, high);			//set middle index through the split function
	quicksort(a, low, middle-1);			//quicksort first half
	quicksort(a, middle+1, high);			//quicksort second half
}

int *split(int *a, int *low, int *high)			//split wll return the index of high
{
	int part_element = *low;

	for (;;) {					//intentional infinite loop
		while (low < high && part_element <= *high)  //decrease high
			high--;
		if (low >= high) break;			//low should never be greater than or equal to high unless it is sorted, so break
		*low++ = *high;

		while (low < high && *low <= part_element)   //increase low
			low++;
		if (low >= high) break;			//low should never be greater or equal to high unless it is sorted, so break
		*high-- = *low;
	}

	*high = part_element;
	return high;					//return the index of high
}



