#include <stdio.h>
#include <stdlib.h>

typedef int elementType;

typedef struct tagNode {
	elementType Data;
	struct tagNode* nextNode;
	struct tagNode* prevNode;
} Node;
Node* DLL_CreateNode(elementType newData) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->Data = newData;
	newNode->nextNode = NULL;
	newNode->prevNode = NULL;

	return newNode;
}
void DLL_DestroyNode(Node* Node) {
	free(Node);
}
void DLL_AppendNode(Node** Head, Node* newNode) {
	if (*Head == NULL) {
		*Head = newNode;
	}
	else {
		Node* Tail = (*Head);
		while (Tail->nextNode != NULL) {
			Tail = Tail->nextNode;
		}
		Tail->nextNode = newNode;
		newNode->prevNode = Tail;
	}
}
void DLL_RemoveNode(Node** Head, Node* Remove) {
	if (*Head == Remove) {
		*Head = Remove->nextNode;
		if (*Head == NULL) {
			(*Head)->nextNode = NULL;
		}
		Remove->prevNode = NULL;
	}
	else {
		Node* Temp = Remove;

		if (Remove->prevNode != NULL) {
			Remove->prevNode->nextNode = Temp->nextNode;
		}
		if (Remove->nextNode != NULL) {
			Remove->nextNode->prevNode = Temp->prevNode;
		}
		Remove->prevNode = NULL;
		Remove->nextNode = NULL;
	}
}
void DLL_InsertAfter(Node* Current, Node* newNode) {
	newNode->nextNode = Current->nextNode;
	newNode->prevNode = Current;
	Current->nextNode = newNode;
	if (Current->nextNode != NULL) {
		Current->nextNode->prevNode = Current;
	}
}
void DLL_PrintReverse(Node* Head) {

	if (Head == NULL) {
		printf("출력할 것이 없습니다.");
	}
	while (Head->nextNode != NULL) {
		Head = Head->nextNode;
	}
	while (Head != NULL) {
		printf("%d\n", Head->Data);
		Head = Head->prevNode;
	}
}