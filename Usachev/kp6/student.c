#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#define MAXGROUPS 100

void destroyTable(Table* t) {
    if (t == NULL) {
        return;
    }
    destroyTable(t->prev);
    free(t);
}

int findPerson(Table* t, char* surname) {
    int c = 0;
    while (t->prev) {
        if (!strcmp(t->st.surname, surname)) {
            c += 1;
        }
        t = t->prev;
    }
    return c;
}

Table* createTable(FILE* in) {
    Table* t = malloc(sizeof(Table));
    t->id = 0;
    t->prev = NULL;
    Student stud;
    while (studentReadBin(&stud, in)) {
        Table* newTable = malloc(sizeof(Table));
        newTable->st = stud;
        newTable->id = t->id + 1;
        newTable->prev = t;
        t = newTable;
    }
    return t;
}

int infoStudent(FILE* in, char* surname, char* initials) {
    Student st;
    int found = 0;
    while (studentReadBin(&st, in)) {
        if (!strcmp(st.surname, surname) && !strcmp(st.initials, initials)) {
            found = 1;
            printf("Имя: %s %s\nПол: %c\nНомер класса: %d\nБуква класса:  %c\nВУЗ:  %s\nМесто работы:  %s\n", st.surname, st.initials, st.gender, st.course, st.group, st.university, st.job);
        }
    }
    if (found == 0) {
        printf("Студента %s %s нет в списке\n", surname, initials); 
    }
    return found;
}

Table* addStudent(FILE* file, Table* t) {
    Student student;
    memset(&student, 0, sizeof(Student));
    fscanf(stdin, "%s", student.surname);
    if (feof(stdin)) {
        return t;
    }
    fscanf(stdin, "%3s", student.initials);
    if (feof(stdin)) {
        return t;
    }
    fscanf(stdin, " %c", &student.gender);
    if (feof(stdin)) {
        return t;
    }
    fscanf(stdin, " %d", &student.course);
    if (feof(stdin)) {
        return t;
    }
    fscanf(stdin, " %c", &student.group);\
    if (feof(stdin)) {
        return t;
    }
    fscanf(stdin, "%s", student.university);
    if (feof(stdin)) {
        return t;
    }
    fscanf(stdin, "%s", student.job);
    if (feof(stdin)) {
        return t;
    }
    studentWriteBin(&student, file);
    Table* tmp = malloc(sizeof(Table));
    tmp->st = student;
    tmp->id = t->id + 1;
    tmp->prev = t;
    t = tmp;
    printf("Студент  %s %s успешно добавлен!\n", student.surname, student.initials);
    return t;
}

void removeStudent(char* file, char* surname, char* initials, Table** t) {
    FILE* in = fopen(file, "r");
    if (!in) {
        printf("Не удается открыть файл!\n");\
        exit(1);
    }
    FILE* tmp = fopen("tmp", "w");
    Student student;
    bool found = false;
    while (studentReadBin(&student, in)) {
        if (strcmp(student.surname, surname)) {
            studentWriteBin(&student, tmp);
        } else if (strcmp(student.initials, initials)) {
            studentWriteBin(&student, tmp);
        } else {
            found = true;
        }
    }
    fclose(in);
    fclose(tmp);


    in = fopen(file, "w");
    if (!in) {
        printf("Не удается открыть файл!\n");
        exit(1);
    }
    tmp = fopen("tmp", "r");
    while (studentReadBin(&student, tmp)) {
        if (strcmp(student.surname, surname) != 0) {
            studentWriteBin(&student, in);
        } else if (strcmp(student.initials, initials) != 0) {
            studentWriteBin(&student, in);
        }
    }
    fclose(in);
    fclose(tmp);
    remove("tmp");

    if (found == false) {
        printf("Такого студента нет!\n");
        return;
    } else {
        printf("Студент %s %s удален.\n", surname, initials);
    }

    Table* current = *t;
    Table* previous = NULL;

    while (current != NULL) {
        if (current->prev == NULL)
            return;
        if ((!strcmp(current->st.surname, surname)) && (!strcmp(current->st.initials, initials))) {
            if (previous == NULL) {
                *t = current->prev;
            } else {
                previous->prev = current->prev;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->prev;
    }
}

void countGenderPerGroup(Table* t) {
    Table* current = t;
    while (current != NULL) {
        int maleCount = 0;
        int femaleCount = 0;
        char currentGroup = '\0';
        currentGroup = current->st.group;
        int length = strlen(current->st.university);
        char currentUniversity[length];
        memset(currentUniversity, 0, sizeof(currentUniversity));
        strcpy(currentUniversity, current->st.university);
        // Проверка, была ли уже обработана текущая группа
        bool groupProcessed = false;
        Table* checkCurrent = t;
        while (checkCurrent != current) {
            if (checkCurrent->st.group == currentGroup && strcmp(checkCurrent->st.university, currentUniversity) == 0) {
                groupProcessed = true;
                break;
            }
            checkCurrent = checkCurrent->prev;
        }

        // Если группа уже была обработана, переходим к следующей
        if (groupProcessed) {
            current = current->prev;
            continue;
        }

        // Подсчет количества мальчиков и девочек в текущей группе и университете
        Table* innerCurrent = t;
        while (innerCurrent != NULL) {
            if (innerCurrent->st.group == currentGroup && strcmp(innerCurrent->st.university, currentUniversity) == 0) {
                if (innerCurrent->st.gender == 'M') {
                    maleCount++;
                } else if (innerCurrent->st.gender == 'F') {
                    femaleCount++;
                }
            }
            innerCurrent = innerCurrent->prev;
        }

        // Вывод информации, если количество девочек больше количества мальчиков
        if (femaleCount > maleCount) {
            printf("Университет: %s, Группа %c: Мальчики - %d, Девочки - %d\n", currentUniversity, currentGroup, maleCount, femaleCount);
        }

        current = current->prev;
    }
}







