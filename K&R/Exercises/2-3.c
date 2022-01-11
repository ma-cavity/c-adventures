#include <stdio.h>
#include <ctype.h>
#include "Stack.h"
#include <math.h>
#define LIMIT 64

int main() {
    char character;
    unsigned long int decimal = 0;
    struct Stack* Stack = createStack(LIMIT);

    for(int iterator = 0 ; (character = getchar()) != '\n' || iterator > LIMIT ; iterator++) {
        character = tolower(character);
        if(character == '0' && iterator == 0 || character == 'x') {
            Push(Stack, character, true);
            continue;
        }

        if(!isxdigit(character))
            return 1;

        Push(Stack, character, true);
    }

    character = ' ';

    for(int iterator = 0 ; (character = Pop(Stack, true)) > 0 ; iterator++) {
        int x = 0;
        if(character == 'x') {
            Pop(Stack, true);
            break;
        }
        if(isxdigit(character) && !isdigit(character))
            x = character - 'W';
        else
            x = atoi(&character);
        decimal += x * pow(16, iterator);
    }

    printf("%ld\n", decimal);
}