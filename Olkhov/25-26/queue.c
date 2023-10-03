#include "queue.h"

void init_queue(Queue *q) {
    q->size = 0;
    q->first = NULL;
    q->last = NULL;
}
size_t size_queue(Queue *q) {
    return q->size;
}
bool empty_queue(Queue *q) {
    return size_queue(q) == 0;
}
void push_back(Queue *q, int value) {
    NodeQ* tmp = malloc(sizeof(NodeQ)); 
    tmp->value = value; // Присваиваем значение элементу
    tmp->next = q->first;
    q->first = tmp;
    if (q->size == 0) { // Если очередь пуста, новый элемент будет и первым, и последним
        q->last = tmp;
    }
    q->size++;
}
int pop_front(Queue *q) {
    if (q->size == 0) {
        return 9999999;
    }

    if (q->size == 1) {
        int value = q->last->value;
        free(q->last);
        q->size--;
        return value;
    }
    NodeQ* tmp = q->first;
    NodeQ* tmp2 = q->first->next;
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


int top_front(Queue *q) {
    return q->last->value;
}
void delete_queue(Queue *q) {
    int size = size_queue(q);
    if(size == 0) {
        printf("Queue is empty!\n");
        return;
    }
    NodeQ* tmp = q->first;
    for(int i = 0; i < size; i++) {
        NodeQ* next = tmp->next;
        free(tmp);
        tmp = next;
    }
    q->size = 0;
    q->first = NULL;
    q->last = NULL;
}
void print_queue(Queue *q) {
    int size = size_queue(q);
    if (size == 0) {
        printf("Queue is empty!\n");
        return;
    }
    NodeQ* current = q->first;
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