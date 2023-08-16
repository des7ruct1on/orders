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
    printf("8)Удалить максимальный элемент\n");
    printf("9)Удалить минимальный элемент\n");
    printf("10)Опустошить дек\n");
}

void removeMax(deck *D) {
    if (empty(D)) {
        printf("Дек пустой.\n");
        return;
    }
    
    // Поиск максимального элемента
    int maxVal = D->first->value;
    element *curr = D->first->next;
    while (curr != NULL) {
        if (curr->value > maxVal) {
            maxVal = curr->value;
        }
        curr = curr->next;
    }
    
    // Удаление максимального элемента
    curr = D->first;
    while (curr != NULL) {
        if (curr->value == maxVal) {
            // Если элемент находится в начале дека
            if (curr->prev == NULL) {
                D->first = curr->next;
                if (curr->next != NULL) {
                    curr->next->prev = NULL;
                }
            }
            // Если элемент находится в конце дека
            else if (curr->next == NULL) {
                D->last = curr->prev;
                curr->prev->next = NULL;
            }
            // Если элемент находится в середине дека
            else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }
            free(curr);
            D->size--;
            printf("Максимальный элемент %d успешно удален из дека.\n", maxVal);
            return;
        }
        curr = curr->next;
    }
    
    printf("Максимальный элемент не найден в деке.\n");
}

void removeMin(deck *D) {
    if (empty(D)) {
        printf("Дек пустой.\n");
        return;
    }
    
    // Поиск минимального элемента
    int minVal = D->first->value;
    element *curr = D->first->next;
    while (curr != NULL) {
        if (curr->value < minVal) {
            minVal = curr->value;
        }
        curr = curr->next;
    }
    
    // Удаление минимального элемента
    curr = D->first;
    while (curr != NULL) {
        if (curr->value == minVal) {
            // Если элемент находится в начале дека
            if (curr->prev == NULL) {
                D->first = curr->next;
                if (curr->next != NULL) {
                    curr->next->prev = NULL;
                }
            }
            // Если элемент находится в конце дека
            else if (curr->next == NULL) {
                D->last = curr->prev;
                curr->prev->next = NULL;
            }
            // Если элемент находится в середине дека
            else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }
            free(curr);
            D->size--;
            printf("Минимальный элемент %d успешно удален из дека.\n", minVal);
            return;
        }
        curr = curr->next;
    }
    
    printf("Минимальный элемент не найден в деке.\n");
}

int main(int argc, const char *argv[]) {
    int choose = 1; // переменная выбора
    int numSize; // размер дека
    deck *D = malloc(sizeof(deck)); // выделяем память под дек
    deck *D1 = malloc(sizeof(deck));
    initDeck(D);
    int value; //значение дека
    while (choose) {
        printChoose();
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                deleteDeck(D);
                deleteDeck(D1);
                break;
            case 1:
                printf("Введите количество элементов ");
                scanf("%d", &numSize); //считываем размер дека
                for (int i = 0; i < numSize; i++) {
                    value = rand() % 11;
                    pushFront(D, value);
                }
                printDeck(D);
                getchar();
                break;
            case 2:
                printDeck(D);
                getchar();
                break;
            case 3:
                numSize = size(D); //присваиваем размер дека
                printf("\nРазмер дека: %d", numSize);
                break;
            case 4:
                printf("\nВведите значение элемента: ");
                scanf("%d", &value);
                pushFront(D, value); //добавляем введенное значение спереди
                break;
            case 5:
                printf("\nВведите значение элемента: ");
                scanf("%d", &value);
                pushBack(D, value); //добавляем сзади
                break;
            case 6:
                value = popFront(D); //взятие первого элемента и его удаление
                printf("\nЭлемент =%d удален\n", value);
                break;
            case 7:
                value = popBack(D); //взятие последнего элемента и его удаление
                printf("\nЭлемент =%d удален\n", value);
                break;
            case 8:
                removeMax(D);
                printDeck(D);
                break;
            case 9:
                removeMin(D);
                printDeck(D);
                break;
            case 10:
                deleteDeck(D);
                D = malloc(sizeof(deck));
                initDeck(D);
                break;
        }
    }
    return 0;
}