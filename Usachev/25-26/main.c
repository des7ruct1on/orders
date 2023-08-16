#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "stack.h"

void printMenu() {
    printf("\nВыберите действие\n");
    printf("0)Выход\n");
    printf("1)Вывести содержимое стека\n");
    printf("2)Узнать размер стека\n");
    printf("3)Добавить элемент\n");
    printf("4)Удалить элемент\n");
    printf("5)Сортировка пузырьком\n");
    printf("6)Опустошить стек\n");
    printf("\n");
}

void bubbleSort(stack* s) {
    int n = sizeStack(s);
    if (n <= 1) {
        return; // Стек уже отсортирован или пустой
    }

    stack* tempStack = (stack*)malloc(sizeof(stack));
    stackInit(tempStack);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Извлекаем два верхних элемента из стека
            int elem1 = s->top->value;
            popBack(s);
            int elem2 = s->top->value;
            popBack(s);

            if (elem1 > elem2) {
                // Если элементы не в правильном порядке, меняем их местами
                pushBack(tempStack, elem1);
                pushBack(s, elem2);
            } else {
                pushBack(tempStack, elem2);
                pushBack(s, elem1);
            }
        }

        // Переносим отсортированные элементы обратно в исходный стек
        while (!emptyStack(tempStack)) {
            int elem = tempStack->top->value;
            popBack(tempStack);
            pushBack(s, elem);
        }
    }

    // Освобождаем временный стек
    free(tempStack);
}

int main() {
    stack* s = (stack*)malloc(sizeof(stack));
    stackInit(s);
    int choose = 1;
    int value;
    int size;
    while(choose) {
        printMenu();
        scanf("%d", &choose);
        switch(choose) {
        case 0:
            stackDelete(s);
            free(s);
            return 0;
        case 1:
            stackPrint(s);
            break;
        case 2:
            size = sizeStack(s);
            printf("Размер стека: %d\n", size);
            break;
        case 3:
            printf("Введите значение элемента: ");
            scanf("%d", &value);
            pushBack(s, value);
            break;
        case 4:
            popBack(s);
            break;
        case 5:
            bubbleSort(s);
            stackPrint(s);
            break;
        case 6:
            stackDelete(s);
            break;
        default:
            printf("Указанного действия не существует!\n");
            break;
        }
    }
    return 0;
}