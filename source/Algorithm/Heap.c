#include <stdio.h>
#include <stdlib.h>

typedef int elementType;

typedef struct tagHeapNode {
	elementType data;
} heapNode;

typedef struct tagHeap {
	heapNode* Nodes;
	int capacity;
	int usedSize;
} heap;

void heap_insert(heap* h, elementType newData) {
	int currentPosition = h->usedSize;
	int parentPosition = heap_getParent(currentPosition);

	if (h->usedSize == h->capacity) {
		h->capacity *= 2;
		h->Nodes = (heapNode*)realloc(h->Nodes, sizeof(heapNode) * h->capacity);
	}
	h->Nodes[currentPosition].data = newData;

	while (currentPosition > 0 && h->Nodes[currentPosition].data < h->Nodes[parentPosition].data) {
		heap_swapNodes(h, currentPosition, parentPosition);

		currentPosition = parentPosition;
		parentPosition = heap_getParent(currentPosition);
	}
	h->usedSize++;
}

void heap_deleteMin(heap* h, heapNode* root) {
	int parentPosition = 0, leftPosition = 0, rightPosition = 0;
	memcpy(root, &h->Nodes[0], sizeof(heapNode));
	memset(&h->Nodes[0], 0, sizeof(heapNode));

	h->usedSize--;
	heap_swapNodes(h, 0, h->usedSize); //void swapNodes(heap* h, int index1, int index2);

	leftPosition = heap_getLeftChild(0); //int heap_getLeftChild(int index);
	rightPosition = leftPosition + 1;

	while (1) {
		int selectedChild = 0;

		if (leftPosition >= h->usedSize) {
			break;
		}
		if (rightPosition >= h->usedSize) {
			selectedChild = leftPosition;
		}
		else {
			if (h->Nodes[leftPosition].data > h->Nodes[rightPosition].data) { selectedChild = rightPosition; }
			else { selectedChild = leftPosition; }
		}

		if (h->Nodes[selectedChild].data < h->Nodes[parentPosition].data) {
			heap_swapNodes(h, parentPosition, selectedChild);
			parentPosition = selectedChild;
		}
		else { break; }
		leftPosition = heap_getLeftChild(parentPosition);
		rightPosition = leftPosition + 1;
	}
	if (h->usedSize < (h->capacity / 2)) {
		h->capacity /= 2;
		h->Nodes = (heapNode*)realloc(h->Nodes, sizeof(heapNode) * h->capacity);
	}
}