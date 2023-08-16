#ifndef table_h
#define table_h

#include <math.h>
#include <ctype.h>
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define STRSIZE 100

typedef struct value {
    long long int key; //ключ
    char string[STRSIZE]; //строка стихотворения
} value;

typedef struct { //структура вектора
    value* data; //значение
    int size; //размер 
} vector;

void createVector(vector* v, int size);
bool empty(vector* v);
int sizeVector(vector* v);
value loadVector(vector* v, int i);
void writeVector(vector* v, int i, value data);
void resizeVector(vector* v, int size);
void destroyVector(vector* v);
void printTable(vector* v);
void swap(value* x, value* y);
void sortShake(vector* v);
value binarySearch(vector* table, long long int key);
bool checkSortTable(vector* table);
bool checkSortTableDescending(vector* table);
void vectorReverse(vector* a, vector* b);
#endif
