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
    }
    q->size++;
}
int popBack(queue *q) {
    int value = q->last->value;
    element* prev = q->first;
    while (prev->next != q->last) { // Находим элемент, предшествующий последнему
        prev = prev->next;
    }
    free(q->last);
    q->last = prev; // Переустанавливаем указатель на последний элемент
    q->last->next = NULL; // Устанавливаем указатель следующего элемента последнего на NULL
    q->size--;
    if (q->size == 0) { // Если очередь стала пустой, первый элемент также будет NULL
        q->first = NULL;
    }
    return value;
}
int topBack(queue *q) {
    return q->last->value;
}
void deleteQueue(queue *q) {
    int size = sizeQueue(q);
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
void printQueue(queue *q) {
    int size = sizeQueue(q);
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