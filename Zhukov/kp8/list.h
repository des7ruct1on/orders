#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct Complex {
    int real;
    int im;
} Complex;

// Структура для элемента списка
typedef struct Node {
    Complex data;
    struct Node* next;
} Node;

// Структура для списка
typedef struct Linked_list {
    Node* barrier; // Барьерный элемент
    int size;             // Размер списка (без учета барьерного элемента)
} Linked_list;

void init_list(Linked_list* list);
void append(Linked_list* list, Complex data);
void remove_index(Linked_list* list, int k);
void print_list(Linked_list* list);
int get_size(Linked_list* list);
void clear_list(Linked_list* list);
void pop_back(Linked_list* list);
void insert_at(Linked_list* list, int index, Complex data);

#endif