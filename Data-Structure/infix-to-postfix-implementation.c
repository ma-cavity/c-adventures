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
    struct Stack* Stack = createStack(60);
    char character, postfix[60] = "";
    int characterPrecedence, precedenceOfPeek, iterator ;

    // iterating the infix Expression
    for(iterator = 0 ; (character = getchar()) != EOF ; iterator++) {
        printf("----- tier %d -----\n", iterator);

        character = tolower(character);

        if(character == '\n') { // encountering the last character of the expression, which is a LF control character. at this point program starts popping till Stack is empty, then outputs the Prefix Expression.
            printf("- the incoming character is : EndOfExpression (LineFeed ASCII) \n");
            printf("- End Of The Expression\n");
            printf("- clearing the stack : \n\n");

            while(!isEmpty(Stack)){
                char tempPoppedValue = Pop(Stack, false);
                strncat(postfix, &tempPoppedValue, 1);
                printf("printed %c \n", tempPoppedValue);
            }

            printf("\n- Postfix Expression : \n\n\t%s\n\n", postfix);

            return 0;
        }else {
            printf("- the incoming character is : %c \n", character);
        }

        if(character == ' ') {
            putchar(' ');
            continue;
        }

        if(character >= 'a' && character <= 'z' || character >= '0' && character <= '9') { // Rule NO 1
            strncat(postfix, &character, 1);
            printf("printed %c \n", postfix[iterator]);
            printf("- printed directly because it's an operand [a-zA-Z0-9] \n");
            continue;
        }
        else { // Rule NO 2
            if(isEmpty(Stack) || character == '(') { // Rule NO 2. push if stack is empty
                Push(Stack, character, false);
                printf(character == '(' ? "- Pushed because the character is '(' " : "- Pushed because the Stack is empty \n");
                continue;
            }else if(character == ')') { // Rule NO 7
                printf("- encountered ')' , popping till reach '(' (where TOP='(' ) \n");
                while(Peek(Stack, false) != '('){
                    char tempPoppedValue = Pop(Stack, false);
                    strncat(postfix, &tempPoppedValue, 1);
                    printf("printed %c \n", postfix[iterator]);
                }
                Pop(Stack, false); // Popping the ( character
                continue;
            }else if ((characterPrecedence = getPrecedenceOfOperator(character)) != -1) {
                int cachedPeek = Peek(Stack, false);
                if(characterPrecedence > (precedenceOfPeek = getPrecedenceOfOperator(cachedPeek))) { // Rule NO 2 push if character has higher precedence than TOP
                    Push(Stack, character, false);
                    continue;
                } else { // Rule NO 4
                    printf("- Popping till precedence of TOP is higher than or equal to precedence of '%c'\n", character);

                    while(getPrecedenceOfOperator(character) <= getPrecedenceOfOperator(Peek(Stack, false)))
                    {
                        char tempPoppedValue = Pop(Stack, false);
                        strncat(postfix, &tempPoppedValue, 1);
                        printf("printed %c \n", postfix[iterator]);
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
