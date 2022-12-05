#ifndef GRAPH_H
#define GRAPH_H


#include <stdio.h>
#include <stdlib.h>


enum visitMode {visited, notVisited};//�湮 ����

typedef int vElementType;

typedef struct tagVertex {
	vElementType data;				//�ڷ�
	int visited;					//�湮 ����
	int index;						//������ �ε���_�ִ� ��� Ž�� �˰��򿡼� �����.

	struct tagVertex* next;			//���� ����
	struct tagEdge* adjacencyList;	//���� ����Ʈ_edge ����ü�� next �����͸� �̿��� ������.
} vertex;

typedef struct tagEdge {
	int weight;						//����ġ_�ּ� ���� Ʈ��, �ִ� ��� Ž�� �˰��򿡼� �����.
	struct tagEdge* next;			//���� ����_vertex�� adjacencyList ������ ���.
	vertex* from;					//������ ���� ����
	vertex* target;					//������ �� ����
} edge;

typedef struct tagGraph {
	vertex* vertices;				//���� ���
	int vertexCount;				//������ ��
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