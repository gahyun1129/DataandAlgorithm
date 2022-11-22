#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode {
	char* Data;
	struct tagNode* nextNode;
} Node;

typedef struct taglinkedQueue {
	Node* front;
	Node* rear;
	int count;
} linkedQueue;

void LQ_createQueue(linkedQueue** queue) {
	(*queue) = (linkedQueue*)malloc(sizeof(linkedQueue));
	(*queue)->front = NULL;
	(*queue)->rear = NULL;
	(*queue)->count = 0;
}

void LQ_destroyQueue(linkedQueue* queue) {
	while (!LQ_isEmpty(queue)) {
		Node* popped = LQ_Dequeue(queue);
		LQ_destroyNode(popped);
	}

	free(queue);
}

void LQ_Enqueue(linkedQueue* queue, Node* newNode) {
	if (queue->front == NULL) {
		queue->front = newNode;
		queue->rear = newNode;
		queue->count++;
	}
	else {
		queue->rear->nextNode = newNode;
		queue->rear = newNode;
		queue->count++;
	}
}

Node* LQ_Dequeue(linkedQueue* queue) {
	Node* front = queue->front;

	if (queue->front->nextNode == NULL) {
		queue->front = NULL;
		queue->rear = NULL;
	}
	else {
		queue->front = queue->front->nextNode;
	}

	queue->count--;
	return front;
}
int LQ_isEmpty(linkedQueue* queue) {
	return (queue->front == NULL);
}