#include <stdio.h>
#include <string.h>
#define LIMIT 100

int main() {
    char s1[LIMIT] = "", s2[LIMIT] = "";
    int occurranceOffset = 0, occurranceCounter = 0;

    fgets(s1, LIMIT, stdin);
    fgets(s2, LIMIT, stdin);

    for(int iterator = 0 ; iterator < strlen(s1) ; iterator++) {
        if(s1[iterator] == s2[0]) {
            for(int internalIterator = 0 ; internalIterator < strlen(s2) - 1 ; internalIterator++) {
                if(s1[iterator + internalIterator] == s2[internalIterator]) {
                    if(internalIterator == 0) {
                        occurranceOffset = iterator;
                    }
                    occurranceCounter++;

                if(occurranceCounter + 1 == strlen(s2)) {
                    printf("%d", occurranceOffset);
                    return 0;
                }

                } else {
                    occurranceCounter = 0;
                    break;
                }
            }
        }
    }

}