#include <stdio.h>
#include <stdlib.h>

typedef int elementType;

typedef struct tagNode {
	elementType Data;
	struct tagNode* nextNode;
	struct tagNode* prevNode;
} Node;
void CDLL_AppendNode(Node** Head, Node* newNode) {
	if (*Head == NULL) {
		*Head = newNode;
		(*Head)->nextNode = *Head;
		(*Head)->prevNode = *Head;
	}
	else {
		Node* Tail = (*Head)->prevNode;
		Tail->nextNode->prevNode = newNode;
		Tail->nextNode = newNode;

		newNode->prevNode = Tail;
		newNode->nextNode = *Head;
	}
}
void CDLL_RemoveNode(Node** Head, Node* Remove) {
	if (*Head == Remove) {
		(*Head)->nextNode->prevNode = Remove->prevNode;
		(*Head)->prevNode->nextNode = Remove->nextNode;

		(*Head) = Remove->nextNode;

		Remove->nextNode = NULL;
		Remove->prevNode = NULL;
	}
	else {
		Remove->nextNode->prevNode = Remove->prevNode;
		Remove->prevNode->nextNode = Remove->nextNode;

		Remove->nextNode = NULL;
		Remove->prevNode = NULL;
	}
}