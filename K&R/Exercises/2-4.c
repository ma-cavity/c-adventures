#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LIMIT 10

void squeeze(char s1[], char c) {
    for (int i = 0 ; i < LIMIT ; i++) {
        if(s1[i] == '\0' && i + 1 >= LIMIT) {
            s1[i] = ('\n');
        }

        if(isgraph(s1[i])) {
            if(s1[i] == c)
                s1[i] = 31;
        }
    }
}

int main() {
    char s1[LIMIT] = "";
    fgets(s1, LIMIT, stdin);
    squeeze(s1, '!');
    printf("%s", s1);
}