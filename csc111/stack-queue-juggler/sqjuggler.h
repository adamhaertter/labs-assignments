/* CSC111 Computer Science
 * Project 1: Stack & Queue ADT Juggler: sqjuggler.h
 * Programmer: Adam Haertter
 * Professor: Dr. Lee
 */

typedef int Item;
typedef struct stack_type *Stack;
typedef struct queue_type *Queue;

void terminate(const char *message);

Stack createStack();
Queue createQueue();

void destroyStack(Stack s);
void empty_stack(Stack s);
int stack_is_empty(Stack s);
int stack_is_full(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);

void destroyQueue(Queue q);
void empty_queue(Queue q);
int queue_is_empty(Queue q);
void enqueue(Queue q, Item i);
Item dequeue(Queue q);

void add(int toAdd);
void del();
