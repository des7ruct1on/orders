#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "student.h"

void print_menu() {
    printf("|=====================================================================================================|\n");
    printf("|  exit  | выход                                                                                      |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|  info  | информация о конкретном пассажире (info [Фамилия] [Инициалы])                              |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|   add  | добавление студента(add [Фамилия] [Инициалы] [Пол] [Номер класса] [Буква] [Номер школы]    |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|  task  | найти пассажиров, вес багажа которых отличается от максимального веса на k                 |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|  table | распечатать таблицу                                                                        |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("| remove | удаление школльника(remove [Фамилия] [Инициалы])                                           |\n");
    printf("|=====================================================================================================|\n");
}

void task(hash_table* table, int p) {
    if (p == 0) {
        printf("Недопустимое значение!!!\n");
        return;
    }
    int counter_ten = 0;
    int counter_p = 0;
    for(int i = 0; i < TABLE_SIZE; i++) {
        if (table->cells[i].data != NULL) {
            student* tmp = table->cells[i].data; 
            if (tmp->class_num == 10) {
                counter_ten++;
            } else if (tmp->class_num == p) {
                counter_p++;
            }
        }
    }
    if (counter_p > counter_ten) {
        printf("В %d-ых классах больше на %d учеников\n", p, (counter_p - counter_ten));
    } else if (counter_p < counter_ten) {
        printf("В %d-ых классах меньше на %d учеников\n", p, (counter_ten - counter_p));
    } else {
        printf("Одинаковое количество учеников\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Вы должны запускать программу с базой данных пассажиров\n");
        exit(1);
    }
    char filename[STR_SIZE];
    strncpy(filename, argv[1], STR_SIZE - 1);
    filename[STR_SIZE - 1] = '\0';
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка, не удалось открыть файл");
        exit(1);
    }
    char line[STR_SIZE];
    hash_table* table = malloc(sizeof(hash_table));
    init_hash_table(table);
    while(fgets(line, STR_SIZE, file) != NULL) {
        student* s = create_student();
        read_from_str(s, line);
        char* surname = get_surname(s);
        char* initials = get_initials(s);
        char key[STR_SIZE];
        strcpy(key, surname); // Копируем фамилию в ключ
        strcat(key, " "); // добавляем разделитель
        strcat(key, initials); // Добавляем инициалы в конец ключа
        insert_element(table, key, s);
    }
    fclose(file);
    char choose[STR_SIZE];
    printf("Выберите действие\n");
    int p;
    while(strcmp(choose, "exit") != 0) {
        print_menu();
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
        int len_command = strlen(cmd);
        char* arg = choose + len_command + 1;
        if (strcmp(cmd, "add") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка: добавьте данные\n");
                continue;
            }
            insert_student(filename, arg, table);
        } else if (strcmp(cmd, "remove") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка: добавьте имя\n");
                break;
            }
            erase_student(filename, arg, table);
            if (file == NULL) {
                perror("Ошибка при работе с файлом");
                exit(1);
            }
 
        } else if (strcmp(cmd, "info") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка! Добавьте имя пассажира и инициалы\n");
                continue;
            }
            student* find = find_element(table, arg);
            if (find == NULL) {
                printf("Не удается найти абитуриента: %s\n", arg);
                continue;
            }
            print_student(find);
        } else if (strcmp(cmd, "table") == 0) {
            print_table(table);
        } else if (strcmp(cmd, "task") == 0) {
            printf("Введите номер классов: ");
            scanf("%d", &p);
            getchar();
            task(table, p);
        } else {
            continue;
        }

    }
    destructor_hash_table(table);
    free(table);
    return 0;

}