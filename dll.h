// =================== Support Code =================
// Doubly Linked List ( DLL ).
// ==================================================
#ifndef DLL_H
#define DLL_H

#include <stdlib.h>
#include <stdio.h>
// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
// TODO: MAKE MORE VERSATILE
typedef struct node{
        int data;
        struct node* next;
        struct node* previous;
}node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL{
        int count;              // count keeps track of how many items are in the DLL.
        node_t* head;           // head points to the first node in our DLL.
        node_t * tail;          //tail points to the last node in our DLL.
}dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
dll_t* create_dll(){
        dll_t* myDLL= (dll_t*)malloc(sizeof(dll_t));

        myDLL->count = 0;

        myDLL->head = NULL;
        myDLL->tail = NULL;

        return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t* l){
        if (l->count == 0) {
            return 1;}
        else {
            return 0;}
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, int item){
    while(1) {
        //TODO: MAKE BETTER

 node_t* new_item = (node_t*)malloc(sizeof(node_t));
            new_item->data = item;
            new_item->next = l->head;
            new_item->previous = NULL;

            if (dll_empty(l) == 1){
                l->tail = new_item;
                new_item->next = NULL;}

            else {
                l->head->previous = new_item;}
            l->head = new_item;
            l->count += 1;
            return 0;
            }
    return -1;
}

// push a new item to the end of the DLL ( after the last node in the list).
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, int item){
    while(1) {
        node_t* new_item = (node_t*)malloc(sizeof(node_t));
            new_item->data = item;
            new_item->next = NULL;
            new_item->previous = l->tail;

            if (dll_empty(l) == 1){
                l->head = new_item;
                new_item->previous = NULL;}

            else {
                l->tail->next = new_item;}
            l->tail = new_item;
            l->count += 1;
            return 0;
            }
                return -1;
}

// Returns the first item in the DLL.
// Removes an item from the DLL.
// Removing from an empty DLL should crash the program, call exit(1).
int dll_pop_front(dll_t* t){
    if (dll_empty(t) == 0) {
        node_t* popping_item = t->head;
        if (t->count > 1) {
            t->head = t->head->next;
            t->head->previous = NULL;}
        else {
            t->head = NULL;
            t->tail = NULL;}
        t->count -= 1;

        int output = popping_item->data;
        free(popping_item);
        return output;}
    else {
        exit(1);
        return(-1);}
        }

// Returns the last item in the DLL.
// Removes the last item from the DLL.
int dll_pop_back(dll_t* t){
    if (dll_empty(t) == 0) {
        node_t* popping_item = t->tail;
        if (t->count > 1) {
            t->tail = t->tail->previous;
            t->tail->next = NULL;}
        else {
            t->head = NULL;
            t->tail = NULL;}
        t->count -= 1;

        int output = popping_item->data;
        free(popping_item);
        return output;}
    else {
        exit(1);
        return(-1);}
        }

// Inserts a new node before the node at the specified position.
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed or trying to insert at a negative position or at
//  a position past the size of the DLL ).
int dll_insert(dll_t* l, int pos, int item){
    while(1) {
// I referenced  https://www.geeksforgeeks.org/write-a-function-to-get-nth-node-in-a-linked-list/
// for this section

            node_t* insert_position = l->head;
            int count = 0;
            while (insert_position != NULL){
                if (count == pos){
                    break;}
                count++;
                insert_position = insert_position->next;}

            node_t* new_item = (node_t*)malloc(sizeof(node_t));
            new_item->data = item;
            new_item->next = insert_position;

            if (count == 0) {
                l->head = new_item;
                if (l->count == 0) {
                    l->tail = new_item;
                    }
                new_item->previous = NULL;
               }
            else {
                insert_position->previous->next = new_item;
            }
            if (insert_position != NULL){
                new_item->previous = insert_position->previous;
                insert_position->previous = new_item;
                }
            l->count += 1;
            return 0;}

    return -1;
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the position is negative or trying to retrieve an item at or past the size,
// or the list is empty.
                                                                                                                            
int dll_get(dll_t* l, int pos){
    if ((pos >= 0) && (pos < l->count) && (dll_empty(l) == 0)) {
            node_t* get_position = l->head;
            int count = 0;

            while (get_position != NULL){
                if (count == pos){
                    break;}
                count++;
                get_position = get_position->next;}

            return get_position->data;}
    else {
            return -1;}
    }

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the position is negative or trying to remove an item at or past the size,
// or if the list is empty
int dll_remove(dll_t* l, int pos){
   if ((pos >= 0) && (pos < l->count) && (dll_empty(l) == 0)) {

            node_t* removal_position = l->head;
            int count = 0;

            while (removal_position != NULL){
                if (count == pos){
                    break;}
                count++;
                removal_position = removal_position->next;}

            if (removal_position->next == NULL) {
                l->tail = removal_position->previous;
                removal_position->previous = NULL;}
            else {
                removal_position->next->previous = removal_position->previous;}
                                                                                     
            if (count == 0) {
                l->head = removal_position->next;}
                // l->head->previous = NULL;}
            else {
                removal_position->previous->next = removal_position->next;}
            l->count -= 1;

            int output = removal_position->data;
            free(removal_position);
            return output;
   }
    else {
            return -1;}
}
// DLL Size
// Queries the current size of a DLL
// A DLL that has not been previously created will crash the program.
// (i.e. A NULL DLL cannot return the size)
unsigned int dll_size(dll_t* t){
        if (t != NULL) {
            return t->count;}
        else {
            exit(1);
            return 0;
            }
}

// Free DLL
// Removes a DLL and ALL of its elements from memory.
// This should be called before the program terminates.
void free_dll(dll_t* t){
    node_t* free_node = t->head;
    dll_t* free_dll= t;
    while (t->head != NULL) {
       free_node = t->head;
       t->head = t->head->next;
       free(t->head);
       }

    free(free_dll);
}

// Print DLL
// Returns a  string representing the items in the DLL, from head to tail.
void dll_print(dll_t* l){
    if (dll_empty(l) == 0){
        node_t* item_to_print = l->head;
        int count = 1;
        printf("%d", item_to_print->data);

        while (count < dll_size(l)){
                item_to_print = item_to_print->next;
                printf("..%d", item_to_print->data);
                count++;}
        }
 }

#endif
                                                                 