//
// =================== Support Code =================
// Graph.
// ==================================================
#ifndef GRAPH_H
#define GRAPH_H

// Create a neighbor data structure to server as the neighbor's list.
// In our case, we will stores 'integers' as our neighbors that 
// corresponding to the data that the actual nodes store.
typedef struct neighbor{
	int data;
	struct neighbor * next;
}neighbor_t;

// Create a node data structure to store data within
// our graph. In our case, we will stores 'integers'
// as our data in the nodes
typedef struct node{
	int data;
	struct node *next;
	struct neighbor * neighbor;
}node_t;

// Create a graph data structure
// Our graph keeps track of the number of nodes, the number of edges and an array
// of all the nodes in the graph, and the maximum number of nodes we store in our graph.
typedef struct graph{
	int numNodes;		
	int numEdges;
	node_t* nodes;	 //an array of nodes storing all of our nodes.
}graph_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Name: create_graph
// Input(s):
//          None
// Output: No value is returned, a Graph structure is created,
// memory is set allocated and default parameters are initialize.
graph_t* create_graph() {
	graph_t* myGraph= (graph_t*)malloc(sizeof(graph_t));
	myGraph->numNodes = 0;
	myGraph->numEdges = 0;
	myGraph->nodes = NULL;

	return myGraph;
}

// Graph Empty
// Check if the graph is empty
// Returns 0 if true (The graph is completely empty, i.e. numNodes == 0 )
// Returns -1 if false (the graph has at least one node)
// Name: graph_empty
// Input(s):
//          (1) 'g' is a pointer to an graph address.
// Output: int, 0 if g points to an empty graph, -1 otherwise.
int graph_empty(graph_t* g) {
    if (g->numNodes > 0) {
        return -1;
    }
	return 0;
}

// Adds a new node withe the correspoding item in the graph.
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed).
// Duplicates nodes should not be added. For a duplicate node returns 0.
// Name: graph_add_node
// Input(s):
//          (1) 'g' is a pointer to an graph address.
//
//          (2) 'item' is the value to be held by the node we are adding.
// Output: No value is returned, but graph should be modified to store an additional node..
int graph_add_node(graph_t* g, int item) {
    if (1) {
        node_t *newNode = (node_t *) malloc(sizeof(node_t));
        newNode->data = item;
        newNode->next = NULL;
        newNode->neighbor = NULL;

        if (graph_empty(g) == 0) {
            g->nodes = newNode;
        } else {
            node_t *checkNode = g->nodes;
            while (checkNode->next != NULL) {
                if (checkNode->data == item) {
                    free(newNode);
                    return 0;
                }
                checkNode = checkNode->next;
            }
            checkNode->next = newNode;
        }
        g->numNodes += 1;
        return 0;
    }
    return -1;
}

// Name: retrieveNode
// Input(s):
//          (1) 'g' is a pointer to an graph address.
//
//          (2) 'item' is the value held by the node we are trying to get.
// Output: the pointer to the node we were looking to retrieve is returned.
node_t* retrieveNode(graph_t* g, int item) {
    node_t *checkNode = g->nodes;
    while (checkNode != NULL) {
            if (checkNode->data == item) {
                return checkNode;
            }
            checkNode = checkNode->next;
    }
    checkNode = NULL;
    return checkNode;
}


