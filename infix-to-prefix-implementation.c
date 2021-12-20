#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Stack {
    int Top;
    unsigned Capacity;
    int* Array;
};

struct Stack* createStack(unsigned Capacity)
{
    struct Stack* Stack = (struct Stack*)malloc(sizeof(struct Stack));
    Stack->Capacity = Capacity;
    Stack->Top = -1;
    Stack->Array = (int*)malloc(Stack->Capacity * sizeof(int));
    return Stack;
}

int isFull(struct Stack* Stack)
{
    return Stack->Top == Stack->Capacity - 1;
}

int isEmpty(struct Stack* Stack)
{
    return Stack->Top == -1;
}

void Push(struct Stack* Stack, int item)
{
    if (isFull(Stack))
        return;
    Stack->Array[++Stack->Top] = item;
    printf("Pushed %c\n", item);
}

int Pop(struct Stack* Stack)
{
    if (isEmpty(Stack))
        return INT_MIN;
    int Popped = Stack->Array[Stack->Top--];
    printf("Popped %c\n", Popped);
    return Popped;
}

int Peek(struct Stack* Stack)
{
    if (isEmpty(Stack))
        return INT_MIN;
    int Peek = Stack->Array[Stack->Top];
    printf("Peek %c\n", Peek);
    return Peek;
}

int getPrecedenceOfOperator(char Operator){
    switch (Operator) {
        case '-':
        case '+':
            return 1;
            break;
        case '*':
        case '/':
            return 2;
            break;
        case '^':
            return 3;
            break;
        default:
            return -1;
    }
}

int main()
{
    struct Stack* Stack = createStack(100);
    int PR, peekPR, iterator ;
    char prefix[60];
    char character;

    for(iterator = 0 ; (character = getchar()) != EOF ; iterator++) {
        printf("----- tier %d-----\n", iterator);
        character = tolower(character);

        if(character == '\n') {
            printf("\n - clearing the stack : \n\n");
            while(!isEmpty(Stack)){
                prefix[iterator] = Pop(Stack);
                printf("echoed %c \n", prefix[iterator]);
            }
            printf("%s", prefix);
            printf("----- tier -----\n");
            return 0;
        }

        if(character == ' ') {
            putchar(' ');
            continue;
        }

        if(character >= 'a' && character <= 'z' || character >= '0' && character <= '9') {
             prefix[iterator] = character;
             printf("echoed %c \n", prefix[iterator]);
             continue;
        }
        else {
            if(isEmpty(Stack)) {
                Push(Stack, character);
                continue;
            }

            if(character == '('){
                putchar(')');
                putchar(')');
                putchar('\n');
                while(Peek(Stack) != ')'){
                    prefix[iterator] = Pop(Stack);
                    printf("echoed %c \n", prefix[iterator]);
                }
                Pop(Stack);
                continue;
            } else if(character == ')') {
                putchar('(');
                putchar('(');
                putchar('\n');
                Push(Stack, character);
                continue;
            }

            if ((PR = getPrecedenceOfOperator(character)) != -1) {
                int cachedPeek = Peek(Stack);
                peekPR = getPrecedenceOfOperator(cachedPeek);
                if(PR > peekPR) {
                    Push(Stack, character);
                    continue;
                } else if(PR == peekPR) {
                    while(getPrecedenceOfOperator(Peek(Stack)) == PR) {
                        prefix[iterator] = Pop(Stack);
                        printf("echoed %c \n", prefix[iterator]);
                    }
                    Push(Stack, character);
                    continue;
                } else if (PR == peekPR && character == '^') {
                    Push(Stack, character);
                    continue;
                } else if (PR < peekPR) {
                    while(PR < peekPR && !isEmpty(Stack))
                    {
                        prefix[iterator] = Pop(Stack);
                        printf("echoed %c \n", prefix[iterator]);
                    }
                    Push(Stack, character);
                    continue;
                }
            } else {
                printf("%d : %c\n", PR, character);
                return 1;
            }
        }
        printf("----- tier -----\n");
    }
    return 0;
}
