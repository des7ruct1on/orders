#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aeroflot.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Используйте:\n\t./generate FILE_FROM FILE_TO\n");
        exit(0);
    }
    char filename[STR_SIZE];
    strncpy(filename, argv[1], STR_SIZE - 1);
    filename[STR_SIZE - 1] = '\0';

    char* ext = strrchr(filename, '.');
    bool is_binary = false;
    if (strcmp(ext, ".txt") == 0 || ext == NULL) {
        printf("Вы используете текстовый файл\n");
    } else if (strcmp(ext, ".bin") == 0 || ext != NULL) {
        is_binary = true;
        printf("Вы используете бинарный файл\n");
    } else {
        fprintf(stderr, "Некорректное расширение файла!\n");
        exit(2);
    }
    FILE* in;
    FILE* out;
    char line[STR_SIZE];    
    if (!is_binary) {
        in = fopen(argv[1], "r");
        out = fopen(argv[2], "wb");  // открываем текстовый

        if (!in || !out) {
            printf("Не получается открыть файл!\n");
            exit(1);
        }
        while (fgets(line, STR_SIZE, in) != NULL) {
            passenger* pas = create_passenger();
            read_from_str(pas, line);
            write_passenger_bin(pas, out);
            destructor_passenger(pas);
        }
    } else {
        in = fopen(argv[1], "rb");
        out = fopen(argv[2], "w");  // открываем бинарный

        if (!in || !out) {
            printf("Не получается открыть файл!\n");
            exit(1);
        }


        while (!feof(in)) {
            passenger* pas = create_passenger();
            if(!read_passenger_bin(pas, in)) {
                destructor_passenger(pas);
                break;
            }
            write_passenger_txt(pas, out);
            destructor_passenger(pas);
        }
    }
    fclose(in);
    fclose(out);
    printf("Конвертация завершена!\n");
    return 0;
}

