#include "Graph.h"

void topologicalSort(vertex* v, Node** list) {
	while (v != NULL && v->visited == notVisited) {
		TS_DFS(v, list);
		v = v->next;
	}
}

void TS_DFS(vertex* v, Node** list) {
	Node* newHead = NULL;
	edge* e = NULL;

	v->visited = visited;

	e = v->adjacencyList;

	while (e != NULL) {
		if (e->target != NULL && e->target->visited == notVisited) {
			TS_DFS(e->target, list);
		}
		e = e->next;
	}

	printf("%c\n", v->data);

	newHead = SLL_createNode(v);
	SLL_insertNewHead(list, newHead);
}