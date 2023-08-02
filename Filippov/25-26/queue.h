#ifndef queue_h 
#define queue_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct element {
    int value; //значение
    struct element *next; //указ на след элемент
} element;

typedef struct queue {
    element *first; //первый элемент
    element *last; //последний элемент
    int size; //рамзер
} queue;

void init_queue(queue *q);
int size_queue(queue *q);
bool empty_queue(queue *q);
void push_back(queue *q, int value);
int pop_front(queue *q);
int top_front(queue *q);
void delete_queue(queue *q);
void print_queue(queue *q);

#endif