// Removes the node from the graph and the corresponding edges connected 
// to the node.
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (the node to be removed doesn't exist in the graph).
// Name: removeNode
// Input(s):
//          (1) 'g' is a pointer to a graph address.
//
//          (2) 'item' is the value held by the node we are removing.
// Output: Returns a -1 if the operation fails (otherwise returns 0 on success).
int graph_remove_node(graph_t* g, int item) {
    node_t *removingNode = retrieveNode(g, item);
    if (removingNode == NULL) { return -1; }
    node_t *removingNodeHelp = g->nodes;
    neighbor_t *removingNeighbor;
    neighbor_t *removingNeighborHelp;

    if (removingNodeHelp == removingNode) {
        g->nodes = removingNode->next;
    }
    //REMOVING NODE FROM LIST
    else {
        while (removingNodeHelp->next != removingNode && removingNodeHelp->next != NULL) {
            removingNodeHelp = removingNodeHelp->next;
        }
        removingNodeHelp->next = removingNode->next;
    }
    //REMOVING ANY NEIGHBOR RELATIONSHIP HELD BY OTHER NODES
    removingNodeHelp = g->nodes;

    while (removingNodeHelp->next != NULL) {
        if (removingNodeHelp->neighbor != NULL) {
            removingNeighborHelp = removingNodeHelp->neighbor;
            while (removingNeighborHelp != NULL && removingNeighborHelp->next != NULL) {
                if (removingNeighborHelp->next->data == item) {
                    removingNeighbor = removingNeighborHelp->next;
                    if (removingNeighborHelp->next->next != NULL) {
                        removingNeighborHelp->next = removingNeighborHelp->next->next;}
                    else {removingNeighborHelp->next = NULL;}
                    free(removingNeighbor);
                }
                removingNeighborHelp = removingNeighborHelp->next;
            }
        }
        removingNodeHelp = removingNodeHelp->next;
    }
    neighbor_t *tempNeighbor;

    //REMOVING NODE'S NEIGHBOR RELATIONSHIPS
    while (removingNode->neighbor != NULL) {
        tempNeighbor = removingNode->neighbor;
        removingNode->neighbor = removingNode->neighbor;
        free(tempNeighbor);
    }
    free(removingNode);
    g->numNodes -= 1;
    return 0;
}

//Adds an edge from source to destination. 
//If source or desination is not found in the graph returns -1.
//Otherwise it returns 0 1( even for trying to add a duplicate edge )
// Name: graph_add_edge
// Input(s):
//          (1) 'g' is a pointer to a graph address.
//
//          (2) 'source' is the value held by the node we are adding the outgoing edge.
//
//          (3) 'destination' is the value held by the node we are adding the incoming edge.
// Output: Returns a -1 if the operation fails (otherwise returns 0 on success).
int graph_add_edge(graph_t * g, int source, int destination) {

    node_t *sourceNode = retrieveNode(g, source);
    node_t *destinationNode = retrieveNode(g, destination);
    if (sourceNode == NULL || destinationNode == NULL) {return -1;}
    neighbor_t* sourceNewNeighbor = (neighbor_t *) malloc(sizeof(neighbor_t));
    sourceNewNeighbor->next = NULL;
    sourceNewNeighbor->data = destination;

    if (sourceNode->neighbor != NULL) {
        neighbor_t *checkNeighbor = sourceNode->neighbor;
        while (checkNeighbor->next != NULL) {
            checkNeighbor = checkNeighbor->next;
        }
        checkNeighbor->next = sourceNewNeighbor;
    } else { sourceNode->neighbor = sourceNewNeighbor; }
    g->numEdges += 1;
    return 0;
}


//Removes an edge from source to destination.
//If source or desination is not found in the graph returns -1.
//If no such edge exists also returns -1.
//Otherwise it returns 0
// Name: graph_remove_edge
// Input(s):
//          (1) 'g' is a pointer to a graph address.
//
//          (2) 'source' is the value held by the node we are removing the edge.
//
//          (3) 'destination' is the value held by the node we are removing the edge.
// Output: Returns a -1 if the operation fails (otherwise returns 0 on success).
int graph_remove_edge(graph_t * g, int source, int destination){

    neighbor_t* removingEdge = NULL;
    neighbor_t* removingEdgeHelp = NULL;
    node_t* removalSource = retrieveNode(g, source);
    //CHECK IF SOURCE AND DESTINATION EXIST
    if (removalSource == NULL|| retrieveNode(g, destination) == NULL) {return -1;}

    //IF THE NODE WE ARE REMOVING THE EDGE FROM HAS NEIGHBORS
    if (removalSource->neighbor != NULL) {
        removingEdgeHelp = removalSource->neighbor;
        if (removingEdgeHelp->data == destination) {
            if (removingEdgeHelp->next != NULL) {
                removalSource->neighbor = removingEdgeHelp->next;
                free(removingEdgeHelp);
            }
            else {
                removalSource->neighbor = NULL;
                free(removingEdgeHelp);
            }
            g->numEdges -= 1;
            return 0;
            }
        while (removingEdgeHelp != NULL && removingEdgeHelp->next != NULL) {
            if (removingEdgeHelp->next->data == destination) {
                removingEdge = removingEdgeHelp->next;
                if (removingEdgeHelp->next->next != NULL) {
                    removingEdgeHelp->next = removingEdgeHelp->next->next;}
                else {removingEdgeHelp->next = NULL;}
                free(removingEdge);
                g->numEdges -= 1;
                return 0;
            }
            removingEdgeHelp = removingEdgeHelp->next;
        }
    }
    return -1;
}


//Returns 0 if the node with value is in the graph, otherwise returns -1;
// Name: contains_node
// Input(s):
//          (1) 'g' is a pointer to a graph address.
//
//          (2) 'value' is the data held by the node we are searching for.
// Output: Returns 0 if the node with value is in the graph, otherwise returns -1;
int contains_node( graph_t * g, int value){
    node_t *checkNode = g->nodes;
    while (checkNode->next != NULL) {
        if (checkNode->data == value) {
            return 0;
        }
        checkNode = checkNode->next;
    }
    return -1;
}

//Returns 0 if an edge from source to destination exists, -1 otherwise.
// Name: contains_edge
// Input(s):
//          (1) 'g' is a pointer to a graph address.
//
//          (2) 'source' is the data held by the node we are looking for a connection from
//
//          (3) 'destination' is the data held by the node we are looking for a connection from
// Output: Returns 0 if an edge from source to destination exists, -1 otherwise.
int contains_edge( graph_t * g, int source, int destination){
    node_t *checkNode = g->nodes;
    neighbor_t* checkNeighbor;
    while (checkNode->next != NULL) {
        if (checkNode->data == source && checkNode->neighbor != NULL) {
            checkNeighbor = checkNode->neighbor;
            while (checkNeighbor != NULL) {
                if (checkNeighbor->data == destination) {
                    return 0;
                }
                checkNeighbor = checkNeighbor->next;
            }
        }
        checkNode = checkNode->next;
    }
    return -1;
}
//Returns an int array of all the neighbors of the node with data=value.
// Name: getNeighbors
// Input(s):
//          (1) 'g' is a pointer to a graph address.
//
//          (2) 'value' is the data held by the node of which whose neighbors we are retrieving.
//
// Output: Returns 0 if an edge from source  exists, array of neighbors otherwise.
int * getNeighbors( graph_t * g, int value ) {

	int* neighborArray = (int*)malloc(sizeof(int) * g->numNodes);

    node_t *checkNode = g->nodes;
    neighbor_t* checkNeighbor;
    int i = 0;
    while (checkNode->next != NULL) {
        if (checkNode->data == value) {
            checkNeighbor = checkNode->neighbor;
            while (checkNeighbor->next != NULL) {
                 neighborArray[i] = checkNeighbor->data;
                 i++;
                 checkNeighbor = checkNeighbor->next;
                }
            return neighborArray;
        }
        checkNode = checkNode->next;
    }
    return 0;
}


// Returns the number of neighbors for value.
int numNeighbors( graph_t * g, int value ){
    node_t *checkNode = g->nodes;
    neighbor_t* checkNeighbor;
    int i = 0;
    while (checkNode->next != NULL) {
        if (checkNode->data == value) {
            checkNeighbor = checkNode->neighbor;
            while (checkNeighbor->next != NULL) {
                i++;
                checkNeighbor = checkNeighbor->next;
            }
        }
        checkNode = checkNode->next;
    }
    return i;
}


// Prints the the graph using BFS
// For NULL or empty graph it should print nothing. 
void graph_print(graph_t * g){
	
}

// Graph Size
// Returns the number of nodes in the graph
unsigned int graph_num_nodes(graph_t* g){
	return 0;
}

// Graph Size
// Returns the number of edges in the graph
unsigned int graph_num_edges(graph_t* g){
	return 0;
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the progrram terminates.
void free_graph(graph_t* g) {
    node_t* checkNode = g->nodes;
    node_t* deleteNode;
    neighbor_t* checkNeighbor;
    neighbor_t* deleteNeighbor;
    while (checkNode != NULL) {
        deleteNode = checkNode;
        checkNeighbor = checkNode->neighbor;
        while (checkNeighbor != NULL) {
            deleteNeighbor = checkNeighbor;
            checkNeighbor = checkNeighbor->next;
            free(deleteNeighbor);
        }

        checkNeighbor = NULL;
        checkNode = checkNode->next;
        free(deleteNode);
    }
    free(g);
}


#endif
