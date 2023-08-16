#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

void printMenu() { // функция меню
    printf("\n");
    printf("|=========================================================================|\n");
    printf("|0. Выход                                                                 |\n");
    printf("|1. Распечатать список                                                    |\n");
    printf("|2. Добавить элемент в начало                                             |\n");
    printf("|3. Добавить элемент в конец                                              |\n");
    printf("|4. Добавить элемент по индексу                                           |\n");
    printf("|5. Удалить элемент в начале                                              |\n");
    printf("|6. Удалить элемент в конце                                               |\n");
    printf("|7. Удалить элемент по индексу                                            |\n");
    printf("|8. Узнать размер списка                                                  |\n");
    printf("|9. Очистить список, если в нем есть элемент, равный заданному значению   |\n");
    printf("|=========================================================================|\n");
    printf("|Введите номер желаемого действия                                         |\n");
    printf("|=========================================================================|\n");
}

void task(Node** head, char* element) { //функция задания
    Node* current = *head;
    bool needClear = false;
    do { //проверяем на совпадение элементов
        if (strcmp(element, convertToStr(current->data)) == 0) {
            needClear = true;
            break;
        }
        current = current->next;
    } while (current != *head);
    if (needClear) { // найдено совпадение
        destroyList(*head);
        *head = NULL;
        return;
    } else { // иначе
        printf("Элемент %s не содержится в списке\n", element);
        return;
    }
}

int main(int argc, const char *argv[]) {
    Node* head = NULL; //изначально "голова" = нулю
    int choose = 1;
    char element[5]; // элемент списка
    numbers num; 
    int size = sizeList(head); //размер списка
    int index = 1;
    while(choose) {
        printMenu(); 
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                printf("\nЗавершение работы...\n");
                destroyList(head);
                return 0;
            case 1:
                printList(head);
                break;
            case 2:
                printf("Введите значение элемента: ");
                scanf(" %s", element); 
                num = convertToNum(element); //конвертируем строку в цифру из enum
                if(num == -1) {
                    break;
                }
                pushFront(&head, num);
                break;
            case 3:
                printf("Введите значение элемента: ");
                scanf(" %s", element); 
                num = convertToNum(element); //конвертируем строку в цифру из enum
                if(num == -1) {
                    break;
                }
                pushBack(&head, num);
                break;
            case 4:
                printf("Введите номер индекса: ");
                scanf("%d", &index);
                printf("Введите значение элемента: ");
                scanf(" %s", element); 
                num = convertToNum(element); //конвертируем строку в цифру из enum
                if(num == -1) {
                    break;
                }
                pushIndex(&head, num, index);
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
                printf("Введите значение элемента:");
                scanf(" %s", element); 
                task(&head, element);
                printList(head);
                break;
            default:
                printf("Такого действия не существует\n");
                break;
        }
    }
    return 0;
}