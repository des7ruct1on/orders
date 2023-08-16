#ifndef vector_h
#define vector_h

#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct { //структура вектора
    int* value; //значение
    int size; //размер 
} vector;

void createVector(vector* v, int size);
bool emptyVector(vector* v);
int sizeVector(vector* v);
int printVector(vector* v, int i);
void writeVector(vector* v, int i, int value);
void resizeVector(vector* v, int size);
void destroyVector(vector* v);
#endif