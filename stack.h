
// Stack
//

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
// Stores the maximum 'depth' of our stack.
// Our implementation enforces a maximum depth of our stack.
// (i.e. capacity cannot exceed MAX_DEPTH for any stack)
# define MAX_DEPTH 32

// Create a node data structure to store data within
// our stack. In our case, we will stores 'integers'
typedef struct node{
	int data;
	struct node* next;
}node_t;

// Create a stack data structure
// Our stack holds a single pointer to a node, which
// is a linked list of nodes.
typedef struct stack{
	int count;		// count keeps track of how many items
				// are in the stack.
	unsigned int capacity;	// Stores the maximum size of our stack
	node_t* head;		// head points to a node on the top of our stack.
}stack_t;

// Creates a stack
// Returns a pointer to a newly created stack.
stack_t* create_stack(unsigned int capacity){
	stack_t* myStack = (stack_t*)malloc(sizeof(stack_t));
	myStack->capacity = capacity;
	myStack->count = 0;
	myStack->head = (node_t*)malloc(sizeof(node_t));	

	return myStack;
}

// Stack Empty
// Check if the stack is empty
// Returns 1 if true (The stack is completely empty)
// Returns 0 if false (the stack has at least one element enqueued)
int stack_empty(stack_t* s){
    if (s->count == 0) {
	return 1;}
    else {
	return 0;}
}

// Stack Full
// Check if the stack is full
// Returns 1 if true (The Stack is completely full, i.e. equal to capacity)
// Returns 0 if false (the Stack has more space available to enqueue items)
int stack_full(stack_t* s){
    if (s->capacity == s->count) {
        return 1;}
    else {
	return 0;}
}

// Enqueue a new item
// i.e. push a new item into our data structure
// Returns a -1 if the operation fails (otherwise returns 0 on success).
int stack_enqueue(stack_t* s, int item){
    if (stack_full(s) == 0) {
        node_t* new_item = (node_t*)malloc(sizeof(node_t));	
        new_item->next = s->head;
        new_item->data = item;
        
        s->head = new_item;
        s->count += 1;
        return 0;}

    else {	
	return -1;}
    }


// Dequeue an item
// Returns the item at the front of the stack and
// removes an item from the stack.
int stack_dequeue(stack_t* s){
    if (stack_empty(s) == 0) {
        node_t* outgoing_item = s->head;
        s->head = s->head->next;
        s->count -= 1;
        
        int output = outgoing_item->data;
        free(outgoing_item);
        return output;}
    else {
      exit(1);
      return (-1);}
}


// Stack Size
// Queries the current size of a stack
// A stack that has not been previously created will crash the program.
unsigned int stack_size(stack_t* s){
    if (s != NULL) {
        return s->count;}
    else {	
        exit(1);
        return -1;
         }
    }

// Free stack
// Removes a stack and ALL of its elements from memory.
// This should be called before the program terminates.
void free_stack(stack_t* s){
    while (stack_empty(s) != 1) {
       stack_dequeue(s);
       printf("OK");
       return;    
        }
    free(s->head);
    free(s);}
    
#endif
