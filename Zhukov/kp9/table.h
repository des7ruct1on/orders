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
    char key[5]; //ключ
    char string[STRSIZE]; //строка стихотворения
} value;

typedef struct { //структура вектора
    value* data; //значение
    int size; //размер 
} vector;

void create_vector(vector* v, int size);
bool empty_vector(vector* v);
int size_vector(vector* v);
value print_vector(vector* v, int i);
void add_vector(vector* v, int i, value data);
void resize_vector(vector* v, int size);
void destroy_vector(vector* v);
void print_table(vector* v);
value binary_search(vector* table, char* key, bool reverse_sorted);
void bubble_sort(vector* v);
bool check_sort_table(vector* table);
bool check_sort_table_reverse(vector* table);
#endif
