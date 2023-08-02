#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

void print_choose() { //вывод выбора действий
    printf("\nВыберите действие:\n");
    printf("0)Выход\n");
    printf("1)Создать рандомную очередь\n");
    printf("2)Вывести содержимое очереди\n");
    printf("3)Узнать размер очереди\n");
    printf("4)Вставить элемент в начало\n");
    printf("5)Удалить последний элемент\n");
    printf("6)Сортировка простой вставкой\n");
    printf("7)Опустошить очередь\n");
}

void insertionSort(queue* q) {
    int size = size_queue(q);
    if (size <= 1) {
        return;
    }

    element* sorted = q->first; // Указатель на отсортированную часть очереди
    element* curr = sorted->next; // Указатель на следующий элемент после отсортированной части

    while (curr != NULL) {
        element* temp = curr;
        curr = curr->next; // Переходим к следующему элементу

        // Удаляем temp из очереди
        if (temp == q->first) {
            q->first = temp->next;
        } else {
            element* prev = q->first;
            while (prev->next != temp) {
                prev = prev->next;
            }
            prev->next = temp->next;
        }

        // Вставляем temp в отсортированную часть
        if (temp->value < sorted->value) {
            temp->next = sorted;
            sorted = temp;
        } else {
            element* prev = sorted;
            while (prev->next != NULL && prev->next->value < temp->value) {
                prev = prev->next;
            }
            temp->next = prev->next;
            prev->next = temp;
        }
    }

    q->first = sorted; // Обновляем указатель на первый элемент очереди
}







int main(int argc, const char *argv[]) {
    int choose = 1; // переменная выбора
    int numSize; // размер дека
    queue* q = malloc(sizeof(queue)); // выделяем память под очередь
    init_queue(q);
    int value; //значение дека
    while (choose) {
        print_choose();
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                delete_queue(q);
                free(q);
                break;
            case 1:
                printf("Введите количество элементов ");
                scanf("%d", &numSize); //считываем размер очереди
                for (int i = 0; i < numSize; i++) {
                    value = rand() % 11;
                    push_back(q, value);
                }
                print_queue(q);
                getchar();
                break;
            case 2:
                print_queue(q);
                getchar();
                break;
            case 3:
                numSize = size_queue(q); //присваиваем размер дека
                printf("\nРазмер очереди: %d", numSize);
                break;
            case 4:
                printf("\nВведите значение элемента: ");
                scanf("%d", &value);
                push_back(q, value); //добавляем введенное значение спереди
                break;
            case 5:
                value = pop_front(q); //взятие последнего элемента и его удаление
                printf("\nЭлемент =%d удален\n", value);
                break;
            case 6:
                insertionSort(q);
                printf("Отсортированная очередь: ");
                print_queue(q);
                break;
            case 7:
                delete_queue(q);
                break;
        }
    }
    return 0;
}