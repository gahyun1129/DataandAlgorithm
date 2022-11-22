#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tagNode
{
    char* Data;
    struct tagNode* NextNode;
} Node;

typedef struct tagLinkedListStack
{
    Node* List;
    Node* Top;
} LinkedListStack;

typedef enum
{
    LEFT_PARENTHESIS = '(', RIGHT_PARENTHESIS = ')',
    PLUS = '+', MINUS = '-',
    MULTIPLY = '*', DIVIDE = '/',
    SPACE = ' ', OPERAND
} SYMBOL;

char NUMBER[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };

int          IsNumber(char Cipher);
unsigned int GetNextToken(char* Expression, char* Token, int* TYPE);
int          IsPrior(char Operator1, char Operator2);
void         GetPostfix(char* InfixExpression, char* PostfixExpression);
double       Calculate(char* PostfixExpression);
void  LLS_CreateStack(LinkedListStack** Stack);
void  LLS_DestroyStack(LinkedListStack* Stack);

Node* LLS_CreateNode(char* Data);
void  LLS_DestroyNode(Node* _Node);

void  LLS_Push(LinkedListStack* Stack, Node* NewNode);
Node* LLS_Pop(LinkedListStack* Stack);

Node* LLS_Top(LinkedListStack* Stack);
int   LLS_GetSize(LinkedListStack* Stack);
int   LLS_IsEmpty(LinkedListStack* Stack);


int main(void)
{
    char InfixExpression[100];
    char PostfixExpression[100];

    double Result = 0.0;

    memset(InfixExpression, 0, sizeof(InfixExpression));
    memset(PostfixExpression, 0, sizeof(PostfixExpression));

    printf("Enter Infix Expression:");
    scanf("%s", InfixExpression);

    GetPostfix(InfixExpression, PostfixExpression);

    printf("Infix:%s\nPostfix:%s\n",
        InfixExpression,
        PostfixExpression);

    Result = Calculate(PostfixExpression);

    printf("Calculation Result : %f\n", Result);

    return 0;
}


void  LLS_CreateStack(LinkedListStack** Stack)
{
    //  ������ ���� ����ҿ� ���� 
    (*Stack) = (LinkedListStack*)malloc(sizeof(LinkedListStack));
    (*Stack)->List = NULL;
    (*Stack)->Top = NULL;
}

void LLS_DestroyStack(LinkedListStack* Stack)
{
    while (!LLS_IsEmpty(Stack))
    {
        Node* Popped = LLS_Pop(Stack);
        LLS_DestroyNode(Popped);
    }

    //  ������ ���� ����ҿ��� ���� 
    free(Stack);
}

Node* LLS_CreateNode(char* NewData)
{
    Node* NewNode = (Node*)malloc(sizeof(Node));
    NewNode->Data = (char*)malloc(strlen(NewData) + 1);

    strcpy(NewNode->Data, NewData);  //  �����͸� �����Ѵ�. 

    NewNode->NextNode = NULL; //  ���� ��忡 ���� �����ʹ� NULL�� �ʱ�ȭ�Ѵ�. 

    return NewNode;//  ����� �ּҸ� ��ȯ�Ѵ�. 
}

void  LLS_DestroyNode(Node* _Node)
{
    free(_Node->Data);
    free(_Node);
}

void LLS_Push(LinkedListStack* Stack, Node* NewNode)
{
    if (Stack->List == NULL)
    {
        Stack->List = NewNode;
    }
    else
    {
        //  ������ Top�� �ű� ��带 �����Ѵ�.
        Stack->Top->NextNode = NewNode;
    }

    //  ������ Top �ʵ忡 �� ����� �ּҸ� ����Ѵ�. 
    Stack->Top = NewNode;
}

Node* LLS_Pop(LinkedListStack* Stack)
{
    //  LLS_Pop() �Լ��� ��ȯ�� �ֻ��� ��� ���� 
    Node* TopNode = Stack->Top;


    if (Stack->List == Stack->Top)
    {
        Stack->List = NULL;
        Stack->Top = NULL;
    }
    else
    {
        // Top �Ʒ��� �ִ� ��带 ���ο� CurrentTop�� ���� 
        Node* CurrentTop = Stack->List;
        while (CurrentTop != NULL && CurrentTop->NextNode != Stack->Top)
        {
            CurrentTop = CurrentTop->NextNode;
        }

        // CurrentTop�� Top�� ����
        Stack->Top = CurrentTop;
        Stack->Top->NextNode = NULL;
    }

    return TopNode;
}

Node* LLS_Top(LinkedListStack* Stack)
{
    return Stack->Top;
}

int LLS_GetSize(LinkedListStack* Stack)
{
    int    Count = 0;
    Node* Current = Stack->List;

    while (Current != NULL)
    {
        Current = Current->NextNode;
        Count++;
    }

    return Count;
}

int LLS_IsEmpty(LinkedListStack* Stack)
{
    return (Stack->List == NULL);
}

