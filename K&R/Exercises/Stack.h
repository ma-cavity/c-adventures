#ifndef C_ADVENTURES_STACK_H
#define C_ADVENTURES_STACK_H
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

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

void Push(struct Stack* Stack, int item, bool silent)
{
    if (isFull(Stack))
        return;
    Stack->Array[++Stack->Top] = item;
    if (!silent)
        printf("Pushed %c\n", item);

}

int Pop(struct Stack* Stack, bool silent)
{
    if (isEmpty(Stack))
        return INT_MIN;
    int Popped = Stack->Array[Stack->Top--];

    if (!silent)
        printf("Popped %c\n", Popped);
    return Popped;
}

int Peek(struct Stack* Stack, bool silent)
{
    if (isEmpty(Stack))
        return INT_MIN;
    int Peek = Stack->Array[Stack->Top];

    if (!silent)
        printf("the TOP is : %c\n", Peek);
    return Peek;
}

#endif //C_ADVENTURES_STACK_H