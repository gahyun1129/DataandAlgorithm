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

typedef enum {
	LEFT_PARENTHESIS = '(', RIGHT_PARENTHESIS = ')',
	PLUS = '+', MINUS = '-',
	MULTIPLY = '*', DIVIDE = '/',
	SPACE = ' ', OPERAND
} SYMBOL;

char NUMBER[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };

int isNumber(char Cipher);
unsigned int getNextToken(char* Expression, char* Token, int* TYPE);
int getPriority(char Operator, int inStack);
int isPrior(char operatorInStack, char operatorInToken);
Node* LLS_createNode(char* newData);
void LLS_destroyNode(Node* _Node);
void LLS_createStack(LinkedListStack** Stack);
void LLS_Push(LinkedListStack* Stack, Node* newNode);
Node* LLS_Pop(LinkedListStack* Stack);
void LLS_destroyStack(LinkedListStack* Stack);
int LLS_isEmpty(LinkedListStack* Stack);
Node* LLS_Top(LinkedListStack* Stack);
void getPostfix(char* infixExpression, char* postfixExpression);


int isNumber(char Cipher) {
	int i = 0;
	int ArrayLength = sizeof(NUMBER);
	for (i = 0; i < ArrayLength; i++) {
		if (Cipher == NUMBER[i]) {
			return 1;
		}
	}
	return 0;
}
unsigned int getNextToken(char* Expression, char* Token, int* TYPE) {
	unsigned int i = 0;
	for (i = 0; 0 != Expression[i]; i++) {
		Token[i] = Expression[i];
		if (isNumber(Expression[i]) == 1) {
			*TYPE = OPERAND;

			if (isNumber(Expression[i + 1]) != 1) {
				break;
			}
		}
		else {
			*TYPE = Expression[i];
			break;
		}
	}
	Token[++i] = '\0';
	return i;
}
int getPriority(char Operator, int inStack) {
	int Priority = -1;
	switch (Operator) {
	case LEFT_PARENTHESIS: {
		if (inStack) Priority = 3;
		else Priority = 0;
		break;
	}
	case MULTIPLY:
	case DIVIDE:
		Priority = 1;
		break;
	case PLUS:
	case MINUS:
		Priority = 2;
		break;
	}
	return Priority;
}
int isPrior(char operatorInStack, char operatorInToken) {
	return (getPriority(operatorInStack, 1) > getPriority(operatorInToken, 0));
}
Node* LLS_createNode(char* newData) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->Data = (char*)malloc(strlen(newData) + 1);

	strcpy(newNode->Data, newData);
	newNode->nextNode = NULL;

	return newNode;
}
void LLS_destroyNode(Node* _Node) {
	free(_Node->Data);
	free(_Node);
}
void LLS_createStack(LinkedListStack** Stack) {
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
void LLS_destroyStack(LinkedListStack* Stack) {
	while (!LLS_isEmpty(Stack)) {
		Node* Popped = LLS_Pop(Stack);
		LLS_DestroyNode(Popped);
	}

	free(Stack);
}
int LLS_isEmpty(LinkedListStack* Stack) {
	return (Stack->List == NULL);
}
Node* LLS_Top(LinkedListStack* Stack) {
	return Stack->Top;
}
void getPostfix(char* infixExpression, char* postfixExpression) {
	LinkedListStack* Stack;

	char Token[32];
	int Type = - 1;
	unsigned int Position = 0;
	unsigned int Length = strlen(infixExpression);

	LLS_createStack(&Stack);

	while (Position < Length) {
		Position += getNextToken(&infixExpression[Position], Token, &Type);
		if (Type == OPERAND) {
			strcat(postfixExpression, Token);
			strcat(postfixExpression, " ");
		}
		else if (Type == RIGHT_PARENTHESIS) {
			while (!LSS_isEmpty(Stack)) {
				Node* Popped = LLS_Pop(Stack);
				if (Popped->Data[0] == LEFT_PARENTHESIS) {
					LLS_destroyNode(Popped);
					break;
				}
				else {
					strcat(postfixExpression, Popped->Data);
					LLS_destroyNode(Popped);
				}
			}
		}
		else {
			while (!LLS_isEmpty(Stack) && !isPrior(LLS_Top(Stack)->Data[0], Token[0])) {
				Node* Popped = LLS_Pop(Stack);

				if (Popped->Data[0] != LEFT_PARENTHESIS) {
					strcat(postfixExpression, Popped->Data);
				}

				LLS_destroyNode(Popped);
			}
			LLS_Push(Stack, LLS_createNode(Token));
		}
	}

	while (!LLS_isEmpty(Stack)) {
		Node* Popped = LLS_Pop(Stack);
		if (Popped->Data[0] != LEFT_PARENTHESIS) {
			strcat(postfixExpression, Popped->Data);
		}

		LLS_destroyNode(Popped);
	}
	LLs_destroyStack(Stack);
}
double Calculate(char* postfixExpression) {
	LinkedListStack* Stack;
	Node* ResultNode;

	double Result;
	char Token[32];
	int Type = -1;
	unsigned int Read = 0;
	unsigned int Length = strlen(postfixExpression);

	LLS_createStack(&Stack);

	while (Read < Length) {

	}
}