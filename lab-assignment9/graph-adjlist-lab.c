// chen.haoyang4@northeastern.edu
// Haoyang (Hendrick) Chen
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* structure represents a node to store the names and pointer to
   next node */
typedef struct node
{
    char name[50];
    struct node* next;
} node;

/* Structure represents a Graph with an array of adjacency lists.
   Size of the array will be number of vertices. */
typedef struct Graph
{
    int numberOfVertices;
    struct node** adjLists;
} Graph;

/* A function to create a new node */
node* createNode(char* name)
{
    node* newNode = (node*)malloc(sizeof(node));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

/* A function to create a graph with an array of adjacency lists
   which is= number of vertices */
Graph* createGraph(int vertices)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numberOfVertices = vertices;
    graph->adjLists = (struct node**)malloc(vertices * sizeof(struct node*));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

/* function to count Number of lists present in the graph */
int numberoflistspresent(Graph* graph)
{
    int i, j = 0; // j->number of lists already there in the graph
    for (i = 0; i < graph->numberOfVertices; i++) {
        if (graph->adjLists[i] != NULL) {
            j++;
        }
    }
    return j;
}

/* searching the persons who are already there in the list if found,
   return his position, otherwise return -1 */
int search(char* name, Graph* graph)
{
    int i;
    for (i = 0; i < numberoflistspresent(graph); i++) {
        if (strcmp(graph->adjLists[i]->name, name) == 0) {
            return i; // position of person in the list
        }

    }
    return -1; // person not found in the list
}

/* adds an edge to an undirected graph */
void addConnection(Graph* graph, char* person, char* friend)
{
    int p = search(person, graph); // search for the person in the graph, index or position
    int f = search(friend, graph); // search for the friend in the graph, index or position

    // Add the person to the graph if not already present
    if (p == -1) {
        p = numberoflistspresent(graph);
        graph->adjLists[p] = createNode(person);
    }

    // Add the friend to the graph if not already present
    if (f == -1) {
        f = numberoflistspresent(graph);
        graph->adjLists[f] = createNode(friend);
    }

    // Add the friend to the person's adjacency list
    node* newNode = createNode(friend);
    newNode->next = graph->adjLists[p]->next;
    graph->adjLists[p]->next = newNode;

    // Add the person to the friend's adjacency list (since the graph is undirected)
    newNode = createNode(person);
    newNode->next = graph->adjLists[f]->next;
    graph->adjLists[f]->next = newNode;
}

/* function to print the adjacency list representation of a graph */
void printGraph(Graph* graph)
{
    int i;
    for (i = 0; i < graph->numberOfVertices; i++) {
        if (graph->adjLists[i] != NULL) {
            // print the current vertex and all its neighbors
            struct node* temp = graph->adjLists[i];
            printf("\n%s---", graph->adjLists[i]->name);
            while (temp->next != NULL) {
                temp = temp->next;
                printf("%s-", temp->name);
            }
            printf("NULL\n");
        }
    }
}

/*   CONVERSION TO MATRIX*/
int getIndex(Graph* graph, char* name)
{
    int N = graph->numberOfVertices;
    int i, j = 0;
    for (i = 0; i < N && strcmp(name, graph->adjLists[i]->name) != 0; i++) {
        j++;
    }
    return j;
}

void matrixForm(Graph* graph, int emptyMatrix[50][50], int N)
{
    int i, j;
    for (i = 0; i < N; i++) {
        struct node* temp = graph->adjLists[i]->next;
        while (temp != NULL) {
            j = getIndex(graph, temp->name);
            emptyMatrix[i][j] = 1;
            temp = temp->next;
        }
    }
}

void graphDestroy(Graph* graph)
{
    int i;
    node* p;
    for (i = 0; i < graph->numberOfVertices; i++) {
        node* temp = graph->adjLists[i];
        while (temp != NULL) {
            p = temp;
            temp = temp->next;
            free(p);
        }
    }
    free(graph->adjLists);
    free(graph);
}

void printMatrix(int matrix[50][50], Graph* graph)
{
    int row, col, nodes = graph->numberOfVertices;
    printf("\nAdjacent matrix:\n");
    printf("        ");
    for (col = 0; col < nodes; col++) {
        printf("%6s ", graph->adjLists[col]->name);
    }
    printf("\n");
    for (col = 0; col < nodes; col++) {
        printf("----------");
    }
    printf("\n");
    for (row = 0; row < nodes; row++) {
        printf("%7s| ", graph->adjLists[row]->name);
        for (col = 0; col < nodes; col++) {
            printf("  %2d    ", matrix[row][col]);
        }
        printf("\n");
    }
}

int main()
{
    int Num = 7;
    // construct a graph
    Graph* graph = createGraph(Num);

    addConnection(graph, "Person A", "Person B");
    addConnection(graph, "Person A", "Person G");
    addConnection(graph, "Person A", "Person E");
    addConnection(graph, "Person B", "Person E");
    addConnection(graph, "Person B", "Person C");
    addConnection(graph, "Person B", "Person G");
    addConnection(graph, "Person C", "Person D");
    addConnection(graph, "Person C", "Person E");
    addConnection(graph, "Person D", "Person E");
    addConnection(graph, "Person D", "Person F");
    addConnection(graph, "Person E", "Person F");
    addConnection(graph, "Person E", "Person G");
    addConnection(graph, "Person F", "Person G");

    // function to print the adjacency list representation of a graph
    printGraph(graph);

    /* Initialising adjacency matrix with values NULL */
    int N = graph->numberOfVertices, i, j;
    int adj_matrix[50][50];
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            adj_matrix[i][j] = 0;
        }
    }

    matrixForm(graph, adj_matrix, N);
    printMatrix(adj_matrix, graph);
    graphDestroy(graph);
    return 0;
}
