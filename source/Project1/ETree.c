#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char elementType;
typedef struct tagETNode {
	struct tagETNode* left;
	struct tagETNode* right;

	elementType data;
} ETNode;

ETNode* ET_createNode(elementType newData) {
	ETNode* newNode = (ETNode*)malloc(sizeof(ETNode));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->data = newData;

	return newNode;
}

void ET_destroyNode(ETNode* Node) {
	free(Node);
}

void ET_preorderPrintTree(ETNode* Node) {
	if (Node == NULL) {
		return;
	}
	printf(" %c", Node->data);
	ET_preorderPrintTree(Node->left);
	ET_preorderPrintTree(Node->right);
}

void ET_inorderPrintTree(ETNode* Node) {
	if (Node == NULL) {
		return;
	}
	ET_inorderPrintTree(Node->left);
	printf(" %c", Node->data);
	ET_inorderPrintTree(Node->right);
}

void ET_postorderPrintTree(ETNode* Node) {
	if (Node == NULL) {
		return;
	}
	ET_postorderPrintTree(Node->left);
	ET_postorderPrintTree(Node->right);
	printf(" %c", Node->data);
}

void ET_destroyTree(ETNode* Node) {
	if (Node == NULL) {
		return;
	}
	ET_destroyTree(Node->left);
	ET_destroyTree(Node->right);
	ET_destroyNode(Node);
}

void ET_buildExpressionTree(char* PostfixExpression, ETNode** Node) {
	int len = strlen(PostfixExpression);
	char token = PostfixExpression[len - 1];
	PostfixExpression[len - 1] = '\0';

	switch (token)
	{
	case '+': case '-': case '*': case'/': {
		(*Node) = ET_createNode(token);
		ET_buildExpressionTree(PostfixExpression, &(*Node)->right);
		ET_buildExpressionTree(PostfixExpression, &(*Node)->left);
		break;
	}
	default: (*Node) = ET_createNode(token);
		break;
	}
}

double ET_evaluate(ETNode* Tree) {
	char Temp[2];

	double left = 0;
	double right = 0;
	double result = 0;

	if (Tree == NULL) {
		return 0;
	}
	switch (Tree->data)
	{
		case '+': case '-': case '*': case'/': {
			left = ET_evaluate(Tree->left);
			right = ET_evaluate(Tree->right);

			if (Tree->data == '+') result = left + right;
			else if (Tree->data == '-') result = left - right;
			else if (Tree->data == '*') result = left * right;
			else if (Tree->data == '/') result = left / right;
			
			break;
		}
		default: {
			memset(Temp, 0, sizeof(Temp));
			Temp[0] = Tree->data;
			result = atof(Temp);
			break;
		}
	}
	return result;
}

int main() {

}
