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

void initQueue(queue *D);
int sizeQueue(queue *D);
bool emptyQueue(queue *D);
void pushFront(queue *D, int value);
int popBack(queue *D);
int topBack(queue *D);
void deleteQueue(queue *D);
void printQueue(queue *D);

#endif
