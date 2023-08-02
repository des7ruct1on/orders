#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void print_menu() { // функция меню
    printf("\n");
    printf("T|Menu|TTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
    printf("| 0. Выход                         |\n");
    printf("| 1. Распечатать список            |\n");
    printf("| 2. Добавить элемент в начало     |\n");
    printf("| 3. Добавить элемент в конец      |\n");
    printf("| 4. Добавить элемент по индексу   |\n");
    printf("| 5. Удалить элемент в начале      |\n");
    printf("| 6. Удалить элемент в конце       |\n");
    printf("| 7. Удалить элемент по индексу    |\n");
    printf("| 8. Узнать размер списка          |\n");
    printf("| 9. Сдвиг на 1 вперед             |\n");
    printf("|==================================|\n");
    printf("| Введите номер желаемого действия |\n");
    printf("|==================================|\n");
}

void shift(Node** head) {
    Node* tmp = (*head);
    *head = tmp->prev;
    (*head)->next = tmp;
    
}


int main(int argc, const char *argv[]) {
    Node* list = NULL; // объявляем список
    int choose = 1;
    char* element; // элемент списка
    int size = size_list(list); //размер списка
    int index = 1;
    while (choose) {
        print_menu();
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                destroy_list(list);
                //free(element);
                return 0;
            case 1:
                print_list(list);
                break;
            case 2:
                printf("Введите строку: ");
                element = (char*)malloc(STR_SIZE * sizeof(char)); // Выделяем память под элемент
                scanf(" %s", element);
                push_front(&list, element);
                break;
            case 3:
                printf("Введите строку: ");
                element = (char*)malloc(STR_SIZE * sizeof(char)); // Выделяем память под элемент
                scanf(" %s", element);
                push_back(&list, element);
                break;
            case 4:
                printf("Введите номер индекса: ");
                scanf("%d", &index);
                printf("Введите строку: ");
                element = (char*)malloc(STR_SIZE * sizeof(char)); // Выделяем память под элемент
                scanf(" %s", element);
                push_index(&list, element, index);
                break;
            case 5:
                delete_front(&list);
                printf("Удаление завершено!\n");
                print_list(list);
                break;
            case 6:
                delete_back(&list);
                printf("Удаление завершено!\n");
                print_list(list);
                break;
            case 7:
                printf("Введите номер индекса: ");
                scanf("%d", &index);
                delete_index(&list, index);
                if (size != size_list(list)) {
                    printf("Удаление завершено!\n");
                }
                print_list(list);
                break;
            case 8:
                size = size_list(list);
                printf("Размер списка: %d\n", size);
                break;
            case 9:
                shift(&list);
                print_list(list);
                break;
            default:
                printf("Такого действия не существует\n");
                break;
        }
    }
    return 0;
}
