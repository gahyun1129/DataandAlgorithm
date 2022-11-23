#include <stdio.h>
#include <stdlib.h>

typedef char elementType;
typedef struct tagSBTNode {
	struct tagSBTNode* left;
	struct tagSBTNode* right;

	elementType data;
} SBTNode;

SBTNode* SBT_createNode(elementType newData) {
	SBTNode* newNode = (SBTNode*)malloc(sizeof(SBTNode));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = newData;

	return newNode;
}

void SBT_destroyNode(SBTNode* Node) {
	free(Node);
}

void SBT_preorderPrintTree(SBTNode* Node) {
	if (Node == NULL) {
		return;
	}
	printf(" %c", Node->data);
	SBT_preorderPrintTree(Node->left);
	SBT_preorderPrintTree(Node->right);
}

void SBT_inorderPrintTree(SBTNode* Node) {
	if (Node == NULL) {
		return;
	}
	SBT_inorderPrintTree(Node->left);
	printf(" %c", Node->data);
	SBT_inorderPrintTree(Node->right);
}

void SBT_postorderPrintTree(SBTNode* Node) {
	if (Node == NULL) {
		return;
	}
	SBT_postorderPrintTree(Node->left);
	SBT_postorderPrintTree(Node->right);
	printf(" %c", Node->data);
}

void SBT_destroyTree(SBTNode* Node) {
	if (Node == NULL) {
		return;
	}
	SBT_destroyTree(Node->left);
	SBT_destroyTree(Node->right);
	SBT_destroyNode(Node);
}

int main() {
	return 0;
}