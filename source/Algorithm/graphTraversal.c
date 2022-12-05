#include "graphTraversal.h"

void DFS(vertex* v)
{
	edge* e = NULL;

	printf("%d", v->data);

	v->visited = visited;

	e = v->adjacencyList;

	while (e != NULL) {
		if (e->target != NULL && e->target->visited == notVisited) {
			DFS(e->target);
		}
		e = e->next;
	}
}

void BFS(vertex* v, LinkedQueue* queue)
{
	edge* e = NULL;
	printf("%d ", v->data);
	v->visited = visited;

	LQ_Enqueue(queue, LQ_CreateNode(v));
	while (!LQ_IsEmpty(queue)) {
		Node* popped = LQ_Dequeue(queue);
		v = popped->Data;
		e = v->adjacencyList;

		while (e != NULL) {
			v = e->target;

			if (v != NULL && v->visited == notVisited) {
				printf("%d ", v->data);
				v->visited = visited;
				LQ_Enqueue(queue, LQ_CreateNode(v));
			}
			e = e->next;
		}
	}
}
