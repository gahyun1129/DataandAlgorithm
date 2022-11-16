#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagNode {
	ElementType Data;
	struct tagNode* nextNode;
} Node;

Node* SLL_CreateNode(ElementType NewData) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->Data = NewData;
	newNode->nextNode = NULL;

	return newNode;
}
void SLL_DestroyNode(Node* Node) {
	free(Node);
}
void SLL_AppendNode(Node** Head, Node* newNode) {
	if (*Head == NULL) {
		*Head = newNode;
	}
	else {
		Node* Tail = (*Head);
		while (Tail->nextNode != NULL) {
			Tail = Tail->nextNode;
		}
		Tail->nextNode = newNode;
	}
}
Node* SLL_GetNodeAt(Node* Head, int Location) {
	Node* Current = Head;
	while (Current != NULL && (--Location >= 0)) {
		Current = Current->nextNode;
	}

	return Current;
}
void SLL_RemoveNode(Node** Head, Node* Remove) {
	if (*Head == Remove) {
		*Head = Remove->nextNode;
	}
	else {
		Node* Current = *Head;
		while (Current != NULL && Current->nextNode != Remove) {
			Current = Current->nextNode;
		}
		if (Current != NULL) {
			Current->nextNode = Remove->nextNode;
		}
	}
}
void SLL_InsertAfter(Node* Current, Node* newNode) {
	newNode->nextNode = Current->nextNode;
	Current->nextNode = newNode;
}
int SLL_GetNodeCount(Node* Head) {
	int count = 0;
	Node* Current = Head;
	while (Current != NULL) {
		Current = Current->nextNode;
		count++;
	}
	return count;
}
void SLL_InsertBefore(Node** Head, Node* Current, Node* newNode) {
	if (*Head == Current) {
		newNode->nextNode = *Head;
		*Head = newNode;
	}
	else {
		Node* tmp = *Head;
		while (tmp->nextNode != Current) {
			tmp = tmp->nextNode;
		}
		newNode->nextNode = Current;
		tmp->nextNode = newNode;
	}
}
void SLL_DestroyAllNodes(Node** Head) {
	Node* Current = NULL;
	while (*Head != NULL) {
		Current = *Head;
		Current = Current->nextNode;
		free(*Head);
		*Head = Current;
	}
}
int main() {
	Node* myNode = SLL_CreateNode(117);
	SLL_DestroyNode(myNode);

}