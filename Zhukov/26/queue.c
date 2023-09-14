#include "queue.h"

void initQueue(queue *q) {
    q->size = 0;
    q->first = NULL;
    q->last = NULL;
}
int sizeQueue(queue *q) {
    return q->size;
}
bool emptyQueue(queue *q) {
    return sizeQueue(q) == 0;
}
void pushFront(queue *q, int value) {
    element* tmp = malloc(sizeof(element)); 
    tmp->value = value; // Присваиваем значение элементу
    tmp->next = q->first;
    q->first = tmp;
    if (q->size == 0) { // Если очередь пуста, новый элемент будет и первым, и последним
        q->last = tmp;
        q->first = tmp;
    }
    q->size++;
}
int popBack(queue *q) {
    if (emptyQueue(q)) {
        printf("Очередь пуста0!\n");
        exit(1);
    }

    int value = q->last->value;
    element *prev = q->first;

    if (q->first == q->last) {
        // Если в очереди остался только один элемент
        free(q->last); // Освободить память для последнего элемента
        q->first = NULL;
        q->last = NULL;
    } else {
        while (prev->next != q->last) {
            prev = prev->next;
        }
        free(q->last); // Освободить память для последнего элемента
        q->last = prev;
        q->last->next = NULL;
    }

    q->size--;

    return value;
}




int topBack(queue *q) {
    return q->last->value;
}
void deleteQueue(queue *q) {
    int size = sizeQueue(q);
    if(size == 0) {
        printf("Очередь пуста1!\n");
        return;
    }
    element* tmp = q->first;
    for(int i = 0; i < size; i++) {
        element* next = tmp->next;
        free(tmp);
        tmp = next;
    }
    q->size = 0;
    q->first = NULL;
    q->last = NULL;
}
void printQueue(queue *q) {
    int size = sizeQueue(q);
    if (size == 0) {
        printf("Очередь пуста2!\n");
        return;
    }
    element* current = q->first;
    printf("{");
    for(int i = 0; i < size; i++) {
        printf("%d", current->value);
        if(i < size - 1) {
            printf(", ");
        }
        current = current->next;
    }
    printf("}");
}