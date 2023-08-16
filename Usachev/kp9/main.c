#include <math.h>
#include <ctype.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "table.h"

void printMenu() {//функция вывода меню
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

void rewriteFile(const char* fileKey, const char* fileString, vector* table) {//функция перезаписи файлов
    FILE* keyFile = fopen(fileKey, "w");//открываем файл ключей
    if (keyFile == NULL) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }
    FILE* stringFile = fopen(fileString, "w");//открываем файл строк
    if (stringFile == NULL) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }
    int size = sizeVector(table);
    for (int i = 0; i < size; i++) {//заптсываем в оба файла значения
        value tmp = printVector(table, i);
        fprintf(keyFile, "%f\n", tmp.key);
        fprintf(stringFile, "%s\n", tmp.string);
    }
    fclose(keyFile);
    fclose(stringFile);
}
int main(int argc, char const* argv[]) {
    if (argc != 3) {
        printf("Используйте: %s <KEY> <STRINGS>\n", argv[0]);
        return 1;
    }

    FILE* fileKey = fopen(argv[1], "r");//открываем файл ключей
    FILE* fileString = fopen(argv[2], "r");//открываем файл строк
    if (fileKey == NULL || fileString == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    vector* table = malloc(sizeof(vector));
    createVector(table, 0);

    char lineKey[STRSIZE];//строка для считывания ключа
    char lineString[STRSIZE];//строка для считывания строки
    while (fgets(lineKey, sizeof(lineKey), fileKey) != NULL && fgets(lineString, sizeof(lineString), fileString) != NULL) {
        float key;
        char string[STRSIZE];
        sscanf(lineKey, "%f", &key);
        sscanf(lineString, "%s", string);
        value element;
        element.key = key;
        strcpy(element.string, string);
        resizeVector(table, sizeVector(table) + 1);
        writeVector(table, sizeVector(table) - 1, element);
    }
    fclose(fileKey);
    fclose(fileString);
    printf(" Исходная таблица выглядит так:\n");
    printTable(table);
    int choose = 1;
    float key;
    bool reverseSorted = checkSortTableReverse(table);//проверяем на отсортированность по убыванию
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
                bubbleSort(table);
                printf(" Таблица отсортирована:\n");
                printTable(table);
                break;
            case 2:
                if (checkSortTable(table) == 0 && !reverseSorted) { //если таблица не отсортирована
                    printf(" Для начала отсортируйте таблицу!\n");
                    break;
                } else {
                    printf("Введите ключ: ");
                    scanf("%f", &key);
                    value result = binarySearch(table, key, reverseSorted);
                    if (result.key != 0) {
                        printf("| %12f | %s |\n", result.key, result.string);
                    } else {
                        printf(" Указанного ключа в таблице нет\n");
                    }
                    break;
                } 
            case 3:
                printTable(table);
                break;
            case 4:
                rewriteFile(argv[1], argv[2], table);
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
