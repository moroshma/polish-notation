#ifndef STACK_H
#define STACK_H

typedef struct Stack {
    int data;
    struct Stack* next;
} Stack;

Stack* push(Stack* st, int data);
Stack* pop(Stack* st);
int top(Stack* st);
int isEmpty(const Stack* st);
void destroy(Stack* st);

typedef struct StackDouble {
    double data;
    struct StackDouble* next;
} StackDouble;

StackDouble* push_d(StackDouble* st, double data);
StackDouble* pop_d(StackDouble* st);
double top_d(StackDouble* st);

void destroy_d(StackDouble* st);

#endif