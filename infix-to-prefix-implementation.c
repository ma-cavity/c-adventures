#include <stdio.h>
#include <ctype.h>
#include <string.h>
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
    struct Stack* Stack = createStack(60);
    int PR, peekPR, iterator ;
    char prefix[60], character;

    for(iterator = 0 ; (character = getchar()) != EOF ; iterator++) {
        printf("----- tier %d-----\n", iterator);

        character = tolower(character);

        if(character == '\n') { // encountering the last character of the expression, which is a LF control character
            printf("\n - clearing the stack : \n\n");
            while(!isEmpty(Stack)){
                char tempPoppedValue = Pop(Stack);
                strncat(prefix, &tempPoppedValue, 1);
                printf("echoed %c \n", prefix[iterator]);
            }
            printf("\n - Prefix Expression : \n\n\t%s\n\n", prefix);
            return 0;
        }

        if(character == ' ') {
            putchar(' ');
            continue;
        }

        if(character >= 'a' && character <= 'z' || character >= '0' && character <= '9') {
             strncat(prefix, &character, 1);
             printf("choed %c \n", prefix[iterator]);
             continue;
        }
        else {
            if(isEmpty(Stack)) {
                Push(Stack, character);
                continue;
            }

            if(character == '('){
                while(Peek(Stack) != ')'){
                    char tempPoppedValue = Pop(Stack);
                    strncat(prefix, &tempPoppedValue, 1);
                    printf("echoed %c \n", prefix[iterator]);
                }
                Pop(Stack);
                continue;
            } else if(character == ')') {
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
                        char tempPoppedValue = Pop(Stack);
                        strncat(prefix, &tempPoppedValue, 1);
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
                        char tempPoppedValue = Pop(Stack);
                        strncat(prefix, &tempPoppedValue, 1);
                        printf("echoed %c \n", prefix[iterator]);
                    }
                    Push(Stack, character);
                    continue;
                }
            } else {
                return 1;
            }
        }
    }
    return 0;
}
