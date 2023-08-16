#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char latin[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZFM";
#define LATIN_SIZE ((int)(sizeof(latin) - 1))
#define STRSIZE 24

static unsigned int gseed = 0;

static inline void fastSrand(int seed) {
    gseed = seed;
}

static inline int fastRand() {
    gseed = (214013 * gseed + 2531011);
    return (gseed >> 16) & 0x7FFF;
}

void generateStudentData(FILE* file) {
    char surname[STRSIZE] = { '\0' };
    char initials[3] = { '\0' };
    char gender = latin[LATIN_SIZE + fastRand() % 2 - 2];
    char group = latin[fastRand() % LATIN_SIZE];
    char university[STRSIZE] = { '\0' };
    char job[STRSIZE] = { '\0' };
    int course = fastRand() % 5 + 1;

    // Генерация фамилий
    int i;
    int surname_size = fastRand() % (STRSIZE - 1) + 1;
    for (i = 0; i < surname_size; ++i) {
        surname[i] = latin[fastRand() % LATIN_SIZE];
    }

    // Генерация инициалов
    initials[0] = latin[fastRand() % LATIN_SIZE];
    initials[1] = latin[fastRand() % LATIN_SIZE];

    // Генерация университета
    int universitySize = fastRand() % (STRSIZE - 1) + 1;
    for (i = 0; i < universitySize; ++i) {
        university[i] = latin[fastRand() % LATIN_SIZE];
    }

    // Генерация работы
    int jobSize = fastRand() % (STRSIZE - 1) + 1;
    for (i = 0; i < jobSize; ++i) {
        job[i] = latin[fastRand() % LATIN_SIZE];
    }

    fprintf(file, "%s %s %c %d %c %s %s\n", surname, initials, gender, course, group, university, job);
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
        fprintf(stderr, "Не удается открыть файл!.\n", filename);
        return 1;
    }

    fastSrand(0);

    int i;
    for (i = 0; i < qty; ++i) {
        generateStudentData(f);
    }

    fclose(f);

    printf("Генерация данных завершена. %d студентов записано в '%s'.\n", qty, filename);

    return 0;
}
