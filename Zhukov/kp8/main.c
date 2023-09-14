#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

void print_menu() { // функция меню
    printf("\n");
    printf("|===T======================================================================|\n");
    printf("|0. |Выход                                                                 |\n");
    printf("|1. |Распечатать список                                                    |\n");
    printf("|2. |Добавить элемент в конец                                              |\n");
    printf("|3. |Добавить элемент по индексу                                           |\n");
    printf("|4. |Удалить элемент в конце                                               |\n");
    printf("|5. |Удалить элемент по индексу                                            |\n");
    printf("|6. |Узнать размер списка                                                  |\n");
    printf("|7. |Очистить список, если в нем есть элемент, равный заданному значению   |\n");
    printf("|==========================================================================|\n");
    printf("|Введите номер желаемого действия                                          |\n");
    printf("|==========================================================================|\n");
}

int main(int argc, const char *argv[]) {
    Linked_list list;
    init_list(&list);
    int choose = 1;
    int _real; // действ часть
    int _im; // мнимая часть
    int size = get_size(&list); //размер списка
    int index = 1;
    while(choose) {
        print_menu(); 
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                printf("\nЗавершение работы...\n");
                clear_list(&list);
                return 0;
            case 1:
                printList(&list);
                break;
            case 2:
                Complex element; // элемент списка 
                printf("Введите значение элемента действительной части: ");
                scanf("%d", &_real);
                printf("Введите значение элемента мнимой части: ");
                scanf("%d", &_im);
                element.real = _real;
                element.im = _im;
                append(&list, element);
                printList(&list);
                break;
            case 3:
                Complex element; // элемент списка 
                printf("Введите значение элемента действительной части: ");
                scanf("%d", &_real);
                printf("Введите значение элемента мнимой части: ");
                scanf("%d", &_im);
                element.real = _real;
                element.im = _im;
                printf("Введите индекс: ");
                scanf("%d", &index);
                insert_at(&list, index, element);
                printList(&list);
                break;
            case 4:
                pop_back(&list);
                printf("Удаление завершено!\n");
                printList(&list);
                break;
            case 5:
                printf("Введите индекс: ");
                scanf("%d", &index);
                printf("Удаление завершено!\n");
                remove_index(&list, index);
                break;
            case 6:
                size = get_size(&list);
                printf("Размер списка: %d\n", size);
                break;
            case 7:
                
                break;
            default:
                printf("Такого действия не существует\n");
                break;
        }
    }
    return 0;
}