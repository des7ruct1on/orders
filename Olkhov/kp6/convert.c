#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcspecs.h"

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
    FILE* in; // файл входящий
    FILE* out; // файл выходящий
    char line[MAX_SIZE];    
    if (!is_binary) {
        in = fopen(argv[1], "r");
        out = fopen(argv[2], "wb");  // открываем текстовый

        if (!in || !out) {
            printf("Не получается открыть файл!\n");
            exit(1);
        }
        while (fgets(line, MAX_SIZE, in) != NULL) {
            person* p = create_person();
            read_str(p, line);
            write_person_bin(p, out);
            destructor_person(p);
        }
    } else { // входящий файл - бинарный
        in = fopen(argv[1], "rb");
        out = fopen(argv[2], "w");  

        if (!in || !out) {
            printf("Не получается открыть файл!\n");
            exit(1);
        }


        while (!feof(in)) {
            person* p = create_person();
            if(!read_bin(p, in)) {
                destructor_person(p);
                break;
            }
            //print_person(p);
            write_person_txt(p, out);
            destructor_person(p);
        }
    }
    fclose(in);
    fclose(out);
    printf("Конвертация завершена!\n");
    return 0;
}

