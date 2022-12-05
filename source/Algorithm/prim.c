#include "Graph.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

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

void Prim(graph* g, vertex* startVertex, graph* MST)
{
    int i = 0;

    PQNode StartNode = { 0, startVertex };
    PriorityQueue* PQ = PQ_Create(10);
    
    vertex* currentVertex = NULL;
    edge* currentEdge = NULL;

    int* weights = (int*)malloc(sizeof(int) * g->vertexCount);
    vertex** MSTVertieces = (vertex**)malloc(sizeof(vertex*) * g->vertexCount);
    vertex** Fringes = (vertex**)malloc(sizeof(vertex*) * g->vertexCount);
    vertex** Precedences = (vertex**)malloc(sizeof(vertex*) * g->vertexCount);

    currentVertex = g->vertices;
    while (currentVertex != NULL) {
        vertex* newVertex = createVertex(currentVertex->data);
        addVertex(MST, newVertex);

        Fringes[i] = NULL;
        Precedences[i] = NULL;
        MSTVertieces[i] = newVertex;
        weights[i] = MAX_WEIGHT;
        currentVertex = currentVertex->next;
        i++;
    }

    PQ_Enqueue(PQ, StartNode);
    weights[startVertex->index] = 0;

    while (!PQ_IsEmpty(PQ)) {
        PQNode Popped;

        PQ_Dequeue(PQ, &Popped);
        currentVertex = (vertex*)Popped.Data;

        Fringes[currentVertex->index] = currentVertex;

        currentEdge = currentVertex->adjacencyList;
        while (currentEdge != NULL) {
            vertex* targetVertex = currentEdge->target;

            if (Fringes[targetVertex->index] == NULL && currentEdge->weight < weights[targetVertex->index]) {
                PQNode newNode = { currentEdge->weight, targetVertex };
                PQ_Enqueue(PQ, newNode);

                Precedences[targetVertex->index] = currentEdge->from;
                weights[targetVertex->index] = currentEdge->weight;
            }
            currentEdge = currentEdge->next;
        }
    }
    for (i = 0; i < g->vertexCount; i++) {
        int fromIndex, toIndex;
        if (Precedences[i] == NULL) {
            continue;
        }
        fromIndex = Precedences[i]->index;
        toIndex = i;

        addEdge(MSTVertieces[fromIndex], createEdge(MSTVertieces[fromIndex], MSTVertieces[toIndex], weights[i]));
        addEdge(MSTVertieces[toIndex], createEdge(MSTVertieces[toIndex], MSTVertieces[fromIndex], weights[i]));

    }

    free(Fringes);
    free(Precedences);
    free(MSTVertieces);
    free(weights);

    PQ_Destroy(PQ);
}