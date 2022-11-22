#include <stdio.h>
#include <stdlib.h>

typedef int elementType;

typedef struct tagNode {
	elementType data;
} Node;

typedef struct tagCircularQueue {
	int capacity;
	int front;
	int rear;

	Node* nodes;
} circularQueue;

void CQ_createQueue(circularQueue** queue, int capacity) {
	(*queue) = (circularQueue*)malloc(sizeof(circularQueue));

	(*queue)->nodes = (Node*)malloc(sizeof(Node) * (capacity + 1));	//공백/포화 상태 구분을 위해 1만큼 크기를 더 할당함.

	(*queue)->capacity = capacity;
	(*queue)->front = 0;
	(*queue)->rear = 0;
}

void CQ_destroyQueue(circularQueue* queue) {
	free(queue->nodes);
	free(queue);
}

void CQ_Enqueue(circularQueue* queue, elementType data) {
	int position = 0;
	if (queue->rear == queue->capacity) {
		position = queue->rear;
		queue->rear = 0;
	}
	else {
		position = queue->rear++;
	}

	queue->nodes[position].data = data;
}

void CQ_Dequeue(circularQueue* queue) {
	int position = queue->front;

	if (queue->front == queue->capacity) {
		queue->front = 0;
	}
	else {
		queue->front++;
	}
	return queue->nodes[position].data;
}

int CQ_isEmpty(circularQueue* queue) {
	return (queue->front == queue->rear);
}

int CQ_isFull(circularQueue* queue) {
	if (queue->front < queue->rear) { return (queue->rear - queue->front) == queue->capacity; }
	else { return (queue->rear + 1) == queue->front; }
}