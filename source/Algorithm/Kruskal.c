#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct tagDisjointSet
{
    struct tagDisjointSet* Parent;
    void* Data;
} DisjointSet;

void DS_UnionSet(DisjointSet* Set1, DisjointSet* Set2);
DisjointSet* DS_FindSet(DisjointSet* Set);
DisjointSet* DS_MakeSet(void* NewData);
void DS_DestroySet(DisjointSet* Set);

typedef int       PriorityType;

typedef struct tagePQNode
{
    PriorityType Priority;
    void* Data;
} PQNode;

typedef struct tagPriorityQueue
{
    PQNode* Nodes;
    int Capacity;
    int UsedSize;
} PriorityQueue;

PriorityQueue* PQ_Create(int InitialSize);
void           PQ_Destroy(PriorityQueue* PQ);
void           PQ_Enqueue(PriorityQueue* PQ, PQNode NewData);
void           PQ_Dequeue(PriorityQueue* PQ, PQNode* Root);
int            PQ_GetParent(int Index);
int            PQ_GetLeftChild(int Index);
void           PQ_SwapNodes(PriorityQueue* PQ, int Index1, int Index2);
int            PQ_IsEmpty(PriorityQueue* PQ);
void kruskal(graph* g, graph* MST) {
    int i;
    vertex* currentVertex = NULL;
    vertex** MSTvertices = (vertex**)malloc(sizeof(vertex*) * g->vertexCount);
    DisjointSet** vertexSet = (DisjointSet**)malloc(sizeof(DisjointSet*) * g->vertexCount);
    PriorityQueue* PQ = PQ_Create(10);

    i = 0;
    currentVertex = g->vertices;
    while (currentVertex != NULL) {
        edge* currentEdge;
        vertexSet[i] = DS_MakeSet(currentVertex);
        MSTvertices[i] = createVertex(currentVertex->data);
        addVertex(MST, MSTvertices[i]);

        currentEdge = currentVertex->adjacencyList;
        while (currentEdge != NULL) {
            PQNode newNode = { currentEdge->weight, currentEdge };
            PQ_Enqueue(PQ, newNode);

            currentEdge = currentEdge->next;
        }
        currentVertex = currentVertex->next;
        i++;
    }
    while (!PQ_IsEmpty(PQ)) {
        edge* currentEdge;
        int fromIndex;
        int toIndex;
        PQNode Popped;

        PQ_Dequeue(PQ, &Popped);
        currentEdge = (edge*)Popped.Data;

        printf("%c-%c : %d\n", currentEdge->from->data, currentEdge->target->data, currentEdge->weight);
        fromIndex = currentEdge->from->index;
        toIndex = currentEdge->target->index;

        if (DS_FindSet(vertexSet[fromIndex]) != DS_FindSet(vertexSet[toIndex])) {
            addEdge(MSTvertices[fromIndex], createEdge(MSTvertices[fromIndex], MSTvertices[toIndex], currentEdge->weight));
            addEdge(MSTvertices[toIndex], createEdge(MSTvertices[toIndex], MSTvertices[fromIndex], currentEdge->weight));
            DS_UnionSet(vertexSet[fromIndex], vertexSet[toIndex]);
        }
    }
    for (i = 0; i < g->vertexCount; i++) {
        DS_DestroySet(vertexSet[i]);
    }
    free(vertexSet);
    free(MSTvertices);
}