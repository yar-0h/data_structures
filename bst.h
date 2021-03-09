// =================== Support Code =================
// Binary Search Tree ( BST ).
// ==================================================
#ifndef BST_H
#define BST_H

// Create a node data structure to store data within
// our BST. In our case, we will stores 'integers'
typedef struct node{
	int data;
	struct node* rightChild;
  	struct node* leftChild;
}node_t;

// Create a BST data structure
// Our BST holds a pointer to the root node in our BST called root.
typedef struct BST{
	int count;		// count keeps track of how many items are in the BST.
	node_t* root;		// root points to the root node in our BST.
}bst_t;

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values.
bst_t* create_bst(){
	// Modify the body of this function as needed.
	bst_t* myBST= (bst_t*)malloc(sizeof(bst_t));
    myBST->count = 0;
    myBST->root = NULL;

	return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element enqueued)
int bst_empty(bst_t* t){
    if (t->count <= 0) {
	    return 1;}
    else {
        return 0;
    }
    }

// Adds a new node containing item in the correct place of the BST.
// If the data is less then the current node we go right, otherwise we go left.
// Same as described in the README.md file. 
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed).
int bst_add(bst_t* t, int item){
    node_t* incomingNode = (node_t*)malloc(sizeof(node_t));
    incomingNode->data = item;
    incomingNode->leftChild = NULL;
    incomingNode->rightChild = NULL;
    if (bst_empty(t)) {
        t->root = incomingNode;
        t->count += 1;
        return 0;
    }
    else {
        node_t* placeNode = t->root;
        node_t* parentNode;
        while (placeNode != NULL) {
            parentNode = placeNode;
            if (item < placeNode->data) {
                placeNode = placeNode->leftChild;
            } else {
                placeNode = placeNode->rightChild;
            }
        }
        if (item < parentNode->data) {
            parentNode->leftChild = incomingNode;
            t->count += 1;
            return 0;
            }
        else if (item >= parentNode->data)  {
            parentNode->rightChild = incomingNode;
            t->count += 1;
            return 0;
            }
        else {
            return -1;
        }
    }
}

// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// For NULL tree it should print nothing. 
void bst_print(bst_t* t, int order){
    if (t->root == NULL) {
        return;
    }
    else {
        if (order == 0) {
            bst_t tempBST;
            tempBST.count = t->count;

            if (t->root->leftChild != NULL) {
                tempBST.root = t->root->leftChild;
                bst_print(&tempBST, 0);
            }

            printf("%d\n", t->root->data);

            if (t->root->rightChild != NULL) {
                tempBST.root = t->root->rightChild;
                bst_print(&tempBST, 0);
            }
        }
        else {
            bst_t tempBST;
            if (t->root->rightChild != NULL) {
                tempBST.root = t->root->rightChild;
                bst_print(&tempBST, 1);
            }

            printf("%d\n", t->root->data);

            if (t->root->leftChild != NULL) {
                tempBST.root = t->root->leftChild;
                bst_print(&tempBST, 1);
            }
        }
    }
}

// Returns the sum of all the nodes in the tree. 
// exits the program for a NULL tree. 
int sum(bst_t *t){
    if (t->root == NULL) {
        exit(1);
    }
    else {
        int total = 0;
        bst_t tempBST;
        tempBST.count = t->count;

        if (t->root->leftChild != NULL) {
            tempBST.root = t->root->leftChild;
            total += sum(&tempBST);
        }
        total += t->root->data;

        if (t->root->rightChild != NULL) {
            tempBST.root = t->root->rightChild;
            total += sum(&tempBST);
        }
        return total;
    }
}

// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree it exists the program. 
int find(bst_t * t, int value) {
    if (t->root == NULL) {
        exit(1);
    }
    else {
        bst_t tempBST;
        tempBST.count = t->count;
        if (t->root->data == value) {
            return 1;
        }
        else {
            if (t->root->data > value && t->root->leftChild != NULL) {
                tempBST.root = t->root->leftChild;
                return find(&tempBST, value);
            }
            else if (t->root->data <= value && t->root->rightChild != NULL) {
                tempBST.root = t->root->rightChild;
                return find(&tempBST, value);
            }
        }
    }
}

// BST Size
// Queries the current size of the BST
// A BST that has not been previously created will crash the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){
    if (t == NULL) {
        exit(1);
    }
    else {
        return t->count;
    }
}

void free_nodes(node_t* n) {
    if (n == NULL) {
        return;
    }
    free_nodes(n->leftChild);
    free_nodes(n->rightChild);
    free(n);
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the program terminates.
void free_bst(bst_t* t) {
    free_nodes(t->root);
    free(t);
}


#endif
