#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

void printChoose() { //вывод выбора действий
    printf("\nВыберите действие:\n");
    printf("0)Выход\n");
    printf("1)Создать рандомную очередь\n");
    printf("2)Вывести содержимое очереди\n");
    printf("3)Узнать размер очереди\n");
    printf("4)Вставить элемент в начало\n");
    printf("5)Удалить последний элемент\n");
    printf("6)Сортировка слиянием\n");
    printf("7)Опустошить очередь\n");
}

// Функция для сортировки слиянием двух очередей
void merge(queue *res, queue *q1, queue *q2) {
    queue tmp;
    initQueue(&tmp);

    while (!emptyQueue(q1) && !emptyQueue(q2)) {
        if (topBack(q1) > topBack(q2)) {
            pushFront(&tmp, popBack(q1));
        } else {
            pushFront(&tmp, popBack(q2));
        }
    }

    while (!emptyQueue(q1)) {
        pushFront(&tmp, popBack(q1));
    }

    while (!emptyQueue(q2)) {
        pushFront(&tmp, popBack(q2));
    }

    // Переворачиваем tmp и копируем его в res
    while (!emptyQueue(&tmp)) {
        pushFront(res, popBack(&tmp));
    }
}

// Функция для сортировки очереди слиянием
void mergeSort(queue *q) {
    if (sizeQueue(q) > 1) {
        queue q1, q2;
        initQueue(&q1);
        initQueue(&q2);

        int half_size = sizeQueue(q) / 2;

        for (int i = 0; i < half_size; i++) {
            pushFront(&q1, popBack(q));
        }

        while (!emptyQueue(q)) {
            pushFront(&q2, popBack(q));
        }

        mergeSort(&q1);
        mergeSort(&q2);

        merge(q, &q1, &q2);
    }
}



int main(int argc, const char *argv[]) {
    int choose = 1; // переменная выбора
    int numSize; // размер дека
    queue* q = malloc(sizeof(queue)); // выделяем память под очередь
    initQueue(q);
    int value; //значение дека
    while (choose) {
        printChoose();
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                deleteQueue(q);
                free(q);
                break;
            case 1:
                printf("Введите количество элементов ");
                scanf("%d", &numSize); //считываем размер очереди
                for (int i = 0; i < numSize; i++) {
                    value = rand() % 11;
                    pushFront(q, value);
                }
                printQueue(q);
                getchar();
                break;
            case 2:
                printQueue(q);
                getchar();
                break;
            case 3:
                numSize = sizeQueue(q); //присваиваем размер дека
                printf("\nРазмер очереди: %d", numSize);
                break;
            case 4:
                printf("\nВведите значение элемента: ");
                scanf("%d", &value);
                pushFront(q, value); //добавляем введенное значение спереди
                break;
            case 5:
                value = popBack(q); //взятие последнего элемента и его удаление
                printf("\nЭлемент =%d удален\n", value);
                break;
            case 6:
                mergeSort(q);
                printf("Отсортированная очередь: ");
                printQueue(q);
                break;
            case 7:
                deleteQueue(q);
                break;
        }
    }
    return 0;
}