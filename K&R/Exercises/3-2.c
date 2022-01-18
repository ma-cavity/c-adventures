#include <string.h>
#define STR_LIMIT 100

void escape(char stringDest[], char stringSrc[]) {
    for(int i = 0 ; i < strlen(stringSrc) ; i++) {
        switch (stringSrc[i]) {
            case '\r':
            case '\n':
                strncat(stringDest, "\\n", 2);
                break;
            case '\t':
                strncat(stringDest, "\\t", 2);
                break;
            default:
                strncat(stringDest, &stringSrc[i], 1);
        }
    }

}

void unescape(char stringDest[], char stringSrc[]) {
    for(int iterator = 0 ; iterator < strlen(stringSrc) ; iterator++) {
        if(stringSrc[iterator] == '\\') {
            switch (stringSrc[iterator + 1]) {
                case 't':
                    strncat(stringDest, "\t", 1);
                    iterator+=1;
                    break;
                case 'n':
                    strncat(stringDest, "\n", 1);
                    iterator+=1;
                    break;
            }
        } else {
            if(iterator + 1 >= strlen(stringSrc) && stringSrc[iterator] == '\n') // ignoring the last LF entered in stdin
                continue;
            strncat(stringDest, &stringSrc[iterator], 1);
        }
    }
}