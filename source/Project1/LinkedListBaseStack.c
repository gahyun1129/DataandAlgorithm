#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tagNode {
	char* Data;
	struct tagNode* nextNode;
} Node;

typedef struct tagLinkedListStack {
	Node* Top;		//최상위 노드의 위치
	Node* List;		//연결리스트
} LinkedListStack;

Node* LLS_CreateNode(char* newData) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->Data = (char*)malloc(strlen(newData)+1);

	strcpy(newNode->Data, newData);
	newNode->nextNode = NULL;

	return newNode;
}
void LLS_DestroyNode(Node* _Node) {
	free(_Node->Data);
	free(_Node);
}

void LLS_CreateStack(LinkedListStack** Stack) {
	*Stack = (LinkedListStack*)malloc(sizeof(LinkedListStack));
	(*Stack)->List = NULL;
	(*Stack)->Top = NULL;
}
void LLS_Push(LinkedListStack* Stack, Node* newNode) {
	if (Stack->List == NULL) {
		Stack->List = newNode;
	}
	else {
		Stack->Top->nextNode = newNode;
	}
	Stack->Top = newNode;
}
Node* LLS_Pop(LinkedListStack* Stack) {
	Node* topNode = Stack->Top;
	if (Stack->List == Stack->Top) {
		Stack->List = NULL;
		Stack->Top = NULL;
	}
	else {
		Node* CurrentTop = Stack->List;
		while (CurrentTop != NULL && CurrentTop->nextNode != Stack->Top) {
			CurrentTop = CurrentTop->nextNode;
		}
		Stack->Top = CurrentTop;
		Stack->Top->nextNode = NULL;
	}
	return topNode;
}
void LLS_DestroyStack(LinkedListStack* Stack) {
	while (!LLS_IsEmpty(Stack)) {
		Node* Popped = LLS_Pop(Stack);
		LLS_DestroyNode(Popped);
	}

	free(Stack);
}