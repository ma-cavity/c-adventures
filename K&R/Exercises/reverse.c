#include <string.h>

void reverse(char string[]) {
    for(int iteratorLeft = 0, iteratorRight = strlen(string) - 1 ; iteratorLeft < iteratorRight; iteratorLeft++, iteratorRight--) {
        //swapping
        char tmpChar = string[iteratorLeft];
        string[iteratorLeft] = string[iteratorRight];
        string[iteratorRight] = tmpChar;
    }
}