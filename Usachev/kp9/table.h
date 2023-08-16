#ifndef table_h
#define table_h

#include <math.h>
#include <ctype.h>
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define STRSIZE 256
typedef struct data { //структура элемента таблицы
    float key; //ключ
    char string[STRSIZE]; //строка стихотворения
} value;

typedef struct { //структура вектора
    value* data; //значение
    int size; //размер 
} vector;

void createVector(vector* v, int size);
bool emptyVector(vector* v);
int sizeVector(vector* v);
value printVector(vector* v, int i);
void writeVector(vector* v, int i, value data);
void resizeVector(vector* v, int size);
void destroyVector(vector* v);
void printTable(vector* v);
value binarySearch(vector* table, float key, bool reverseSorted);
void bubbleSort(vector* v);
bool checkSortTable(vector* table);
bool checkSortTableReverse(vector* table);
#endif
