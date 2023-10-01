#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

// функция меню
void print_menu() { // функция меню
    printf("\n");
    printf("|==========================================================================|\n");
    printf("|0 - Выход                                                                 |\n");
    printf("|1 - Распечатать список                                                    |\n");
    printf("|2 - Добавить элемент в начало                                             |\n");
    printf("|3 - Добавить элемент в конец                                              |\n");
    printf("|4 - Добавить элемент по индексу                                           |\n");
    printf("|5 - Удалить элемент в начале                                              |\n");
    printf("|6 - Удалить элемент в конце                                               |\n");
    printf("|7 - Удалить элемент по индексу                                            |\n");
    printf("|8 - Узнать размер списка                                                  |\n");
    printf("|9 - Дополнить до указанной длины список указанным значением               |\n");
    printf("|==========================================================================|\n");
    printf("|Введите номер желаемого действия                                          |\n");
    printf("|==========================================================================|\n");
}


void task(Node** head, int k, bool elem) {
    if (k <= size_list(*head)) {
        return;
    } else {
        while (k > size_list(*head)) {
            push_back(head, elem);
        }
    }
}

int main(int argc, const char *argv[]) {
    //изначально  NULL
    Node* head = NULL; 
    int choose = 1;
    // элемент списка
    char element[6]; 
    bool elem_add; 
    //размер списка
    int size = size_list(head); 
    int index = 1;
    int k;
    while(choose) {
        print_menu(); 
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                printf("\nЗавершение работы...\n");
                delete_list(head);
                return 0;
            case 1:
                print_list(head);
                break;
            case 2:
                printf("Введите значение элемента: ");
                scanf(" %s", element); 
                if (!strcmp(element, "True") || !strcmp(element, "true")) {
                    elem_add = true;
                } else if (!strcmp(element, "False") || !strcmp(element, "false")) {
                    elem_add = false;
                } else {
                    break;
                }
                push_front(&head, elem_add);
                break;
            case 3:
                printf("Введите значение элемента: ");
                scanf(" %s", element); 
                if (!strcmp(element, "True") || !strcmp(element, "true")) {
                    elem_add = true;
                } else if (!strcmp(element, "False") || !strcmp(element, "false")) {
                    elem_add = false;
                } else {
                    break;
                }
                push_back(&head, elem_add);
                break;
            case 4:
                printf("Введите номер индекса: ");
                scanf("%d", &index);
                printf("Введите значение элемента: ");
                scanf(" %s", element); 
                if (!strcmp(element, "True") || !strcmp(element, "true")) {
                    elem_add = true;
                } else if (!strcmp(element, "False") || !strcmp(element, "false")) {
                    elem_add = false;
                } else {
                    break;
                }
                push_index(&head, elem_add, index);
                break;
            case 5:
                pop_front(&head);
                printf("Удаление завершено!\n");
                print_list(head);
                break;
            case 6:
                pop_back(&head);
                printf("Удаление завершено!\n");
                print_list(head);
                break;
            case 7:
                printf("Введите номер индекса: ");
                scanf("%d", &index);
                pop_index(&head, index);
                if (size != size_list(head)) {
                    printf("Удаление завершено!\n");
                }
                print_list(head);
                break;
            case 8:
                size = size_list(head);
                printf("Размер списка: %d\n", size);
                break;
            case 9:
                printf("Введите значение длины: ");
                scanf("%d", &k);
                printf("Введите значение: ");
                scanf(" %s", element); 
                if (!strcmp(element, "True") || !strcmp(element, "true")) {
                    elem_add = true;
                } else if (!strcmp(element, "False") || !strcmp(element, "false")) {
                    elem_add = false;
                } else {
                    break;
                }
                task(&head, k, elem_add);
                print_list(head);
                break;
            default:
                printf("Выбрана невозможная опция\n");
                break;
        }
    }
    return 0;
}