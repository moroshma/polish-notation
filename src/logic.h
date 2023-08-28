#ifndef LOGIC_C
#define LOGIC_C

#include "stack.h"

int translate(char *str, char **polish);
int priority(int operator);
int is_operator(char **str, int *operator);
void add_num(char **str, char **polish, int *len);
int add_op(char **polish, Stack **st, int operator, int * len);

#endif