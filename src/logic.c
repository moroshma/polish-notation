#include "logic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define SIN 's'
#define COS 'c'
#define TAN 't'
#define CTG 'g'
#define SQRT 'q'
#define LN 'l'

int translate(char* str, char** polish) {
    int ret = 1, check = 0, len = 0, operator= 0;
    Stack* stack = NULL;
    while (*str && ret && (check == 0 || check == 1)) {
        if (*str == 'x') {
            check++;
            *polish = realloc(*polish, (len + 2) * sizeof(char));
            (*polish)[len++] = 'x';
            (*polish)[len++] = ' ';
            str++;
        } else if (*str >= '0' && *str <= '9') {
            check++;
            add_num(&str, polish, &len);
        } else if (is_operator(&str, &operator)) {
            if (priority(operator) == 1 || priority(operator) == 2) check--;
            ret = add_op(polish, &stack, operator, & len);

        } else {
            ret = 0;
        }
    }
    *polish = realloc(*polish, (len + 1) * sizeof(char));
    (*polish)[len++] = '\0';
    ret = ret && check == 1 && isEmpty(stack);
    destroy(stack);
    return ret;
}

int is_operator(char** str, int* operator) {
    int ret = 1;
    if (**str == '+' || **str == '-' || **str == '*' || **str == '/' || **str == '(' || **str == ')') {
        *operator= ** str;
        (*str)++;
        if (**str == '-') {
            char* tmp = *str - 2;
            while (*tmp == ' ') tmp--;
            if (*tmp == '(') *operator= '~';
        }
    } else if (!strncmp(*str, "sin(", 4)) {
        *operator= SIN;
        (*str) += 4;
    } else if (!strncmp(*str, "cos(", 4)) {
        *operator= COS;
        (*str) += 4;
    } else if (!strncmp(*str, "tan(", 4)) {
        *operator= TAN;
        (*str) += 4;
    } else if (!strncmp(*str, "ctg(", 4)) {
        *operator= CTG;
        (*str) += 4;
    } else if (!strncmp(*str, "sqrt(", 5)) {
        *operator= SQRT;
        (*str) += 5;
    } else if (!strncmp(*str, "ln(", 3)) {
        *operator= LN;
        (*str) += 3;
    } else {
        ret = 0;
    }
    return ret;
}

int priority(int operator) {
    int ret = 0;  // по умолчанию это открывающая скобка или функция заданная в макросах сверху
    if (operator== ')') ret = -1;
    if (operator== '+' || operator== '-') ret = 1;
    if (operator== '*' || operator== '/') ret = 2;
    if (operator== '~') ret = 3;
    return ret;
}

void add_num(char** str, char** polish, int* len) {
    while (**str >= '0' && **str <= '9') {
        *polish = realloc(*polish, (*len + 1) * sizeof(char));
        (*polish)[(*len)++] = **str;
        (*str)++;
    }
    if (**str == '.') {
        *polish = realloc(*polish, (*len + 1) * sizeof(char));
        (*polish)[(*len)++] = **str;
        (*str)++;
    }
    while (**str >= '0' && **str <= '9') {
        *polish = realloc(*polish, (*len + 1) * sizeof(char));
        (*polish)[(*len)++] = **str;
        (*str)++;
    }
    *polish = realloc(*polish, (*len + 1) * sizeof(char));
    (*polish)[(*len)++] = ' ';
}

int add_op(char** polish, Stack** stack, int operator, int * len) {
    int ret = 1;
    if (priority(operator) == 0) *stack = push(*stack, operator);
    if (priority(operator) == -1) {
        while (!isEmpty(*stack) && priority(top(*stack)) != 0) {
            *polish = realloc(*polish, (*len + 2) * sizeof(char));
            (*polish)[(*len)++] = top(*stack);
            (*polish)[(*len)++] = ' ';
            *stack = pop(*stack);
        }
        if (!isEmpty(*stack)) {
            if (top(*stack) != '(') {
                *polish = realloc(*polish, (*len + 2) * sizeof(char));
                (*polish)[(*len)++] = top(*stack);
                (*polish)[(*len)++] = ' ';
            }
            *stack = pop(*stack);
        } else {
            ret = 0;
        }
    }
    if (priority(operator) > 0) {
        while (!isEmpty(*stack) && priority(top(*stack)) >= priority(operator)) {
            *polish = realloc(*polish, (*len + 2) * sizeof(char));
            (*polish)[(*len)++] = top(*stack);
            (*polish)[(*len)++] = ' ';
            *stack = pop(*stack);
        }
        *stack = push(*stack, operator);
    }
    return ret;
}