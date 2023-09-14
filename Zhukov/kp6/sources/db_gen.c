#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../headers/abit.h"

char* allowedSurnamesMale[] = {
    "Zaitsev",
    "Alekseev",
    "Maksimov",
    "Vasilyev",
    "Grigoryev",
    "Maksimov",
    "Lyashko",
    "Zhukov",
    "Temniy",
    "Svetliy",
};

char* allowedSurnamesFemale[] = {
    "Zaitseva",
    "Alekseeva",
    "Maksimova",
    "Vasilyeva",
    "Gagarina",
    "Maksimova",
    "Lyashko",
    "Zhukova",
    "Temniya",
    "Svetlaya",
};

char* allowedInitials[] = {
    "I.A",
    "D.M",
    "M.S",
    "M.C",
    "V.V",
    "A.Z",
    "O.B",
    "N.N",
    "P.N",
    "K.B",
    "P.B",
    "O.O",
    "A.A",
    "N.L",
    "L.A",
    "U.S",
    "I.S",
    "T.O",
    "R.B",
    "F.M",
};
char* allowedGender[] = {
    "Male",
    "Female",
};
char* allowedSchoolNumber[] = {
    "13",
    "3",
    "88",
    "152",
    "347",
    "95",
    "113",
    "22",
    "16",
    "85",
    "143",
    "36",
    "86",
    "1111",
    "77",
    "93",
    "102",
    "22",
    "167",
    "90",
};
char* allowedSubjects[] = {
    "Math",
    "Eng",
    "Rus",
    "Bio",
    "Geo",
    "Inf",
    "Phys",
    "Chem",
    "Social",
    "Liter",
};
char* allowedComposition[] = {
    "Yes",
    "No",
};


int main(int argc, char *argv[]) {
    srand(time(NULL));  // инициализируем для рандомного заполнения
    int num = atoi(argv[2]); //преобразуем аргумент в число (число необходимых записей)
    FILE* fp = fopen(argv[1], "w");  // открываем файл для записи
    if (argc != 3) {
        printf("Используйте: /generate FILE.txt [количество раз]\n");
        return 1;
    }
    printf("%d", num);
    for (int i = 0; i < num; i++) {
        char* surname;
        char* gender;
        if (rand() % 2 == 0) {
            surname = allowedSurnamesMale[rand() % 10];
            gender = allowedGender[0];
        } else {
            surname = allowedSurnamesFemale[rand() % 10];
            gender = allowedGender[1];
        }
        char* initials = allowedInitials[rand() % 20];
        char* schoolNumber = allowedSchoolNumber[rand() % 20];
        char* hasMedal = allowedComposition[rand() % 2];
        char* hasComposition = allowedComposition[rand() % 2];
        char* subjectName1 = allowedSubjects[2]; //русский язык
        int grade1 = 40 + rand() % (100 - 40 + 1);  // 40 - минимальный балл, потому регеним баллы от 40 до 100
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
        if (hasMedal == allowedComposition[0]) { // если у абитуриента золотая медаль, то нужно повысить его баллы, иначе он не сможет ее защитить
            grade1 = 70 + rand() % (100 - 70 + 1);
            grade2 = 70 + rand() % (100 - 70 + 1);
            grade3 = 70 + rand() % (100 - 70 + 1);
        }
        
        fprintf(fp, "%s %s %s %s %s %s %d %s %d %s %d %s %d",          
                surname, initials, gender, schoolNumber,
                hasMedal, hasComposition, 3, 
                subjectName1, grade1,
                subjectName2, grade2, subjectName3, grade3);   //записываем в файл построчно
        fprintf(fp, "\n");
        
    }

    fclose(fp);
}