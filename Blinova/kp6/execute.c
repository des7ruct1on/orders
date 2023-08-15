#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "aeroflot.h"

void print_menu() {
    printf("|=====================================================================================================|\n");
    printf("|  exit  | выход                                                                                      |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|  info  | информация о конкретном пассажире (info [Фамилия] [Инициалы])                              |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|        | добавление пассажира(add [Фамилия] [Инициалы] [Количество вещей] [Общий вес багажа]        |\n");
    printf("|   add  | [Пункт назначения] [Часы вылета] [Минуты вылета] [Количество пересадок] [Количество детей])|\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|  task  | найти пассажиров, вес багажа которых отличается от максимального веса на k                 |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|  table | распечатать таблицу                                                                        |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("| remove | удаление пассажира(remove [Фамилия] [Инициалы])                                            |\n");
    printf("|=====================================================================================================|\n");
}

void task(hash_table* table, int k) {
    int max = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->cells[i].data != NULL) {
            passenger* tmp = table->cells[i].data;
            if (tmp == NULL) {
                continue;
            }
            int weight = tmp->total_weight;
            if (weight > max) {
                max = weight;
            }
        }
    }
    printf("| Максимальный вес: %d\n", max);
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table->cells[i].data != NULL) {
            passenger* tmp = table->cells[i].data;
            if (tmp == NULL) {
                continue;
            }
            int weight = tmp->total_weight;
            if (fabs(weight - max) <= k) {
                print_passenger(tmp);
            }
        }
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
        passenger* pas = create_passenger();
        read_from_str(pas, line);
        char* surname = get_surname(pas);
        char* initials = get_initials(pas);
        char key[STR_SIZE];
        strcpy(key, surname); // Копируем фамилию в ключ
        strcat(key, " "); // добавляем разделитель
        strcat(key, initials); // Добавляем инициалы в конец ключа
        insert_element(table, key, pas);
    }
    fclose(file);
    char choose[STR_SIZE];
    printf("Выберите действие\n");
    int k;
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
            insert_passenger(filename, arg, table);
        } else if (strcmp(cmd, "remove") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка: добавьте имя\n");
                break;
            }
            erase_passenger(filename, arg, table);
            if (file == NULL) {
                perror("Ошибка при работе с файлом");
                exit(1);
            }
 
        } else if (strcmp(cmd, "info") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка! Добавьте имя пассажира и инициалы\n");
                continue;
            }
            passenger* find = find_element(table, arg);
            if (find == NULL) {
                printf("Не удается найти абитуриента: %s\n", arg);
                continue;
            }
            print_passenger(find);
        } else if (strcmp(cmd, "table") == 0) {
            print_table(table);
        } else if (strcmp(cmd, "task") == 0) {
            printf("Введите значение разницы k: ");
            scanf("%d", &k);
            task(table, k);
        } else {
            continue;
        }

    }
    destructor_hash_table(table);
    free(table);
    return 0;

}