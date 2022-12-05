#include "Graph.h"
#include "graphTraversal.h"

int main(void)
{
    int          Mode = 0;
    graph* graph = createGraph();

    vertex* V1 = createVertex(1);
    vertex* V2 = createVertex(2);
    vertex* V3 = createVertex(3);
    vertex* V4 = createVertex(4);
    vertex* V5 = createVertex(5);
    vertex* V6 = createVertex(6);
    vertex* V7 = createVertex(7);

    addVertex(graph, V1);
    addVertex(graph, V2);
    addVertex(graph, V3);
    addVertex(graph, V4);
    addVertex(graph, V5);
    addVertex(graph, V6);
    addVertex(graph, V7);

    //  정점과 정점을 간선으로 잇기 
    addEdge(V1, createEdge(V1, V2, 0));
    addEdge(V1, createEdge(V1, V3, 0));

    addEdge(V2, createEdge(V2, V4, 0));
    addEdge(V2, createEdge(V2, V5, 0));

    addEdge(V3, createEdge(V3, V4, 0));
    addEdge(V3, createEdge(V3, V6, 0));

    addEdge(V4, createEdge(V4, V5, 0));
    addEdge(V4, createEdge(V4, V7, 0));

    addEdge(V5, createEdge(V5, V7, 0));

    addEdge(V6, createEdge(V6, V7, 0));

    printf("Enter Traversal Mode (0:DFS, 1:BFS) : ");
    scanf("%d", &Mode);

    if (Mode == 0)
    {
        //  깊이 우선 탐색 
        DFS(graph->vertices);
    }
    else
    {
        LinkedQueue* Queue = NULL;
        LQ_CreateQueue(&Queue);

        //  너비 우선 탐색 
        BFS(V1, Queue);

        LQ_DestroyQueue(Queue);
    }

    destroyGraph(graph);

    return 0;
}