int IsNumber(char Cipher)
{   //�������� �Ǻ��ϴ� �Լ�. ���� ���ڶ�� 1, �ƴ϶�� 0�� ��ȯ��.
    int i = 0;
    int ArrayLength = sizeof(NUMBER);

    for (i = 0; i < ArrayLength; i++)
    {
        if (Cipher == NUMBER[i])
            return 1;
    }

    return 0;
}

unsigned int GetNextToken(char* Expression, char* Token, int* TYPE)
{   //
    unsigned int i = 0;

    for (i = 0; 0 != Expression[i]; i++)
    {   //ǥ������ ������ �д� �ݺ���.
        Token[i] = Expression[i];

        if (IsNumber(Expression[i]) == 1)
        {
            *TYPE = OPERAND;    //�ǿ�����

            if (IsNumber(Expression[i + 1]) != 1)
                break;
        }
        else
        {
            *TYPE = Expression[i];
            break;
        }
    }

    Token[++i] = '\0';
    return i;
}

int GetPriority(char Operator, int InStack)
{   //�켱���� ���ϴ� �Լ�. ���� �������� �켱������ ����.
    int Priority = -1;

    switch (Operator)
    {
    case LEFT_PARENTHESIS:
        if (InStack)
            Priority = 3;
        else
            Priority = 0;
        break;

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

int IsPrior(char OperatorInStack, char OperatorInToken)
{   //�켱������ ���ϴ� �Լ�. ������ ���� ���� ũ�ٸ� ��. �ƴ϶�� ����.
    return (GetPriority(OperatorInStack, 1) > GetPriority(OperatorInToken, 0));
}

void GetPostfix(char* InfixExpression, char* PostfixExpression)
{
    LinkedListStack* Stack;

    char Token[32];
    int  Type = -1;
    unsigned int Position = 0;
    unsigned int Length = strlen(InfixExpression);

    LLS_CreateStack(&Stack);

    while (Position < Length)
    {
        Position += GetNextToken(&InfixExpression[Position], Token, &Type);

        if (Type == OPERAND)
        {
            strcat(PostfixExpression, Token);
            strcat(PostfixExpression, " ");
        }
        else if (Type == RIGHT_PARENTHESIS)
        {
            while (!LLS_IsEmpty(Stack))
            {
                Node* Popped = LLS_Pop(Stack);

                if (Popped->Data[0] == LEFT_PARENTHESIS)
                {
                    LLS_DestroyNode(Popped);
                    break;
                }
                else
                {
                    strcat(PostfixExpression, Popped->Data);
                    LLS_DestroyNode(Popped);
                }
            }
        }
        else
        {
            while (!LLS_IsEmpty(Stack) &&
                !IsPrior(LLS_Top(Stack)->Data[0], Token[0]))
            {
                Node* Popped = LLS_Pop(Stack);

                if (Popped->Data[0] != LEFT_PARENTHESIS)
                    strcat(PostfixExpression, Popped->Data);

                LLS_DestroyNode(Popped);
            }

            LLS_Push(Stack, LLS_CreateNode(Token));
        }
    }

    while (!LLS_IsEmpty(Stack))
    {
        Node* Popped = LLS_Pop(Stack);

        if (Popped->Data[0] != LEFT_PARENTHESIS)
            strcat(PostfixExpression, Popped->Data);

        LLS_DestroyNode(Popped);
    }

    LLS_DestroyStack(Stack);
}

double Calculate(char* PostfixExpression)
{
    LinkedListStack* Stack;
    Node* ResultNode;

    double Result;
    char Token[32];
    int  Type = -1;
    unsigned int Read = 0;
    unsigned int Length = strlen(PostfixExpression);

    LLS_CreateStack(&Stack);

    while (Read < Length)
    {
        Read += GetNextToken(&PostfixExpression[Read], Token, &Type);

        if (Type == SPACE)
            continue;

        if (Type == OPERAND)
        {
            Node* NewNode = LLS_CreateNode(Token);
            LLS_Push(Stack, NewNode);
        }
        else
        {
            char   ResultString[32];
            double Operator1, Operator2, TempResult;
            Node* OperatorNode;

            OperatorNode = LLS_Pop(Stack);
            Operator2 = atof(OperatorNode->Data);
            LLS_DestroyNode(OperatorNode);

            OperatorNode = LLS_Pop(Stack);
            Operator1 = atof(OperatorNode->Data);
            LLS_DestroyNode(OperatorNode);

            switch (Type)
            {
            case PLUS:     TempResult = Operator1 + Operator2; break;
            case MINUS:    TempResult = Operator1 - Operator2; break;
            case MULTIPLY: TempResult = Operator1 * Operator2; break;
            case DIVIDE:   TempResult = Operator1 / Operator2; break;
            }

            gcvt(TempResult, 10, ResultString);
            LLS_Push(Stack, LLS_CreateNode(ResultString));
        }
    }

    ResultNode = LLS_Pop(Stack);
    Result = atof(ResultNode->Data);
    LLS_DestroyNode(ResultNode);

    LLS_DestroyStack(Stack);

    return Result;
}
