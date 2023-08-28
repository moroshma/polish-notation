#include "calculation.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

double calculate(char* string, double x) {
    StackDouble* st = NULL;
    int i = 0;
    char* pStr = string;

    while (*pStr != '\0') {
        if (pStr[i] >= '0' && pStr[i] <= '9') {
            double num;
            int shift;
            sscanf(pStr, "%lf%n", &num, &shift);
            st = push_d(st, num);
            pStr += shift + 1;

        } else if (pStr[i] == 'x') {
            st = push_d(st, x);
            pStr += 2;
        } else if (pStr[i] == '+') {
            double a = top_d(st);
            st = pop_d(st);
            double b = top_d(st);
            st = pop_d(st);
            st = push_d(st, a + b);
            pStr += 2;
        } else if (pStr[i] == '-') {
            double a = top_d(st);
            st = pop_d(st);
            double b = top_d(st);
            st = pop_d(st);
            st = push_d(st, a - b);
            pStr += 2;
        } else if (pStr[i] == '/') {
            double a = top_d(st);
            st = pop_d(st);
            double b = top_d(st);
            st = pop_d(st);
            st = push_d(st, a / b);
            pStr += 2;
        } else if (pStr[i] == '*') {
            double a = top_d(st);
            st = pop_d(st);
            double b = top_d(st);
            st = pop_d(st);
            st = push_d(st, a * b);
            pStr += 2;
        } else if (pStr[i] == 's') {
            double a = top_d(st);
            st = pop_d(st);
            st = push_d(st, sin(a));
            pStr += 2;
        } else if (pStr[i] == 'c') {
            double a = top_d(st);
            st = pop_d(st);
            st = push_d(st, cos(a));
            pStr += 2;
        } else if (pStr[i] == 't') {
            double a = top_d(st);
            st = pop_d(st);
            st = push_d(st, tan(a));
            pStr += 2;
        } else if (pStr[i] == 'g') {
            double a = top_d(st);
            st = pop_d(st);
            st = push_d(st, 1.0 / tan(a));
        } else if (pStr[i] == 'q') {
            double a = top_d(st);
            st = pop_d(st);
            st = push_d(st, sqrt(a));
            pStr += 2;
        } else if (pStr[i] == 'l') {
            double a = top_d(st);
            st = pop_d(st);
            st = push_d(st, log(a));
            pStr += 2;
        } else if (pStr[i] == '~') {
            st->data = top_d(st) * -1;
            pStr += 2;
        }
    }

    double result = top_d(st);
    destroy_d(st);
    return result;
}
