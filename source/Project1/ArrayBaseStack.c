#include <stdio.h>
#include <stdlib.h>

typedef int elementType;

typedef struct tagNode {
	elementType Data;
} Node;

typedef struct tagArrayStack {
	int Capacity;		//�뷮
	int Top;			//�ֻ��� ����� ��ġ
	Node* Nodes;		//���� ����ҿ� �Ҵ��� �迭�� ù ��° ��Ҹ� ����Ŵ.
} ArrayStack;

void AS_CreateStack(ArrayStack** Stack, int Capacity) {
	//���� ����ҿ� ���� ����
	(*Stack) = (ArrayStack*)malloc(sizeof(ArrayStack));
	//���� ����ҿ� �迭 ����
	(*Stack)->Nodes = (Node*)malloc(sizeof(Node) * Capacity);
	//capacity, top �ʱ�ȭ
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