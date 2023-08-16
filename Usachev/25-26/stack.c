#include "stack.h"

void stackInit (stack* s) {
    s->size = 0;
    s->top = NULL;
}

int sizeStack(stack* s) {
    return s->size;
}

bool emptyStack (stack* s) {
    return s->size == 0;

}

void pushBack (stack* s, int value) {
    stackNode* tmp = (stackNode*)malloc(sizeof(stackNode));
    stackNode* last = s->top;
    tmp->value = value;
    tmp->prev = last;
    s->top = tmp;
    s->size++;
}



int popBack (stack* s) {
    int size = sizeStack(s);
    if (size == 0) {
        printf("Стек пуст\n");
        return INT_MAX;
    }
    stackNode* last = s->top;
    int value = last->value;
    stackNode* newLast = last->prev;
    s->top = newLast;
    free(last);
    s->size--;
    return value;
}

void stackDelete(stack* s) {
    int size = sizeStack(s);
    if (size == 0) {
        printf("Стек пуст\n");
        return;
    }
    while(size > 0) {
        stackNode* tmp = s->top;
        s->top = s->top->prev;
        free(tmp);
        size--;
    }
    s->size = 0;
    s->top =NULL;
}


void stackPrint(stack* s) {
    stack* tmp = malloc(sizeof(stack));
    stackInit(tmp);
    if (emptyStack(s)) {
        printf("Стек пуст\n");
        free(tmp); // Освобождаем память перед выходом из функции
        return;
    }
    int size = sizeStack(s);
    for(int i = 0; i < size; i++) {
        pushBack(tmp, popBack(s));
    }
    int current;
    for (int i = 0; i < size; i++) {
        current = popBack(tmp);
        printf("%d ", current);
        pushBack(s, current);
    }
    free(tmp); // Освобождаем память перед выходом из функции
}

