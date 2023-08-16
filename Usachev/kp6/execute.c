#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "io.h"

void printMenu() {
    printf("\ttask - вывести классы, где количество девочек больше количества мальчиков\n");
    printf("\tadd    [фамилия] [инициалы] [пол] [номер курса] [буква/номер группы] [место учёбы] [место работы] - добавить выпускника\n");
    printf("\tremove    [фамилия] [инициалы] - удалить выпускника\n");
    printf("\tinfo    [фамилия] [инициалы] - информация о выпускнике\n");
    printf("\texit - завершение программы\n");
}

int main(int argc, char *argv[]) {
    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("Не удается открыть файл!\n");
        exit(1);
    }
    Table* hashTable = createTable(in);
    fclose(in);

    char choose[STRSIZE];
    if (argc != 2) {
        printf("Используйте:\n\t./execute FILE\n");
        exit(0);
    }
    while (!feof(stdin)) {
        printMenu();
        fscanf(stdin, "%s", choose);
        if (feof(stdin)) {
            break;
        }
        if (!strcmp(choose, "task")) {
            countGenderPerGroup(hashTable);
            continue;
        }else if (!strcmp(choose, "add")) {
            FILE* file = fopen(argv[1], "a");
            if (!file) {
            printf("Не удается открыть файл!\n");
                exit(1);
            }
            if (feof(stdin)) {
                fclose(file);
                break;
            }
            hashTable = addStudent(file, hashTable);
            fclose(file);
        } else if (!strcmp(choose, "remove")) {
            char surname[STRSIZE];
            char initials[STRSIZE];
            fscanf(stdin, "%s", surname);
            if (feof(stdin)) {
                break;
            }
            fscanf(stdin, "%s", initials);
            removeStudent(argv[1], surname, initials, &hashTable);
            if (feof(stdin)) {
                break;
            }
        } else if (!strcmp(choose, "exit")) {
            break;
        } else if (!strcmp(choose, "info")) {
            FILE* in = fopen(argv[1], "r");
            if (!in) {
                printf("Не удается открыть файл!\n");
                exit(1);
            }
            char surname[STRSIZE];
            char initials[3];
            fscanf(stdin, "%s", &surname);
            if (feof(stdin)) {
                break;
            }
            fscanf(stdin, "%s", &initials);
            if (feof(stdin)) {
                fclose(in);
                break;
            }
            int find = infoStudent(in, surname, initials);
            fclose(in);
        }
    }
    destroyTable(hashTable);
    return 0;
}
