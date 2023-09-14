#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/abit.h"

//функция меню
void printMenu() {
    printf("> exit - выход\n");
    printf("> info - информация об абитуриенте(info [Фамилия] [Инициалы])\n");
    printf("> add - добавление абитуриента(add [Фамилия] [Инициалы] [Пол] [Школа] [Медаль] [Зачет по сочинению] [количество экзаменов], далее пары [Экзамен] [Балл])\n");
    printf("> task - найти абитуриентов-стобальников, не набравших проходной балл\n");
    printf("> table - распечатать таблицу\n");
    printf("> remove - удаление абитуриента(remove [Фамилия] [Инициалы])\n");
}

//функция задания
void task(HashTable* table, float passBall) {
    for(int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturient* tmp = table->entries[i].value;
            if (tmp == NULL) {
                continue;
            }
            int numSubjects = sizeList(tmp->examStats);
            node* exam = tmp->examStats;
            float balls = 0;
            bool hasMax = false;
            for (int j = 0; j < numSubjects; j++) {
                float ball = exam->data.ball;
                if (ball == 100) {
                    hasMax = true;
                }
                balls += ball;
                exam = exam->next;
            }
            if (balls < passBall && hasMax) {
                printAbiturientChars(tmp);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) { // проверка на открытие файла
        printf("Вы должны запускать программу с базой данных\n");
        exit(1);
    }
    char filename[STRSIZE]; // храним имя файла
    strncpy(filename, argv[1], STRSIZE - 1);
    filename[STRSIZE - 1] = '\0';
    FILE* file;
    char* ext = strrchr(filename, '.');
    bool isBinary = false;
    
    // определяем какое расширение у файла
    if (strcmp(ext, ".txt") == 0 || ext == NULL) { 
        printf("Вы используете .txt файл\n");
    } else if (strcmp(ext, ".bin") == 0) {
        isBinary = true;
        printf("Вы используете .bin файл\n");
    } else { 
        fprintf(stderr, "Некорректное расширение файла!\n");
        exit(2);
    }
    char line[STRSIZE]; // буффер для строки в файла

    // создаем таблицу
    HashTable* table = malloc(sizeof(HashTable));
    initHashTable(table);


    if(!isBinary) { // текстовый файл
        file = fopen(filename, "r");
        if (file == NULL) {
            perror("Ошибка, не удалось открыть файл");
            exit(1);
        }
        while(fgets(line, STRSIZE, file) != NULL) { // построчно считываем абитуриентов
            abiturient* abit = newAbiturient(); // создаем абитуриента
            readFromLine(abit, line); // считываем значения
            char* surname = getSurname(abit); // берем фамилию и имя для ключа в хеш-таблицу
            char* initials = getInitials(abit);
            char key[STRSIZE]; // ключ
            strcpy(key, surname); // Копируем фамилию в ключ
            strcat(key, " "); // добавляем разделитель
            strcat(key, initials); // добавляем инициалы в конец ключа
            insertElement(table, key, abit); // пушим абитуриента в таблицу
        }
    } else { // то же самое, но файл бинарный
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
    fclose(file); // закрываем файл
    char choose[STRSIZE]; // строка выбора
    float ball; // проходной балл
    printf("Выберите действие\n");
    while(strcmp(choose, "exit") != 0) { 
        printMenu(); // вывод меню
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
        if (strcmp(cmd, "add") == 0) {  // добавление в файл
            if (arg[0] == '\0') {
                printf("Ошибка: добавьте имя\n");
                continue;
            }
            if (isBinary) { // бинарник
                addAbiturientBin(filename, arg, table);
            } else { // не бинарник
                addAbiturient(filename, arg, table);
            }
        } else if (strcmp(cmd, "remove") == 0) { // удаление в файле
            if (arg[0] == '\0') {
                printf("Ошибка: добавьте имя\n");
                break;
            }
            if (isBinary) { // бинарник
                removeStudentBin(filename, arg, table);
            } else { // не бинарник
                removeStudent(filename, arg, table);
            }
            if (file == NULL) {
                perror("Ошибка при работе с файлом");
                exit(1);
            }
 
        } else if (strcmp(cmd, "info") == 0) { // информация о конкретном абитуриенте
            if (arg[0] == '\0') {
                printf("Ошибка! Добавьте имя абитуриента и инициалы\n");
                continue;
            }
            abiturient* find = findElement(table, arg); // ищем в таблицу
            if (find == NULL) { // если не нашли
                printf("Не удается найти абитуриента: %s\n", arg);
                continue;
            }
            printAbiturientChars(find); // печатем о нем информацию
        } else if (strcmp(cmd, "table") == 0) { // вывод таблицы абитуриентов
            printAbiturientStr(table);
        } else if (strcmp(cmd, "task") == 0) { // функция задания
            printf("Введите проходной балл: ");
            scanf("%f", &ball);
            getchar(); 
            task(table, ball);
        } else { 
            continue;
        }

    }

    // очистка таблицы
    clearHashTable(table);
    free(table);
    return 0;

} 