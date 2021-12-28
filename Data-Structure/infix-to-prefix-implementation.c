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
            printf("- the incoming character is : EndOfExpression (LineFeed ASCII) \n");
            printf("- End Of The Expression");
            printf("\n- clearing the stack : \n\n");
            while(!isEmpty(Stack)){
                char tempPoppedValue = Pop(Stack);
                strncat(prefix, &tempPoppedValue, 1);
                printf("echoed %c \n", tempPoppedValue);
            }
            printf("\n - Prefix Expression : \n\n\t%s\n\n", prefix);
            return 0;
        }else {
            printf("- the incoming character is : %c \n", character);
        }

        if(character == ' ') {
            putchar(' ');
            continue;
        }

        if(character >= 'a' && character <= 'z' || character >= '0' && character <= '9') {
             strncat(prefix, &character, 1);
             printf("- echoed directly because it's an operand [a-zA-Z0-9] \n");
             printf("echoed %c \n", character);
             continue;
        }
        else {
            if(isEmpty(Stack)) {
                Push(Stack, character);
                continue;
            }
            if(character == ')'){
                printf("- encountered ) , popping till reach ( (where TOP=( ) \n");
                while(Peek(Stack) != '('){
                    char tempPoppedValue = Pop(Stack);
                    strncat(prefix, &tempPoppedValue, 1);
                    printf("echoed %c \n", tempPoppedValue);
                }
                Pop(Stack);
                continue;
            } else if(character == '(') {
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
                        printf("echoed %c \n", tempPoppedValue);
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
                        printf("echoed %c \n", tempPoppedValue);
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
