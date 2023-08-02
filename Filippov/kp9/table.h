#ifndef table_h
#define table_h

#include <math.h>
#include <ctype.h>
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#define STR_SIZE 100

typedef struct data {
    char key[6]; //ключ
    char string[STR_SIZE]; //строка стихотворения
} data;

typedef struct { //структура вектора
    data* data; //значение
    int size; //размер 
} vector;

void create_vector(vector* v, int size);
bool empty_vector(vector* v);
int size_vector(vector* v);
data get_vector(vector* v, int i);
void add_vector(vector* v, int i, data data);
void resize_vector(vector* v, int size);
void destroy_vector(vector* v);
int cmp_key(data x, data y);
void print_table(vector* v);
void swap(data* x, data* y);
data binary_search(vector* table, char* key, bool reverse_sorted);
bool check_table_sorted(vector* table);
bool check_table_reversed(vector* table);
#endif
