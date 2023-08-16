#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pc.h"


void print_menu() {
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|  exit  | выход                                                                                      |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|  info  | информация о конкретном пассажире (info [Фамилия] [Инициалы])                              |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|        | добавление пользователя(add [Фамилия] [Имя] [Процессор(через '-')] [Видеокарта(через '-')] |\n");
    printf("|   add  | [Количество ОЗУ] [Операционная система] [Количество накопителей]                           |\n");
    printf("|        | затем пишете тройки значений [Тип накопителя(SSD/HDD)] [Бренд] [Объем]                     |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|  task  | Вывести информацию о всех рабочих станцияъ                                                 |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("|  table | распечатать таблицу                                                                        |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
    printf("| remove | удаление пользователя(remove [Фамилия] [Инициалы])                                         |\n");
    printf("|-----------------------------------------------------------------------------------------------------|\n");
}

void print_all_specs(person* p, int num) {
    char* surname = get_surname(p);
    char* name = get_name(p);
    char* cpu = get_cpu(p);
    char* gpu = get_gpu(p);
    int ram = get_ram(p);
    char* os = get_os(p);
    int num_drivers = get_amount_disks(p);
    solid_driver* disks = get_driver(p);
    printf("|=============================|\n");
    printf("| Номер компьютера: %d\n", num);
    printf("| Владелец: %s %s\n", surname, name);
    printf("| Характеристики компьютера\n");
    printf("| Процессор: %s\n", cpu);
    printf("| Видеокарта: %s\n", gpu);
    printf("| Объем ОЗУ: %d\n", ram);
    printf("| Операционная система: %s\n", os);
    printf("| Количество хранилищ: %d\n", num_drivers);
    for (int i = 0; i < num_drivers; i++) {
        printf("| Диск %d: %s %s %d\n", (i + 1), disks[i].type, disks[i].name, disks[i].amount);
    }
    printf("|=============================|\n");
}

void task(hash_table* table) {
    int count = 0;
    for(int i = 0; i < TABLE_SIZE; i++) {
        if (table->elements[i].data != NULL) {
            person* tmp = table->elements[i].data; // берем первого
            print_all_specs(tmp, count);
            count++;
        } else {
            continue;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Вы должны запускать программу с базой данных пользователей\n");
        exit(1);
    }

    // запоминаем имя файла
    char filename[STR_SIZE];
    strncpy(filename, argv[1], STR_SIZE - 1);
    filename[STR_SIZE - 1] = '\0';

    FILE* file = fopen(filename, "r");
    if (file == NULL) { // проверка
        perror("Ошибка, не удалось открыть файл!");
        exit(1);
    }
    char line[MAX_SIZE]; // строка
    hash_table* table = malloc(sizeof(hash_table));
    init_hash_table(table);
    while(fgets(line, MAX_SIZE, file) != NULL) {
        person* p = create_person();
        read_str(p, line);
        char* surname = get_surname(p);
        char* name = get_name(p);
        char key[MAX_SIZE];
        // формируем ключ для хеширования
        strcpy(key, surname); 
        strcat(key, " "); 
        strcat(key, name); 
        insert_element(table, key, p); // добавляем в таблицу
    }
    fclose(file);
    char choose[MAX_SIZE];
    printf("Выберите действие\n");
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
            printf("%s\n", arg);
            if (arg[0] == '\0') {
                printf("Ошибка! Отсутсвуют данные\n");
                continue;
            }
            insert_person(filename, arg, table);
        } else if (strcmp(cmd, "remove") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка! Отсутсвуют данные\n");
                break;
            }
            erase_person(filename, arg, table);
            if (file == NULL) {
                perror("Ошибка при работе с файлом");
                exit(1);
            }
 
        } else if (strcmp(cmd, "info") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка! Добавьте фамилию пользователя и имя\n");
                continue;
            }
            person* find = find_element(table, arg);
            if (find == NULL) {
                printf("Пользователь %s отсутсвует в базе данных\n", arg);
                continue;
            }
            print_person(find);
        } else if (strcmp(cmd, "table") == 0) {
            print_table(table);
        } else if (strcmp(cmd, "task") == 0) {
            task(table);
        } else {
            continue;
        }

    }
    destructor_hash_table(table);
    free(table);
    return 0;

}