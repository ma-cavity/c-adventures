#include <stdio.h>

int calculateNumberOfSpaces(int letterIterator) {
    return 5 - (letterIterator % 5);
    // 5 is the default TAB length
}

int main() {
    char character;
    for (int iterator = 0, letterIterator = 0; (character = getchar()) != '\n'; iterator++){
        if(character == '\t') {
            int tabLen = calculateNumberOfSpaces(letterIterator);
            for(int internalIterator = 0; internalIterator < tabLen ; internalIterator++) {
                putchar(' ');
                letterIterator++;
            }
        }
        else {
            putchar(character);
            letterIterator++;
        }
    }
}