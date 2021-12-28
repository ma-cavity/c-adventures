#include <stdio.h>
#include <ctype.h>
#include "Stack.h"

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
    char character;
    int PR, peekPR, iterator ;
    char postfix[60];

    for(iterator = 0 ; (character = getchar()) != EOF ; iterator++) {
        printf("----- tier %d -----\n", iterator);
        character = tolower(character);
        if(character == '\n') { // omitting the LF control character
            printf("\n - clearing the stack : \n\n");
            while(!isEmpty(Stack)){
                postfix[iterator] = Pop(Stack);
                    printf("echoed %c \n", postfix[iterator]);
            }
            printf("%s", postfix);
            printf("----- tier -----\n");
            return 0;
        }

        if(character == ' ') {
            putchar(' ');
            continue;
        }

        if(character >= 'a' && character <= 'z' || character >= '0' && character <= '9') { // Rule NO 1
             postfix[iterator] = character;
             printf("echoed %c \n", postfix[iterator]);
        }
        else { // Rule NO 2
            if(isEmpty(Stack) || character == '(') { // Rule NO 2. push if stack is empty
                Push(Stack, character);
                continue;
            }

            if(character == ')') { // Rule NO 7
                while(Peek(Stack) != '('){
                    postfix[iterator] = Pop(Stack);
                    printf("echoed %c \n", postfix[iterator]);
                }
                Pop(Stack); // Popping the ( character
                continue;
            }

            if ((PR = getPrecedenceOfOperator(character)) != -1) {
                int cachedPeek = Peek(Stack);
                if(PR > (peekPR = getPrecedenceOfOperator(cachedPeek))) { // Rule NO 2 push if character has higher precedence than TOP
                    Push(Stack, character);
                    continue;
                } else { // Rule NO 4
                    while(getPrecedenceOfOperator(character) <= getPrecedenceOfOperator(Peek(Stack)))
                    {
                        postfix[iterator] = Pop(Stack);
                        printf("echoed %c \n", postfix[iterator]);
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
