#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "io.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Используйте:\n\t./generate FILE_FROM FILE_TO\n");
        exit(0);
    }

    FILE *in  = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (!in || !out) {
        printf("Не удается открыть файл!\n");
        exit(1);
    }

    Student s;

    while (studentReadTxt(&s, in)) {
        studentWriteBin(&s, out);
    }
    
    fclose(in);
    fclose(out);
    return 0;
}

