#include "Graph.h"

#define MAX_WEIGHT 36267

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

void Dijkstra(graph* g, vertex* startVertex, graph* shortestPath) {
    int i = 0;
    
    PQNode startNode = { 0, startVertex };
    PriorityQueue* PQ = PQ_Create(10);

    vertex* currentVertex = NULL;
    edge* currentEdge = NULL;

    int* weights = (int*)malloc(sizeof(int) * g->vertexCount);
    vertex** shortestPathVertices = (vertex**)malloc(sizeof(vertex*) * g->vertexCount);
    vertex** fringes = (vertex**)malloc(sizeof(vertex*) * g->vertexCount);
    vertex** precedences = (vertex**)malloc(sizeof(vertex*) * g->vertexCount);

    currentVertex = g->vertices;
    //모든 정점에 경로의 길이를 저장할 곳을 저장하고 길이를 무한대로 초기화.
    while (currentVertex != NULL) {
        vertex* newVertex = createVertex(currentVertex->data);
        addVertex(shortestPath, newVertex);

        fringes[i] = NULL;
        precedences[i] = NULL;
        shortestPathVertices[i] = newVertex;
        weights[i] = MAX_WEIGHT;
        currentVertex = currentVertex->next;
        i++;
    }
    PQ_Enqueue(PQ, startNode);

    weights[startVertex->index] = 0;

    while (!PQ_IsEmpty(PQ)) {
        PQNode Popped;

        PQ_Dequeue(PQ, &Popped);
        currentVertex = (vertex*)Popped.Data;

        fringes[currentVertex->index] = currentVertex;

        currentEdge = currentVertex->adjacencyList;
        while (currentEdge != NULL) {
            vertex* targetVertex = currentEdge->target;

            if (fringes[targetVertex->index] == NULL && weights[currentVertex->index] + currentEdge->weight < weights[currentVertex->index]) {
                PQNode newNode = { currentEdge->weight, targetVertex };
                PQ_Enqueue(PQ, newNode);

                precedences[targetVertex->index] = currentEdge->from;
                weights[targetVertex->index] = weights[currentVertex->index] + currentEdge->weight;
            }
            currentEdge = currentEdge->next;
        }
    }
    for (i = 0; i < g->vertexCount; i++) {
        int fromIndex, toIndex;
        if (precedences[i] == NULL) { continue; }
        fromIndex = precedences[i]->index;
        toIndex = i;
        addEdge(shortestPathVertices[fromIndex], createEdge(shortestPathVertices[fromIndex], shortestPathVertices[toIndex], weights[i]));
    }

    free(fringes);
    free(precedences);
    free(shortestPathVertices);
    free(weights);

    PQ_Destroy(PQ);
}