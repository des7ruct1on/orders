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
    printf("|9 - Выполнить попарный обмен элементов списка                             |\n");
    printf("|==========================================================================|\n");
    printf("|Введите номер желаемого действия                                          |\n");
    printf("|==========================================================================|\n");
}


void task(Node** head) {
    Node* current = *head;

    while (current != NULL && current->next != NULL) {
        
        num temp = current->value;
        current->value = current->next->value;
        current->next->value = temp;

        current = current->next->next; // идем к след паре
    }
}

int main(int argc, const char *argv[]) {
    //изначально  NULL
    Node* head = NULL; 
    int choose = 1;
    // элемент списка
    char element[5]; 
    num number; 
    //размер списка
    int size = size_list(head); 
    int index = 1;
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
                number = convert_num(element); //преобразование в enum
                if(number == -1) {
                    break;
                }
                push_front(&head, number);
                break;
            case 3:
                printf("Введите значение элемента: ");
                scanf(" %s", element); 
                number = convert_num(element); //конвертируем строку в цифру из enum
                if(number == -1) {
                    break;
                }
                push_back(&head, number);
                break;
            case 4:
                printf("Введите номер индекса: ");
                scanf("%d", &index);
                printf("Введите значение элемента: ");
                scanf(" %s", element); 
                number = convert_num(element); //конвертируем строку в цифру из enum
                if(number == -1) {
                    break;
                }
                push_index(&head, number, index);
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
                task(&head);
                print_list(head);
                break;
            default:
                printf("Выбрана невозможная опция\n");
                break;
        }
    }
    return 0;
}