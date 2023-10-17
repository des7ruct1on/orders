#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

void instruction() {
    printf("'pushb' - adds elements to back space\n");
    printf("'popf' - delets elements to front space\n");
    printf("'delq' - delets all elements in queue\n");
    printf("'size' - delets all elements in queue\n");
    printf("'sort' - you are using bubble sort for recorded deque\n"); // Допилить
    printf("'print' - output in terminal your queue\n");
    printf("'quit' - you will exit the program\n\n");
}

void swap(NodeQ* node1, NodeQ* node2) {
    int tmp = node1->value;
    node1->value = node2->value;
    node2->value = tmp;
}


void procedure_find_swap(Queue* q) {
    int swapped;
    NodeQ* ptr1;
    NodeQ* lptr = NULL;
    do {
        swapped = 0;
        ptr1 = q->first;

        while (ptr1->next != lptr) {
            if (ptr1->value > ptr1->next->value) {
                // Swap the values
                swap(ptr1,  ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void bubble_sort(Queue* q) {
    if (q->size == 0) {
        printf("Queue is empty. Nothing to sort.\n");
        return;
    }
    procedure_find_swap(q);
}

int main(int argc, const char *argv[]) {
    char choose[24]; // переменная выбора
    size_t size; // размер дека
    Queue* q = malloc(sizeof(Queue)); // выделяем память под очередь
    init_queue(q);
    int value; //значение дека
    while (true) {
        instruction();
        scanf("%s", choose);
        if (!strcmp(choose, "pushb")) {
            printf("\nEnter the value of element: ");
            scanf("%d", &value);
            push_back(q, value); //добавляем введенное значение спереди
        } else if (!strcmp(choose, "popf")) {
            value = pop_front(q); //взятие последнего элемента и его удаление
            printf("Element =%d was deleted\n", value);
        } else if (!strcmp(choose, "delq")) {
            delete_queue(q);
        } else if (!strcmp(choose, "sort")) {
            bubble_sort(q);
        } else if (!strcmp(choose, "print")) {
            print_queue(q);
        } else if (!strcmp(choose, "quit")) {
            delete_queue(q);
            free(q);
            break;
        } else if (!strcmp(choose, "size")) {
            size = size_queue(q);
            printf("Size: %lu\n", size);
        } else {
            printf("Unknown option, try again\n");
        }
    }
    return 0;
}