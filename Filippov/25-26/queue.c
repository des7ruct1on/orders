#include "queue.h"

void init_queue(queue *q) {
    q->size = 0;
    q->first = NULL;
    q->last = NULL;
}
int size_queue(queue *q) {
    return q->size;
}
bool empty_queue(queue *q) {
    return size_queue(q) == 0;
}
void push_back(queue *q, int value) {
    element* tmp = malloc(sizeof(element)); 
    tmp->value = value; // Присваиваем значение элементу
    tmp->next = q->first;
    q->first = tmp;
    if (q->size == 0) { // Если очередь пуста, новый элемент будет и первым, и последним
        q->last = tmp;
    }
    q->size++;
}
int pop_front(queue *q) {
    if (q->size == 0) {
        return 9999999;
    }

    if (q->size == 1) {
        int value = q->last->value;
        free(q->last);
        q->size--;
        return value;
    }
    element* tmp = q->first;
    element* tmp2 = q->first->next;
    while (tmp2->next != NULL) {
        tmp = tmp->next;
        tmp2 = tmp2->next;
    }
    int value = tmp2->value;
    free(tmp2);
    tmp->next = NULL;
    q->last = tmp;
    q->size--;
    return value;
}


int top_front(queue *q) {
    return q->last->value;
}
void delete_queue(queue *q) {
    int size = size_queue(q);
    if(size == 0) {
        printf("Очередь пуста!\n");
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
void print_queue(queue *q) {
    int size = size_queue(q);
    if (size == 0) {
        printf("Очередь пуста!\n");
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