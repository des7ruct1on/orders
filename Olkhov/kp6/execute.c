#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pcspecs.h"


void print_menu() {
    printf("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
    printf("|  exit  | выход                                                                                      |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("|  info  | информация о конкретном пассажире (info [Фамилия] [Инициалы])                              |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("|        | добавление пассажира(add [Фамилия] [Имя] [Процессор(через '-')] [Видеокарта(через '-')]    |\n");
    printf("|   add  | [Количество ОЗУ] [Операционная система] [Количество накопителей]                           |\n");
    printf("|        | затем пишете тройки значений [Тип накопителя(SSD/HDD)] [Бренд] [Объем]                     |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("|  task  | найти пользователей с однотипными компьютерами                                             |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("|  table | распечатать таблицу                                                                        |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("| remove | удаление пользователя(remove [Фамилия] [Инициалы])                                         |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
}

// будем считать компьютеры однотипными, если у них совпадают процессор и видеокарта
bool almost_same_pc(person* one, person* two) {
    return !strcmp(get_cpu(one), get_cpu(two)) && !strcmp(get_gpu(one), get_gpu(two));
}

// функция проверки на нахождение пользователя в массиве найденных
bool check_found(person** data, person* pers) {
    if (data == NULL) {
        return false;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (data[i] != NULL && strcmp(data[i]->surname, pers->surname) == 0) { // Исправлено: data[i] != NULL
            return true;
        }
    }
    return false;
}


void task(hash_table* table) {
    person* found[TABLE_SIZE] = {NULL}; // массив найденных пользователей
    int index = 0;
    for(int i = 0; i < TABLE_SIZE; i++) {
        if (table->elements[i].data != NULL) {
            person* tmp1 = table->elements[i].data; // берем первого
            for (int j = 0; j < TABLE_SIZE; j++) {
                if (table->elements[i].data != NULL) {
                    person* tmp2 = table->elements[j].data; // берем второго
                    char* surname1 = get_surname(tmp1);
                    char* surname2 = get_surname(tmp2);
                    if (!strcmp(surname1, surname2) && strcmp(table->elements[j].key, table->elements[i].key)) { // сравниваем фамилии
                        if (almost_same_pc(tmp1, tmp2) && !check_found(found, tmp2)) { // проверяем компьютеры и на уникальность проверки
                            print_person(tmp1);
                            print_person(tmp2);
                            found[index] = tmp1; // добавляем найденных
                            index++;
                            found[index] = tmp2; // добавляем найденных
                            index++;
                        } else {
                            continue;
                        }
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
            }
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