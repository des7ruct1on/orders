#ifndef student_h
#define student_h
#include <stdint.h>
#include <stdbool.h>
#define STRSIZE 24

typedef struct {
    char surname[STRSIZE];
    char initials[3];
    char gender;
    char group;
    char university[STRSIZE];
    char job[STRSIZE];
    int course;
} Student;

typedef struct Table {
    int id;
    Student st;
    struct Table *prev;
} Table;

void destroyTable(Table* t);
int findPerson(Table* t, char* surname);
Table* createTable(FILE* in);
int infoStudent(FILE* in, char* surname, char* initials);
Table* addStudent(FILE* file, Table* t);
void removeStudent(char* file, char* surname, char* initials, Table** t);
void countGenderPerGroup(Table* t);
#endif
