#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
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
    struct Stack* Stack = createStack(60); // Stack is used for Infix-To-Prefix Conversion operations.
    struct Stack* CharactersStack = createStack(60); // createStack is used because we need the Expression in the reverse order. if not we could just iterate the Input Expression normally.
    struct Stack* outPutStack = createStack(60); // outPutStack is used because we need to create the Expression in the reverse order. if not we could use normal String concatenation.
    int characterPrecedence, precedenceOfPeek, iterator ;
    char character;


    // appending the LF at the beginning of the Stack (Reversed Order, you remember?)
    Push(CharactersStack, '\n', true);

    // receiving the Expression and Pushing it onto Stack
    while((character = getchar()) != EOF) {
        if(character != '\n')
            Push(CharactersStack, tolower(character), true);
    }

    for(iterator = 0 ; !isEmpty(CharactersStack) ; iterator++) {
        character = Pop(CharactersStack, true);
        printf("----- tier %d -----\n", iterator);

        if(character == '\n') { // encountering the last character of the expression, which is a LF control character. at this point program starts popping till Stack is empty, then outputs the Prefix Expression from outPutStack.
            printf("- the incoming character is : EndOfExpression (LineFeed ASCII)\n");
            printf("- End Of The Expression\n");
            printf("- clearing the stack : \n\n");

            while(!isEmpty(Stack)){
                char tempPoppedValue = Pop(Stack, false);
                Push(outPutStack, tempPoppedValue, true);
                printf("printed %c \n", tempPoppedValue);
            }

            printf("\n- Prefix Expression : \n\n\t");
            while(!isEmpty(outPutStack)) {
                char temp = Pop(outPutStack, true);
                putchar(temp);
            }

            putchar('\n');

            return 0;
        }else {
            printf("- the incoming character is : %c \n", character);
        }

        if(character == ' ') {
            putchar(' ');
            continue;
        }

        if(character >= 'a' && character <= 'z' || character >= '0' && character <= '9') { // [A-Za-Z0-9] are considered as operands
             Push(outPutStack, character, true);
             printf("printed %c \n", character);
             printf("- printed directly because it's an operand [a-zA-Z0-9] \n");
            continue;
        }
        else {
            if(isEmpty(Stack)) {
                Push(Stack, character, false);
                printf("- Pushed because the Stack is empty \n");
                continue;
            }
            else if(character == '('){
                printf("- encountered ')' , popping till reach '(' (where TOP='(' ) \n");
                while(Peek(Stack, false) != ')'){
                    char tempPoppedValue = Pop(Stack, false);
                    Push(outPutStack, tempPoppedValue, true);
                    printf("printed %c \n", tempPoppedValue);
                }
                Pop(Stack, false);
                continue;
            } else if(character == ')') {
                Push(Stack, character, false);
                printf("- ')' must be pushed unconditionally\n");
                continue;
            }

            if ((characterPrecedence = getPrecedenceOfOperator(character)) != -1) {
                int cachedPeek = Peek(Stack, false); // preventing calling Peek multiple times
                precedenceOfPeek = getPrecedenceOfOperator(cachedPeek);
                if(characterPrecedence > precedenceOfPeek) {
                    Push(Stack, character, false);
                    continue;
                } else if(characterPrecedence == precedenceOfPeek) {
                    if(character == '^') {
                        Push(Stack, character, false);
                        continue;
                    }

                    printf("- Popping till precedence of TOP is equal to precedence of '%c'\n", character);

                    while(getPrecedenceOfOperator(Peek(Stack, false)) == characterPrecedence) {
                        char tempPoppedValue = Pop(Stack, false);
                        Push(outPutStack, tempPoppedValue, true);
                        printf("printed %c \n", tempPoppedValue);
                    }
                    Push(Stack, character, false);
                    continue;
                } else if (characterPrecedence < precedenceOfPeek) {
                    printf("- TOP ('%c') has more precedence than '%c'\n", cachedPeek, character);
                    printf("- Popping and Printing while precedence of TOP is more than precedence of '%c'\n", character);
                    while(characterPrecedence < precedenceOfPeek && !isEmpty(Stack))
                    {
                        char tempPoppedValue = Pop(Stack, false);
                        Push(outPutStack, tempPoppedValue, true);
                        printf("printed %c \n", tempPoppedValue);
                    }
                    Push(Stack, character, false);
                    continue;
                }
            } else {
                return 1;
            }
        }
    }
    return 0;
}
