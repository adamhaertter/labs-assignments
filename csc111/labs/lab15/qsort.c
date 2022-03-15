/*
 * CSC111 Computer Sicence II
 * Lab 15 Quick Sort: qsort.c
 * Programmers: Scott Bucher & Adam Haertter
 * Professor: Dr. Lee
 * File Created: Nov 18, 2019
 * File Updated: Nov 18, 2019
*/

#include <stdio.h>

void quicksort(int a[], int low, int high);          //Defines the quicksort fucntion (doesn't return a value, only sets it)
int split(int a[], int low, int high);               //Split returns the index of high

int main()
{
	int i, N;

	printf("How many element would you like to sort? ");
		scanf("%d", &N);

	int a[N];

	printf("Enter %d numbers to be sorted: ", N); //User input
	for (i = 0; i < N; i++)
		scanf("%d", &a[i]);
	
	quicksort(a, 0, N-1);                          //Calls quicksort

	printf("In sorted order: ");                   //Outputs the sorted array
	for (i = 0; i < N; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}

void quicksort(int a[], int low, int high)
{
	int middle;

	if (low >= high) return;
	middle = split(a, low, high);
	quicksort(a, low, middle-1);
	quicksort(a, middle+1, high);
}

int split(int a[], int low, int high)
{
	int part_element = a[low];

	for (;;) {
		while (low < high && part_element <= a[high])
			high--;
		if (low >= high) break;
		a[low++] = a[high];

		while (low < high && a[low] <= part_element)
			low++;
		if (low >= high) break;
		a[high--] = a[low];
	}

	a[high] = part_element;
	return high;
}



