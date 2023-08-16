#include <math.h>
#include <ctype.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "table.h"

void printMenu() {
    printf("\nВыберите дейтсвие:\n");
    printf("0)Выход\n");
    printf("1)Отсортировать таблицу\n");
    printf("2)Найти строку по ключу\n");
    printf("3)Распечатать таблицу\n");
    printf("4)Перезаписать файл\n");
}

void rewriteFile(const char* filename, vector* table) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }

    int size = sizeVector(table);
    for (int i = 0; i < size; i++) {
        value tmp = loadVector(table, i);
        fprintf(file, "%f %s\n", tmp.key, tmp.string);
    }

    fclose(file);
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

    vector* table = malloc(sizeof(vector));
    createVector(table, 0);

    char line[STRSIZE];
    while (fgets(line, sizeof(line), file) != NULL) {
        float key;
        char string[STRSIZE];
        sscanf(line, "%f %[^\n]", &key, string);

        value element;
        element.key = key;
        strcpy(element.string, string);
        resizeVector(table, sizeVector(table) + 1);
        writeVector(table, sizeVector(table) - 1, element);
    }

    fclose(file);

    printf("Исходная таблица выглядит так:\n");
    printTable(table);
    int choose = 1;
    float key;
    while (choose) {
        printMenu();
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                choose = 0;
                destroyVector(table);
                free(table);
                return 0;
            case 1:
                sortShake(table);
                printf("Таблица отсортирована:\n");
                printTable(table);
                break;
            case 2:
                if(checkSortTableDescending(table)) {
                    vector* reverseTable = malloc(sizeof(vector));
                    createVector(reverseTable, sizeVector(table));
                    vectorReverse(table, reverseTable);
                    printf("Введите ключ: ");
                    scanf("%f", &key);
                    value result = binarySearch(reverseTable, key);
                    if (result.key != 0) {
                        printf("| %12f | %s |\n", result.key, result.string);
                    } else {
                        printf("Указанного ключа в таблице нет\n");
                    }
                    destroyVector(reverseTable);
                    free(reverseTable);
                    break;
                } else if (checkSortTable(table) == 0) { //если таблица не отсортирована
                    printf("Для начала отсортируйте таблицу!\n");
                    break;
                } else {
                    printf("Введите ключ: ");
                    scanf("%f", &key);
                    value result = binarySearch(table, key);
                    if (result.key != 0) {
                        printf("| %12f | %s |\n", result.key, result.string);
                    } else {
                        printf("Указанного ключа в таблице нет\n");
                    }
                    break;
                } 
            case 3:
                printTable(table);
                break;
            case 4:
                rewriteFile(argv[1], table);
                printf("Файл успешно перезаписан!\n");
                break;
            default:
                printf("Указанного действия не существует!\n");
                break;
        }
    }

    destroyVector(table);
    return 0;
}
