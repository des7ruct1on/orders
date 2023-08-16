#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/abiturient.h"

void printMenu() {
    printf("\texit - выход\n");
    printf("\tinfo - информация об абитуриенте(info [Фамилия] [Инициалы])\n");
    printf("\tadd - добавление абитуриента(add [Фамилия] [Инициалы] [Пол] [Школа] [Медаль] [Зачет по сочинению] [количество экзаменов], далее пары [Экзамен] [Балл])\n");
    printf("\ttask - найти абитуриента-немедалистов с общим баллов выше среднего\n");
    printf("\ttable - распечатать таблицу\n");
    printf("\tremove - удаление абитуриента(remove [Фамилия] [Инициалы])\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Вы должны запускать программу с базой данных\n");
        exit(1);
    }
    char filename[STRSIZE];
    strncpy(filename, argv[1], STRSIZE - 1);
    filename[STRSIZE - 1] = '\0';
    FILE* file;
    char* ext = strrchr(filename, '.');
    bool isBinary = false;
    if (strcmp(ext, ".txt") == 0 || ext == NULL) {
        printf("Вы используете .txt файл для работы\n");
    } else if (strcmp(ext, ".bin") == 0) {
        isBinary = true;
        printf("Вы используете .bin файл для работы\n");
    } else {
        fprintf(stderr, "Некорректное расширение файла!\n");
        exit(2);
    }
    char line[STRSIZE];
    HashTable* table = malloc(sizeof(HashTable));
    initHashTable(table);
    if(!isBinary) {
        file = fopen(filename, "r");
        if (file == NULL) {
            perror("Ошибка, не удалось открыть файл");
            exit(1);
        }
        while(fgets(line, STRSIZE, file) != NULL) {
            abiturient* abit = newAbiturient();
            readFromLine(abit, line);
            char* surname = getSurname(abit);
            char* initials = getInitials(abit);
            char key[STRSIZE];
            strcpy(key, surname); // Копируем фамилию в ключ
            strcat(key, " "); // добавляем разделитель
            strcat(key, initials); // Добавляем инициалы в конец ключа
            insertElement(table, key, abit);
        }
    } else {
        file = fopen(filename, "rb");
        if (file == NULL) {
            perror("Ошибка, не удалось открыть файл");
            exit(1);
        }
        while (!feof(file)) {
            abiturient* abit = newAbiturient();
            if (!abiturientReadBin(abit, file)) {
                abiturientFree(abit);
                break;
            }
            char key[STRSIZE];
            char* surname = getSurname(abit);
            char* initials = getInitials(abit);     
            strcpy(key, surname); // Копируем фамилию в ключ
            strcat(key, " "); // добавляем разделитель
            strcat(key, initials); // Добавляем инициалы в конец ключа
            insertElement(table, key, abit);
        }
    }
    fclose(file);
    char choose[STRSIZE];
    printf("Выберите действие\n");
    while(strcmp(choose, "exit") != 0) {
        printMenu();
        fgets(choose, sizeof(choose), stdin);
        int len = strlen(choose);
        if (choose[len - 1] == '\n') {
            choose[len - 1]= '\0';
        }
        char* cmd = strtok(choose, " ");
        if (cmd == NULL) {
            printf("Некорректная команда!\n");
            break;
        }
        int lenCmd = strlen(cmd);
        char* arg = choose + lenCmd + 1;
        if (strcmp(cmd, "add") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка: добавьте имя\n");
                continue;
            }
            if (isBinary) {
                addAbiturientBin(filename, arg, table);
            } else {
                addAbiturient(filename, arg, table);
            }
        } else if (strcmp(cmd, "remove") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка: добавьте имя\n");
                break;
            }
            if (isBinary) {
                removeStudentBin(filename, arg, table);
            } else {
                removeStudent(filename, arg, table);
            }
            if (file == NULL) {
                perror("Ошибка при работе с файлом");
                exit(1);
            }
 
        } else if (strcmp(cmd, "info") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка! Добавьте имя абитуриента и инициалы\n");
                continue;
            }
            abiturient* find = findElement(table, arg);
            if (find == NULL) {
                printf("Не удается найти абитуриента: %s\n", arg);
                continue;
            }
            printAbiturientChars(find);
        } else if (strcmp(cmd, "table") == 0) {
            printAbiturientStr(table);
        } else if (strcmp(cmd, "task") == 0) {
            task(table);
        } else {
            continue;
        }

    }
    clearHashTable(table);
    free(table);
    return 0;

} 