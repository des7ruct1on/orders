#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int Item;

typedef struct _node_queue  {
    Item value; //значение
    struct _node_queue  *next; //указ на след элемент
} NodeQ;

typedef struct _queue  {
    NodeQ *first; //первый элемент
    NodeQ *last; //последний элемент
    size_t size; //рамзер
} Queue;

void init_queue(Queue *q);
size_t size_queue(Queue *q);
bool empty_queue(Queue *q);
void push_back(Queue *q, Item  value);
int pop_front(Queue *q);
int top_front(Queue *q);
void delete_queue(Queue *q);
void print_queue(Queue *q);

#endif
