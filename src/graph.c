#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIN 's'
#define COS 'c'
#define TAN 't'
#define CTG 'g'
#define SQRT 'q'
#define LN 'l'

#include "input.h"
#include "logic.h"
#include "stack.h"

#define H 25  // Высота поля
#define L 80  // Ширина поля

#define CMP_L 9.1  // Задаем область определения 4PI
#define CMP_H \
    12  // Задаем область значений от -1 до 1 (ось ординат направлена вниз, чтобы
        // перенаправить - *(-1)

#define RAD \
    0.0174533  // Применяем к тригонометрическим функциям, так как они принимают
               // радианы, коэффициент переводит в градусы

// Функции для проверки - sin(cos(2*i)); sqrt(-(1/(-i*i)))  sin(i)0
double calculate(char* string, double x);
void printGraph(double arr_y[L]);
void findPoint(double arr_y[L], char* st);

int main() {
    char *str = NULL, *polish = NULL;

    printf("Введите математическое выражение в инфиксной нотации: ");
    input(&str);

    if (str) {
        if (translate(str, &polish)) {
            printf("%s\n", polish);
            double arr_y[L];
            findPoint(arr_y, polish);
            printGraph(arr_y);
        } else {
            printf("n/a\n");
        }
    } else {
        printf("n/a\n");
    }

    if (str) free(str);
    if (polish) free(polish);
    return 0;

    //// Распечатываем график - выделить в отдельную функцию, которая принимает
    ///массив значений (80 значений y)
}

void findPoint(double arr_y[L], char* st) {
    int k = 0;
    for (double i = 0; i < L * CMP_L; i += CMP_L) {
        arr_y[k] = (calculate(st, i * RAD) * CMP_H);  // Сюда подставляем функцию
        k++;
    }
}

void printGraph(double arr_y[L]) {
    for (int i = -CMP_H; i < CMP_H + 1; i++) {
        for (int j = 0; j < L; j++) {
            if (i == (int)round(arr_y[j])) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}
