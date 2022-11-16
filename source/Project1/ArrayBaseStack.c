#include <stdio.h>
#include <stdlib.h>

typedef int elementType;

typedef struct tagNode {
	elementType Data;
} Node;

typedef struct tagArrayStack {
	int Capacity;		//용량
	int Top;			//최상위 노드의 위치
	Node* Nodes;		//자유 저장소에 할당한 배열의 첫 번째 요소를 가리킴.
} ArrayStack;

void AS_CreateStack(ArrayStack** Stack, int Capacity) {
	//자유 저장소에 스택 생성
	(*Stack) = (ArrayStack*)malloc(sizeof(ArrayStack));
	//자유 저장소에 배열 생성
	(*Stack)->Nodes = (Node*)malloc(sizeof(Node) * Capacity);
	//capacity, top 초기화
	(*Stack)->Capacity = Capacity;
	(*Stack)->Top = -1;
}

void AS_DestroyStack(ArrayStack* Stack) {
	free(Stack->Nodes);
	free(Stack);
}

void AS_Push(ArrayStack* Stack, elementType Data) {
	Stack->Top++;
	Stack->Nodes[Stack->Top].Data = Data;
}

elementType AS_Pop(ArrayStack* Stack) {
	int position = Stack->Top--;
	return Stack->Nodes[position].Data;
}

int AS_GetSize(ArrayStack* Stack) {
	return Stack->Top + 1;
}

int AS_IsEmpty(ArrayStack* Stack) {
	return (Stack->Top == -1);
}

int AS_IsFull(ArrayStack* Stack) {
	return (Stack->Top + 2 == Stack->Capacity);
}