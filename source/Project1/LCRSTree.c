#include <stdio.h>
#include <stdlib.h>

typedef char elementType;

typedef struct tagLCRSNode {
	struct tagLCRSNode* leftChild;
	struct tagLCRSNode* rightSibling;

	elementType data;
} LCRSNode;

LCRSNode* LCRS_createNode(elementType newData) {
	LCRSNode* newNode = (LCRSNode*)malloc(sizeof(LCRSNode));
	newNode->leftChild = NULL;
	newNode->rightSibling = NULL;
	newNode->data = newData;

	return newNode;
}

void LCRS_destroyNode(LCRSNode* Node) {
	free(Node);
}


void LCRS_addChildNode(LCRSNode* parent, LCRSNode* child) {
	if (parent->leftChild == NULL) {
		parent->leftChild = child;
	}
	else {
		LCRSNode* tempNode = parent->leftChild;
		while (tempNode->rightSibling != NULL) {
			tempNode = tempNode->rightSibling;
		}

		tempNode->rightSibling = child;
	}
}

void LCRS_printTree(LCRSNode* Node, int depth) {
	int i = 0;
	for (i = 0; i < depth - 1; i++) {
		printf("   ");
	}
	if (depth > 0) {
		printf("+--");
	}

	printf("%c\n", Node->data);

	if (Node->leftChild != NULL) {
		LCRS_printTree(Node->leftChild, depth + 1);
	}
	if (Node->rightSibling != NULL) {
		LCRS_printTree(Node->rightSibling, depth);
	}
}

void LCRS_printNodesAtLevel(LCRSNode* Node, int currentLevel, int Level) {
	if (currentLevel == Level) {
		printf("%c, ", Node->data);
	}
	if (Node->leftChild != NULL) {
		LCRS_printNodesAtLevel(Node->leftChild, currentLevel+1, Level);
	}
	if (Node->rightSibling != NULL) {
		LCRS_printNodesAtLevel(Node->rightSibling, currentLevel, Level);
	}
}
int main(void)
{
	//  노드 생성 
	LCRSNode* Root = LCRS_createNode('A');

	LCRSNode* B = LCRS_createNode('B');
	LCRSNode* C = LCRS_createNode('C');
	LCRSNode* D = LCRS_createNode('D');
	LCRSNode* E = LCRS_createNode('E');
	LCRSNode* F = LCRS_createNode('F');
	LCRSNode* G = LCRS_createNode('G');
	LCRSNode* H = LCRS_createNode('H');
	LCRSNode* I = LCRS_createNode('I');
	LCRSNode* J = LCRS_createNode('J');
	LCRSNode* K = LCRS_createNode('K');

	//  트리에 노드 추가 
	LCRS_addChildNode(Root, B);
	LCRS_addChildNode(B, C);
	LCRS_addChildNode(B, D);
	LCRS_addChildNode(D, E);
	LCRS_addChildNode(D, F);

	LCRS_addChildNode(Root, G);
	LCRS_addChildNode(G, H);

	LCRS_addChildNode(Root, I);
	LCRS_addChildNode(I, J);
	LCRS_addChildNode(J, K);

	//  트리 출력 
	LCRS_printTree(Root, 0);
	printf("\n");
	LCRS_printNodesAtLevel(Root, 0, 2);

	//  트리 소멸시키기 
	//LCRS_destroyTree(Root);

	return 0;
}