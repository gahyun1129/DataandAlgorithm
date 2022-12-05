#include "Graph.h"

graph* createGraph()
{
	graph* g = (graph*)malloc(sizeof(graph));
	g->vertices = NULL;
	g->vertexCount = 0;

	return g;
}

void destroyGraph(graph* g)
{
	while (g->vertices != NULL) {
		vertex* vertices = g->vertices->next;
		destroyVertex(g->vertices);
		g->vertices = vertices;
	}

	free(g);
}

vertex* createVertex(vElementType data)
{
	vertex* v = (vertex*)malloc(sizeof(vertex));

	v->data = data;
	v->next = NULL;
	v->adjacencyList = NULL;
	v->visited = notVisited;
	v->index = -1;

	return v;
}

void destroyVertex(vertex* v)
{
	while (v->adjacencyList != NULL) {
		edge* e = v->adjacencyList->next;
		destroyEdge(v->adjacencyList);
		v->adjacencyList = e;
	}

	free(v);
}

edge* createEdge(vertex* from, vertex* target, int weight)
{
	edge* e = (edge*)malloc(sizeof(edge));
	e->from = from;
	e->target = target;
	e->weight = weight;
	e->next = NULL;

	return e;
}

void destroyEdge(edge* e)
{
	free(e);
}

void addVertex(graph* g, vertex* v)
{
	vertex* vertexList = g->vertices;
	if (vertexList == NULL) {
		g->vertices = v;
	}
	else {
		while (vertexList->next != NULL) {
			vertexList = vertexList->next;
		}
		vertexList->next = v;
	}
	
	v->index = g->vertexCount++;
}

void addEdge(vertex* v, edge* e)
{
	if (v->adjacencyList == NULL) {
		v->adjacencyList = e;
	}
	else {
		edge* adjacencyList = v->adjacencyList;
		while (adjacencyList->next != NULL) {
			adjacencyList = adjacencyList->next;
		}
		adjacencyList->next = e;
	}
}

void printGraph(graph* g)
{
	vertex* v = NULL;
	edge* e = NULL;

	if ((v = g->vertices) == NULL) { return; }
	while (v != NULL) {
		printf("%c : ", v->data);

		if ((e = v->adjacencyList) == NULL) {
			v = v->next;
			printf("\n");
			continue;
		}
		while (e != NULL) {
			printf("%c[%d] ", e->target->data, e->weight);
			e = e->next;
		}
		printf("\n");

		v = v->next;
	}
	printf("\n");
}
