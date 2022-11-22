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

LCRSNode* LCRS_destroyNode(LCRSNode* Node) {
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