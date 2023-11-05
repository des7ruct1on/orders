#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deck.h"

void printChoose() { //вывод выбора действий
    printf("\nВыберите действие:\n");
    printf("0)Выход\n");
    printf("1)Создать рандомный дек\n");
    printf("2)Вывести содержимое дека\n");
    printf("3)Узнать размер дека\n");
    printf("4)Вставить элемент в начало\n");
    printf("5)Вставить элемент в конец\n");
    printf("6)Удалить первый элемент\n");
    printf("7)Удалить последний элемент\n");
    printf("8)Сортировка\n");
    printf("9)Опустошить дек\n");
}

void sortDequeBubble(Deque* deque) {
    if (deque->size > 0) {
        int n = deque->size;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                int current = (deque->front + j) % MAX_SIZE;
                int next = (deque->front + j + 1) % MAX_SIZE;

                if (deque->arr[current] > deque->arr[next]) {
                    // Swap elements
                    int temp = deque->arr[current];
                    deque->arr[current] = deque->arr[next];
                    deque->arr[next] = temp;
                }
            }
        }
    }
}

int main() {
    Deque deque;
    initializeDeque(&deque);

    int choice, value;

    do {
        printChoose();
        printf("Введите номер команды: ");
        scanf("%d", &choice);
        int random_size = 0;
        switch (choice) {
            case 1:
                random_size = rand() % 20 + 1;
                for (int i = 0; i < random_size; i++) {
                    value = rand() % 15;
                    insertFront(&deque, value);
                }
                printf("Рандомный дек создан.\n");
                break;
            case 2:
                displayDeque(&deque);
                break;
            case 3:
                printf("Размер дека: %d\n", getSize(&deque));
                break;
            case 4:
                printf("Введите значение для вставки в начало: ");
                scanf("%d", &value);
                insertFront(&deque, value);
                break;
            case 5:
                printf("Введите значение для вставки в конец: ");
                scanf("%d", &value);
                insertRear(&deque, value);
                break;
            case 6:
                deleteFront(&deque);
                break;
            case 7:
                deleteRear(&deque);
                break;
            case 8:
                sortDequeBubble(&deque);
                printf("Дек отсортирован.\n");
                break;
            case 9:
                clearDeque(&deque);
                printf("Дек опустошен.\n");
                break;
            case 0:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Ошибка! Несуществующее действие\n");
                break;
        }
    } while (choice != 0);

    return 0;
}