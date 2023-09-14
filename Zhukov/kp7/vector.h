#ifndef vector_h
#define vector_h

#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

//структура вектора
typedef struct { 
    int* value; //значение
    int size; //размер 
} vector;

// функции-методы вектора
void create_vector(vector* v, int size);
bool empty_vector(vector* v);
int size_vector(vector* v);
int print_vector(vector* v, int i);
void add_vector(vector* v, int i, int value);
void resize_vector(vector* v, int size);
void delete_vector(vector* v);
#endif