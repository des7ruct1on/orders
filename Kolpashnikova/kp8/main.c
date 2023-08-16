#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void printMenu() {
    printf("\n");
    printf("0)Выход\n");
    printf("1)Распечатать список\n");
    printf("2)Добавить элемент в начало\n");
    printf("3)Добавить элемент в конец\n");
    printf("4)Добавить элемент по индексу\n");
    printf("5)Удалить элемент в начале\n");
    printf("6)Удалить элемент в конце\n");
    printf("7)Удалить элемент по индексу\n");
    printf("8)Узнать размер списка\n");
    printf("9)добавить k экземпляров последнего в начало списка\n");
    printf("\n");
    printf("Введите номер желаемого действия\n");
}

float getLast(node** head) {
    node* current = *head;
    while(current->next != NULL) {
        current = current->next;
    }
    return current->data;
}

void task(node** head, int k) {
    float value = getLast(head);
    for(int i = 0; i < k; i++) {
        pushFront(head, value);
    }
    printList(*head);
}

int main(int argc, const char *argv[]) { 
    node* head = NULL;
    int choose = 1;
    float element;
    int k = 1;
    int size = sizeList(head);
    int index = 1;
    while(choose) {
        printMenu();
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                printf("\nЗавершение работы...\n");
                destroy(head);
                return 0;
            case 1:
                printList(head);
                break;
            case 2:
                printf("Введите число: ");
                scanf("%f", &element);
                pushFront(&head, element);
                break;
            case 3:
                printf("Введите число: ");
                scanf("%f", &element);
                pushBack(&head, element);
                break;
            case 4:
                printf("Введите номер индекса: ");
                scanf("%d", &index);
                printf("Введите число: ");
                scanf("%f", &element);
                pushIndex(&head, element, index);
                break;
            case 5:
                deleteFront(&head);
                printf("Удаление завершено!\n");
                printList(head);
                break;
            case 6:
                deleteBack(&head);
                printf("Удаление завершено!\n");
                printList(head);
                break;
            case 7:
                printf("Введите номер индекса: ");
                scanf("%d", &index);
                deleteIndex(&head, index);
                if (size != sizeList(head)) {
                    printf("Удаление завершено!\n");
                }
                printList(head);
                break;
            case 8:
                size = sizeList(head);
                printf("Размер списка: %d\n", size);
                break;
            case 9:
                printf("Введите значение k: ");
                scanf("%d", &k);
                task(&head, k);
                break;
            default:
                printf("Такого действия не существует\n");
                break;
        }
    }
    return 0;
}
