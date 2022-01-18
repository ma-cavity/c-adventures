#include <string.h>
#include <ctype.h>
#include <limits.h>

signed long long int strtoll(char s[]) {
    signed short int sign = 0;
    signed long long int n = 0;

    for(int iterator = 0 ; iterator < strlen(s) && n < LLONG_MAX && n > LLONG_MIN ; iterator++) {
        if(isspace(s[iterator]))
            continue;
        else if (s[iterator] == '-' || s[iterator] == '+')
            sign = iterator == '+' ? 1 : -1;
        else if (isdigit(s[iterator])) {
            n = 10 * n + (s[iterator] - '0');
        } else {
            return -1;
        }
    }

    switch (sign) {
        case -1 :
            return -n;
            break;
        case 0 :
        case 1 :
            return +n;
            break;
        default:
            return -1;
            break;
    }
}