#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroflot.h"

#define MAX_SIZE_SURNAME 10   // Максимальная длина фамилии - 10 символов
#define MAX_DEST_SIZE 18  // Максимальная длина пункта назначения - 18 символов

// Алфавит для генерации данных
char latin[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZFM";
#define LATIN_SIZE ((int)(sizeof(latin) - 1))

static unsigned int gseed = 0;

// Инициализация генератора случайных чисел
static inline void fast_srand(int seed) {
    gseed = seed;
}

// Генерация случайного числа
static inline int fast_rand() {
    gseed = (214013 * gseed + 2531011);
    return (gseed >> 16) & 0x7FFF;
}

// Генерация данных для структуры passenger
void generate_passenger_data(FILE* file) {
    passenger p;

    // Генерация фамилии
    int i;
    int surname_size = fast_rand() % (MAX_SIZE_SURNAME - 1) + 1;
    for (i = 0; i < surname_size; ++i) {
        p.surname[i] = latin[fast_rand() % LATIN_SIZE];
    }
    p.surname[i] = '\0';

    // Генерация инициалов
    p.initials[0] = latin[fast_rand() % LATIN_SIZE];
    p.initials[1] = '.';
    p.initials[2] = latin[fast_rand() % LATIN_SIZE];
    p.initials[3] = '\0';

    // Генерация числа предметов и общего веса
    p.items_num = fast_rand() % 5 + 1;
    p.total_weight = fast_rand() % 20 + 1;

    // Генерация пункта назначения
    int dest_size = fast_rand() % (MAX_DEST_SIZE - 1) + 1;
    for (i = 0; i < dest_size; ++i) {
        p.destination[i] = latin[fast_rand() % LATIN_SIZE];
    }
    p.destination[i] = '\0';

    // Генерация времени
    p.time.hour = fast_rand() % 24;
    p.time.minute = fast_rand() % 60;

    // Генерация информации о пересадках
    p.transfer = fast_rand() % 2;

    // Генерация числа детей
    p.num_childrens = fast_rand() % 4;

    fprintf(file, "%s %s %d %d %s %02d %02d %d %d\n",
            p.surname, p.initials, p.items_num, p.total_weight,
            p.destination, p.time.hour, p.time.minute, p.transfer, p.num_childrens);
    //destructor_passenger(&p);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Используйте: %s <FILE> <COUNT>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    int qty = atoi(argv[2]);

    FILE* f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Не удается открыть файл!.\n");
        return 1;
    }

    fast_srand(0);

    int i;
    for (i = 0; i < qty; ++i) {
        generate_passenger_data(f);
    }

    fclose(f);

    printf("Генерация данных завершена. %d записей о пассажирах записаны в '%s'.\n", qty, filename);

    return 0;
}