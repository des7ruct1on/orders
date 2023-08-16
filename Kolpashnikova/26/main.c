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

// Слияние двух отсортированных деков
deck* merge(deck* left, deck* right) {
    deck* result = malloc(sizeof(deck));
    initDeck(result);

    while (!empty(left) && !empty(right)) {
        if (topFront(left) <= topFront(right)) {
            pushBack(result, popFront(left));
        } else {
            pushBack(result, popFront(right));
        }
    }

    // Добавляем оставшиеся элементы из левого дека
    while (!empty(left)) {
        pushBack(result, popFront(left));
    }

    // Добавляем оставшиеся элементы из правого дека
    while (!empty(right)) {
        pushBack(result, popFront(right));
    }

    return result;
}

// Рекурсивная функция сортировки слиянием для дека
void mergeSort(deck* D) {
    if (size(D) <= 1) {
        return;  // Базовый случай: дек уже отсортирован или пустой
    }

    deck* left = malloc(sizeof(deck));
    deck* right = malloc(sizeof(deck));
    initDeck(left);
    initDeck(right);

    int middle = size(D) / 2;

    // Разделяем дек на две части
    for (int i = 0; i < middle; i++) {
        pushBack(left, popFront(D));
    }

    while (!empty(D)) {
        pushBack(right, popFront(D));
    }

    // Рекурсивно сортируем каждую часть
    mergeSort(left);
    mergeSort(right);

    // Слияние отсортированных частей
    deck* sortedDeck = merge(left, right);

    // Копируем отсортированный дек обратно в исходный
    while (!empty(sortedDeck)) {
        pushBack(D, popFront(sortedDeck));
    }

    // Освобождаем память
    deleteDeck(sortedDeck);
    deleteDeck(left);
    deleteDeck(right);
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
                mergeSort(D);
                printDeck(D);
                break;
            case 9:
                deleteDeck(D);
                D = malloc(sizeof(deck));
                initDeck(D);
                break;
        }
    }
    return 0;
}