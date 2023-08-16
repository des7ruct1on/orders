#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../headers/abiturient.h"
#include "../headers/allowdata.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));  // инициализируем для рандомного заполнения
    int num = atoi(argv[2]);
    FILE* fp = fopen(argv[1], "w");  // открываем файл для записи
    if (argc != 3) {
        printf("Используйте: /generate FILE.txt [количество раз]\n");
        return 1;
    }
    printf("%d", num);
    for (int i = 0; i < num; i++) {
        char record[256];  // буффер для хранения

        char* surname;
        if (rand() % 2 == 0) {
            surname = allowedSurnamesMale[rand() % 10];
        } else {
            surname = allowedSurnamesFemale[rand() % 10];
        }
        char* initials = allowedInitials[rand() % 20];
        char* sex = allowedSex[rand() % 2];
        char* schoolNumber = allowedSchoolNumber[rand() % 20];
        char* hasMedal = allowedComposition[rand() % 2];
        char* hasComposition = allowedComposition[rand() % 2];
        char* subjectName1 = allowedSubjects[2]; //первым предметом всегда будет русский, так как это обязательный предмет
        int grade1 = 40 + rand() % (100 - 40 + 1);  // пусть 40 будет минимальный балл, тогда баллы будет от 40 до 100
        char* subjectName2 = allowedSubjects[rand() % 10];
        while (subjectName2 == allowedSubjects[2]) { //проверка на то, что оценка за экзамен уже есть
            subjectName2 = allowedSubjects[rand() % 10];
        }
        int grade2 = 40 + rand() % (100 - 40 + 1);
        char* subjectName3 = allowedSubjects[rand() % 10];
        while (subjectName3 == allowedSubjects[2] || subjectName3 == subjectName2) { //проверка на то, что оценка за экзамен уже есть
            subjectName3 = allowedSubjects[rand() % 10];
        }
        int grade3 = 40 + rand() % (100 - 40 + 1);
        if (hasMedal == allowedComposition[0]) { // если у абитуриента золотая медаль, то он должен защитить ее, набрав минимум 70 баллов за каждый предмет
            grade1 = 70 + rand() % (100 - 70 + 1);
            grade2 = 70 + rand() % (100 - 70 + 1);
            grade3 = 70 + rand() % (100 - 70 + 1);
        }
        
        sprintf(record, "%s %s %s %s %s %s %d %s %d %s %d %s %d",          
                surname, initials, sex, schoolNumber,
                hasMedal, hasComposition, 3, 
                subjectName1, grade1,
                subjectName2, grade2, subjectName3, grade3);    //записываем в массив record
        fprintf(fp, "%s\n", record);   //записываем в файл построчно
        
    }

    fclose(fp);
}
