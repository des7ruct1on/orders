#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../headers/abiturient.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Используйте:\n\t./convert [файл_до] [файл_после]\n");
        exit(1);
    }

    char filename[STRSIZE];
    strncpy(filename, argv[1], STRSIZE - 1);
    filename[STRSIZE - 1] = '\0';

    char* ext = strrchr(filename, '.');
    bool isBinary = false;

    if (strcmp(ext, ".txt") == 0 || ext == NULL) {
        printf("Вы используете .txt файл для конвертации\n");
    } else if (strcmp(ext, ".bin") == 0 || ext != NULL) {
        isBinary = true;
        printf("Вы используете .bin файл для конвертации\n");
    } else {
        fprintf(stderr, "Некорректное расширение файла!\n");
        exit(2);
    }

    FILE* in;
    FILE* out;
    char line[STRSIZE];
    if (!isBinary) {
        in = fopen(argv[1], "r");
        out = fopen(argv[2], "wb");  // открываем текстовый

        if (!in || !out) {
            printf("Не получается открыть файл!\n");
            exit(1);
        }
        while (fgets(line, STRSIZE, in) != NULL) {
            abiturient* student = newAbiturient();
            readFromLine(student, line);
            abiturientWriteBin(student, out);
            abiturientFree(student);
        }
    } else {
        in = fopen(argv[1], "rb");
        out = fopen(argv[2], "w");  // открываем бинарный

        if (!in || !out) {
            printf("Не получается открыть файл!\n");
            exit(1);
        }


        while (!feof(in)) {
            abiturient* student = newAbiturient();
            if(!abiturientReadBin(student, in)) {
                abiturientFree(student);
                break;
            }
            abiturientWriteTxt(student, out);
            abiturientFree(student);
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
