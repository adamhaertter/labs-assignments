/* CSC111 Computer Science II
 * Project 1: Stack & Queue ADT Juggler - queue.c
 * Programmer: Adam Haertter
 * Professor: Dr. Lee
 */

#include <stdio.h>
#include <stdlib.h>
#include "sqjuggler.h"

struct node{
	Item data;
	struct node *next;
	struct node *prev;
};

struct queue_type{
	struct node *front;
	struct node *end;
};

Queue createQueue(){
	Queue q = malloc(sizeof(struct queue_type));
	if(q == NULL)						//Terminates if queue cannot be created
		terminate("Error in createQueue: queue could not be created.");
	q->front = NULL;					//front and end are set to NULL because new queue is empty
	q->end = NULL;
	return q;
}

void destroyQueue(Queue q){
	empty_queue(q);						//Empties queue before destroying it
	free(q);
}

void empty_queue(Queue q){
	while(!queue_is_empty(q))				//Dequeues every item in queue
		dequeue(q);
}

int queue_is_empty(Queue q){
	return q->front == NULL;
}

void enqueue(Queue q, Item i){
	struct node *new_node = malloc(sizeof(struct node));
	if(new_node == NULL)					//Terminates if full
		terminate("Error in enqueue: queue is full.");

	if(queue_is_empty(q))					//Sets new_node to the first in queue if empty
		q->front = new_node;
	else							//Otherwise, sets new_node to the last one's previous in line
		q->end->prev = new_node;
	new_node->data = i;
	new_node->next = q->end;				//Previous End is now next in line from new_node
	q->end = new_node;					//new_node is now last in queue
}

Item dequeue(Queue q){
	struct node *old_front;
	Item i;

	if(queue_is_empty(q))					//Terminates if empty
		terminate("Error in dequeue: queue is empty.");
	if(q->front == q->end){					//If queue only has 1 item
		i = q->front->data;				
		q->front = NULL;				//Queue is now empty
	} else {
		old_front = q->front;
		i = old_front->data;
		q->front = old_front->prev;			//Queue shifts up in order by one
		free(old_front);				//Old front value is freed from memory
	}
	return i;
}
