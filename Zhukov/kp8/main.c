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
    printf("|7. |Очистить элементы до и после элемента равному введенному значению     |\n");
    printf("|==========================================================================|\n");
    printf("|Введите номер желаемого действия                                          |\n");
    printf("|==========================================================================|\n");
}

void task(Linked_list* list, Complex val) {
    Node* current = list->barrier->next; // Пропускаем барьерный элемент
    int count_prev = 0;
    int count_post = 0;
    bool found = false;
    while(current != NULL) {
        if (current->data.im == val.im && current->data.real == val.real) {
            found = true;
        }
        if (!found) {
            count_prev++;
        } else {
            count_post++;
        }
        current = current->next;
    }
    if (!found) {
        printf("Такого элемента не существует в списке!\n");
        return;
    }
    for (int i = 0; i < count_prev; i++) {
        pop_front(list);
    }
    for (int i = 0; i < count_post - 1; i++) {
        pop_back(list);
    }
}

int main(int argc, const char *argv[]) {
    Linked_list list;
    init_list(&list);
    int choose = 1;
    int _real; // действ часть
    int _im; // мнимая часть
    int size; //размер списка
    int index = 1;
    Complex element; // элемент списка 
    while(choose) {
        print_menu(); 
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                printf("\nЗавершение работы...\n");
                clear_list(&list);
                return 0;
            case 1:
                print_list(&list);
                break;
            case 2:
                printf("Введите значение элемента действительной части: ");
                scanf("%d", &_real);
                printf("Введите значение элемента мнимой части: ");
                scanf("%d", &_im);
                element.real = _real;
                element.im = _im;
                if (_real != 0 && _im != 0) {
                    append(&list, element);
                }
                print_list(&list);
                break;
            case 3:
                printf("Введите значение элемента действительной части: ");
                scanf("%d", &_real);
                printf("Введите значение элемента мнимой части: ");
                scanf("%d", &_im);
                element.real = _real;
                element.im = _im;
                printf("Введите индекс: ");
                scanf("%d", &index);
                if (_real != 0 && _im != 0) {
                    insert_at(&list, index, element);
                }
                print_list(&list);
                break;
            case 4:
                pop_back(&list);
                printf("Удаление завершено!\n");
                print_list(&list);
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
                printf("Введите значение элемента действительной части: ");
                scanf("%d", &_real);
                printf("Введите значение элемента мнимой части: ");
                scanf("%d", &_im);
                element.real = _real;
                element.im = _im;
                task(&list, element);
                break;
            default:
                printf("Такого действия не существует\n");
                break;
        }
    }
    return 0;
}