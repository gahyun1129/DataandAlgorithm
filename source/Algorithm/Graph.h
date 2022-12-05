#ifndef GRAPH_H
#define GRAPH_H


#include <stdio.h>
#include <stdlib.h>


enum visitMode {visited, notVisited};//방문 여부

typedef int vElementType;

typedef struct tagVertex {
	vElementType data;				//자료
	int visited;					//방문 여부
	int index;						//정점의 인덱스_최단 경로 탐색 알고리즘에서 사용함.

	struct tagVertex* next;			//다음 정점
	struct tagEdge* adjacencyList;	//인접 리스트_edge 구조체의 next 포인터를 이용해 구성됨.
} vertex;

typedef struct tagEdge {
	int weight;						//가중치_최소 신장 트리, 최단 경로 탐색 알고리즘에서 사용함.
	struct tagEdge* next;			//다음 간선_vertex의 adjacencyList 구성에 사용.
	vertex* from;					//간선의 시작 정점
	vertex* target;					//간선의 끝 정점
} edge;

typedef struct tagGraph {
	vertex* vertices;				//정점 목록
	int vertexCount;				//정점의 수
} graph;

graph* createGraph();
void destroyGraph(graph* g);

vertex* createVertex(vElementType data);
void destroyVertex(vertex* v);

edge* createEdge(vertex* from, vertex* target, int weight);
void destroyEdge(edge* e);

void addVertex(graph* g, vertex* v);
void addEdge(vertex* v, edge* e);
void printGraph(graph* g);


#endif