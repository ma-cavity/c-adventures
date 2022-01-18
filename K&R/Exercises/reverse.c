#include <string.h>
#include <stdio.h>


void reverse(char string[]) {
    for(int iteratorLeft = 0, iteratorRight = strlen(string) - 1 ; iteratorLeft < iteratorRight; iteratorLeft++, iteratorRight--) {
        //swapping
        char tmpChar = string[iteratorLeft];
        string[iteratorLeft] = string[iteratorRight];
        string[iteratorRight] = tmpChar;
    }
}

int main() {
    char string[100];
    fgets(string, 100, stdin);
    reverse(string);
    printf("%s\n", string);
}


















































void reverse_backup(char string[]) {
    for(int iterator = 0, charIterator = strlen(string) - 1 ; iterator < charIterator ; iterator++, charIterator--) {
        if(string[charIterator] == '\n' || string[iterator] == '\n')
            continue;
        // swapping
        printf("iterator : %c ; charIterator : %c\n", string[iterator], string[charIterator]);
        char tempSwapChar = string[iterator];
        string[iterator] = string[charIterator];
        string[charIterator] = tempSwapChar;
    }
}