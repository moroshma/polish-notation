#include "input.h"

#include <stdio.h>
#include <stdlib.h>

void input(char** str) {
    int c, len = 0;
    *str = realloc(*str, (len + 1) * sizeof(char));
    (*str)[len++] = '(';
    while ((c = getchar()) != '\n' && c != EOF) {
        *str = realloc(*str, (len + 1) * sizeof(char));
        (*str)[len++] = c;
    }
    *str = realloc(*str, (len + 2) * sizeof(char));
    (*str)[len++] = ')';
    (*str)[len++] = '\0';
}
