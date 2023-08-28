
#include <stdlib.h>

#include "stack.h"

Stack* push(Stack* st, int data) {
    Stack* new = malloc(sizeof(Stack));
    new->data = data;
    new->next = st;
    return new;
}

Stack* pop(Stack* st) {
    Stack* tmp = st;
    st = st->next;
    free(tmp);
    return st;
}

int top(Stack* st) { return st->data; }

int isEmpty(const Stack* st) { return st == NULL; }

void destroy(Stack* st) {
    while (st != NULL) {
        st = pop(st);
    }
}

StackDouble* push_d(StackDouble* st, double data) {
    StackDouble* new = malloc(sizeof(StackDouble));
    new->data = data;
    new->next = st;
    return new;
}

StackDouble* pop_d(StackDouble* st) {
    StackDouble* tmp = st;
    st = st->next;
    free(tmp);
    return st;
}

double top_d(StackDouble* st) { return st->data; }

void destroy_d(StackDouble* st) {
    while (st != NULL) {
        st = pop_d(st);
    }
}
