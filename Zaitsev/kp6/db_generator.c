#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


char* surname_male[] = {
    "Filippov",
    "Kravchenko",
    "Dragovich",
    "Melnikov",
    "Hlebnikov",
    "Zaitsev",
    "Kazakov",
    "Rudenko",
    "Rodnikov",
    "Bitykov",
    "Bortakovksiy",
    "Azanov",
    "Sergeev",
    "Potenko"
};

char* initials[] = {
    "I.I",
    "A.I",
    "V.V",
    "F.A",
    "L.I",
    "K.I",
    "I.A",
    "M.A",
    "V.Z"
};

char* surname_female[] = {
    "Filippova",
    "Kravchenko",
    "Dragovich",
    "Melnikova",
    "Hlebnikova",
    "Zaitseva",
    "Kazakova",
    "Rudenko",
    "Rodnikova",
    "Bitykova",
    "Bortakovksiy",
    "Azanova",
    "Sergeeva",
    "Potenko"
};

char index[] = {
    'a',
    'b',
    'v',
    'g',
    'd',
    'e'
};

char* gender[] = {
    "male",
    "female"
};

int main(int argc, char *argv[]) {
    srand(time(NULL));  // инициализируем для рандомного заполнения
    int num = atoi(argv[2]);
    FILE* fp = fopen(argv[1], "w");  // открываем файл для записи
    if (argc != 3) {
        printf("Используйте: /generate FILE.txt [количество раз]\n");
        return 1;
    }
    for (int i = 0; i < num; i++) {

        char* SURNAME;
        char* INITIALS = initials[rand() % (sizeof(initials) / sizeof(initials[0]))];
        char* GENDER;
        if (rand() % 2 == 0) {
            SURNAME = surname_male[rand() % (sizeof(surname_male) / sizeof(surname_male[0]))];
            GENDER = gender[0];

        } else {
            SURNAME = surname_female[rand() % (sizeof(surname_female) / sizeof(surname_female[0]))];
            GENDER = gender[1];
        }
        char INDEX = index[rand() % (sizeof(index) / sizeof(index[0]))];
        int CLASS_NUM = rand() % 11 + 1;
        int SCHOOL_NUM = rand() % 100 + 1;
        fprintf(fp, "%s %s %s %d %c %d\n", SURNAME, INITIALS, GENDER, CLASS_NUM, INDEX, SCHOOL_NUM);       
    }

    fclose(fp);
}