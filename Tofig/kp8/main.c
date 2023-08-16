#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void deleteKthElement(Node** head, int k) {
    Node* current = (*head)->next;
    Node* prev = *head;
    int count = 1;

    while (current != NULL) {
        if (count % k == 0) {
            Node* toDelete = current;
            prev->next = current->next;
            current = current->next;
            free(toDelete);
        } else {
            prev = current;
            current = current->next;
        }
        count++;
    }
}

void printMenu() { // функция меню
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
    printf("9)Удалить каждый k-ый элемент\n");
    printf("\n");
    printf("Введите номер желаемого действия\n");
}

int main(int argc, const char *argv[]) {
    Node* head = malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    int choose = 1;
    int element; // элемент списка
    int k = 1;
    int size = sizeList(head); //размер списка
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
                printf("Введите значение: ");
                scanf(" %d", &element); 
                pushFront(&head, element);
                break;
            case 3:
                printf("Введите значение: ");
                scanf(" %d", &element); 
                pushBack(&head, element);
                break;
            case 4:
                printf("Введите номер индекса: ");
                scanf("%d", &index);
                printf("Введите значение: ");
                scanf(" %d", &element); 
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
                printf("Введите значение k:");
                scanf("%d", &k);
                deleteKthElement(&head, k);
                break;
            default:
                printf("Такого действия не существует\n");
                break;
        }
    }
    return 0;
}