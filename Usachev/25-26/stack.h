#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct stackNode { // структура элемента стека на основе односвязного списка
    int value; // значение
    struct stackNode* prev; //указатель на следующий
} stackNode;

typedef struct stack { //структура стека
    int size; // размер стека
    stackNode* top; // указатель на верхний элемент 
} stack;

bool emptyStack (stack* s);
int sizeStack (stack* s);
void pushBack (stack* s, int value);
int popBack (stack* s);
void stackInit (stack* s);
void stackDelete(stack* s);
void stackPrint(stack* s);

#endif