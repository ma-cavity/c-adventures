#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void expand(char string[]) {
    for(int iterator = 0 ; iterator < strlen(string) ; iterator++) {
        if(string[iterator] == '\n')
            continue;
        else if (string[iterator] == '-') {
            if(string[iterator - 1] == 0 || string[iterator + 1] == 0)
                break;

            if(isalpha(string[iterator - 1]) && isalpha(string[iterator + 1])) {
                char a = tolower(string[iterator - 1]), b = tolower(string[iterator + 1]);
                for(int iterator = 0 ; iterator <= (b - a) ; iterator++) {
                    putchar(a + iterator);
                }
            } else if(isdigit(string[iterator - 1]) && isdigit(string[iterator + 1])) {
                int a = atoi(&string[iterator - 1]), b = atoi(&string[iterator + 1]);
                for(int iterator = 0 ; iterator <= b - a && b <= 9 && a >= 0 && b >= 0 && a <= 9 ; iterator++) {
                    putchar(a + iterator + '0');
                }
            }
        }
    }
}


void trim(char string[], char delimiter) {
    int offset = (string[strlen(string) - 1] == '\n') ? strlen(string) - 2 : strlen(string) - 1;
    if(string[offset] == delimiter)
        string[offset] = '\0';
    if(string[0] == delimiter)
        memmove(&string[0], &string[1], strlen(string));
}

int main() {
    char string[100];
    fgets(string, 100, stdin);
    trim(string, '-');
    expand(string);
}