#include <math.h>
#include <ctype.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "table.h"

void print_menu() {
    printf("\n\n");
    printf("|-------------------------| \n");
    printf("| 0. Выход                | \n");
    printf("| 1. Отсортировать таблицу| \n");
    printf("| 2. Найти строку по ключу| \n");
    printf("| 3. Распечатать таблицу  | \n");
    printf("| 4. Перезаписать файл    | \n");
    printf("|-------------------------| \n");
    printf("\nВыберите дейтсвие:\n");
}

//функция перезаписи файла
void update_file(const char* filename, vector* table) { 
    FILE* file = fopen(filename, "w"); //открываем файл на запись
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    int size = size_vector(table);
    for (int i = 0; i < size; i++) {
        data tmp = get_vector(table, i); //берем каждый элемент вектора
        fprintf(file, "%s %s\n", tmp.key, tmp.string); //записываем в файл
    }

    fclose(file);
}

// Функция просеивания для пирамидальной сортировки
void heapify(vector* table, int n, int i, bool reverse_sorted) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (!reverseSorted) {
        if (left < n && cmp_key(get_vector(table, left), get_vector(table, largest)) > 0) {
            largest = left;
        }

        if (right < n && cmp_key(get_vector(table, right), get_vector(table, largest)) > 0) {
            largest = right;
        }
    } else {
        if (left < n && cmp_key(get_vector(table, left), get_vector(table, largest)) < 0) {
            largest = left;
        }

        if (right < n && cmp_key(get_vector(table, right), get_vector(table, largest)) < 0) {
            largest = right;
        }
    }

    if (largest != i) {
        swap(&table->data[i], &table->data[largest]);
        heapify(table, n, largest, reverse_sorted);
    }
}

// Функция пирамидальной сортировки
void pyramid_sort(vector* table) {
    int n = size_vector(table);

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(table, n, i, false); // для сортировки по возрастанию
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&table->data[0], &table->data[i]);
        heapify(table, i, 0, false); // для сортировки по возрастанию
    }
}

int main(int argc, char const* argv[]) {
    if (argc != 2) {
        printf("Используйте: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    vector* table = malloc(sizeof(vector)); //выделяем память под вектор
    create_vector(table, 0);

    char line[STR_SIZE]; //линия из файла
    while (fgets(line, sizeof(line), file) != NULL) {
        char key[6];
        char string[STR_SIZE];
        sscanf(line, "%5s %[^\n]", key, string); //считываем значения

        data elem;
        strcpy(elem.key, key); //добавляем их к элементу
        strcpy(elem.string, string);
        resize_vector(table, size_vector(table) + 1);
        add_vector(table, size_vector(table) - 1, elem); 
    }

    fclose(file);

    int size = size_vector(table);
    printf("Исходная таблица\n");
    printf("|+>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<+|\n");
    printf("|  Ключ  | Значение                          |\n");
    printf("|+>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<+|\n");
    for (int i = 0; i < size; i++) {
        data tmp = get_vector(table, i);
        printf("| %6s | %-33s |\n", tmp.key, tmp.string);
    }
    printf("|+>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<>=<+|\n");
    char find[6]; //переменная для поиска по ключу
    bool reversed = check_table_reversed(table); //проверяем на отсортированность по убыванию
    int choose = 1;
    while(choose) {
        print_menu();
        scanf("%d", &choose);
        switch(choose) {
            case 0: //выход
                choose = 0;
                destroy_vector(table);
                free(table);
                return 0;
                break;
            case 1: //сортировка
                if (check_table_sorted(table)) {
                    break;
                }
                pyramid_sort(table);
                print_table(table);
                break;
            case 2: //поиск
                if (check_table_sorted(table) == 0 && !reversed) { //если таблица не отсортирована
                    printf("Для начала отсортируйте таблицу!\n");
                    break;
                } else {
                    printf("Введите ключ: ");
                    scanf("%5s", find);
                    if (strcmp(binary_search(table, find, reversed).key, "")) {
                        printf("| %6s | %s |\n", binary_search(table, find, reversed).key, binary_search(table, find, reversed).string);
                    } else {
                        printf("Указанного ключа в таблице нет\n");
                    }
                    break;
                }
            case 3: //вывод таблицы
                print_table(table);
                break;
            case 4:
                update_file(argv[1], table);
                printf("Файл успешно перезаписан!\n");
                break;
            default:
                printf("Указанного действия не существует!\n");
                break;
            
        }
    }
    return 0;
}
