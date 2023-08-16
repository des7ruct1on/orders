#ifndef vector_h
#define vector_h

#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct { //структура вектора
    int* value; //значение
    int size; //размер 
} vector;

void createVector(vector* v, int size);
bool empty(vector* v);
int sizeVector(vector* v);
int loadVector(vector* v, int i);
void writeVector(vector* v, int i, int value);
void resizeVector(vector* v, int size);
bool equalVector(vector* l, vector* r);
void destroyVector(vector* v);
void destroyElement(vector* vIndex, vector* v, int i);
void checkNullElements(vector* v, vector* vIndex);
#endif
