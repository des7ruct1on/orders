#include <math.h>
#include <ctype.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "table.h"

//функция вывода меню
void print_menu() {
    printf("|=====================================|\n");
    printf("|Выберите дейтсвие:                   |\n");
    printf("|=====================================|\n");
    printf("|0. Выход                             |\n");
    printf("|1. Отсортировать таблицу             |\n");
    printf("|2. Найти строку по ключу             |\n");
    printf("|3. Распечатать таблицу               |\n");
    printf("|4. Перезаписать файл                 |\n");
    printf("|=====================================|\n");
}

void rewrite_file(const char* file_key, const char* file_string, vector* table) {//функция перезаписи файлов
    FILE* key_file = fopen(file_key, "w");//открываем файл ключей
    if (key_file == NULL) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }
    FILE* string_file = fopen(file_string, "w");//открываем файл строк
    if (string_file == NULL) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }
    int size = size_vector(table);
    for (int i = 0; i < size; i++) {//заптсываем в оба файла значения
        value tmp = print_vector(table, i);
        fprintf(key_file, "%s\n", tmp.key);
        fprintf(string_file, "%s\n", tmp.string);
    }
    fclose(key_file);
    fclose(string_file);
}
int main(int argc, char const* argv[]) {
    if (argc != 3) {
        printf("Используйте: %s <KEY=> <STRINGS=>\n", argv[0]);
        return 1;
    }

    FILE* file_key = fopen(argv[1], "r");//открываем файл ключей
    FILE* file_string = fopen(argv[2], "r");//открываем файл строк
    if (file_key == NULL || file_string == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    vector* table = malloc(sizeof(vector));
    create_vector(table, 0);

    char line_key[STRSIZE];//строка для считывания ключа
    char line_string[STRSIZE];//строка для считывания строки
    while (fgets(line_key, sizeof(line_key), file_key) != NULL && fgets(line_string, sizeof(line_string), file_string) != NULL) {
        char key[5];
        char string[STRSIZE];
        sscanf(line_key, "%s", key);
        sscanf(line_string, "%s", string);
        value element;
        strcpy(element.key, key);
        strcpy(element.string, string);
        resize_vector(table, size_vector(table) + 1);
        add_vector(table, size_vector(table) - 1, element);
    }
    fclose(file_key);
    fclose(file_string);
    printf("Исходная таблица выглядит так:\n");
    print_table(table);
    int choose = 1;
    char key_find[5];
    bool reverse_sorted = check_sort_table_reverse(table); //проверяем на отсортированность по убыванию
    while (choose) {
        print_menu();
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                destroy_vector(table);
                free(table);
                return 0;
            case 1:
                bubble_sort(table);
                printf(" Таблица отсортирована:\n");
                print_table(table);
                break;
            case 2:
                if (check_sort_table(table) == 0 && !reverse_sorted) { //если таблица не отсортирована
                    printf(" Для начала отсортируйте таблицу!\n");
                    break;
                } else {
                    printf("Введите ключ: ");
                    scanf(" %s", key_find);
                    value result = binary_search(table, key_find, reverse_sorted);
                    if (strcmp(result.key, "")) {
                        printf("| %12s | %s |\n", result.key, result.string);
                    } else {
                        printf(" Указанного ключа в таблице нет\n");
                    }
                    break;
                } 
            case 3:
                print_table(table);
                break;
            case 4:
                rewrite_file(argv[1], argv[2], table);
                printf("Файл успешно перезаписан!\n");
                break;
            default:
                printf("Указанного действия не существует!\n");
                break;
        }
    }

    destroy_vector(table);
    return 0;
}
