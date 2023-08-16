#include <stdio.h>
#include <stdlib.h>

#include "student.h"
#include "io.h"

int studentReadTxt(Student* s, FILE* in) {
    fscanf(in, "%s %s %c %d %c %s %s", s->surname, s->initials, &s->gender, &s->course, &s->group, s->university, s->job);
    return !feof(in);
}

void studentWriteTxt(Student* s, FILE* file) {
    fprintf(file, "%s\t", s->surname);
    fprintf(file, "%s\t", s->initials);
    fprintf(file, "%c\t", s->gender);
    fprintf(file, "%d\t", s->course);
    fprintf(file, "%c\t", s->group);
    fprintf(file, "%s\t", s->university);
    fprintf(file, "%s\t", s->job);
    fprintf(file, "\n");
}

int studentReadBin(Student* s, FILE* in) {
    fread(s->surname, sizeof(char), STRSIZE, in);
    fread(s->initials, sizeof(char), 3, in);
    fread(&s->gender, sizeof(char), 1, in);
    fread(&s->course, sizeof(int), 1, in);
    fread(&s->group, sizeof(char), 1, in);
    fread(s->university, sizeof(char), STRSIZE, in);
    fread(s->job, sizeof(char), STRSIZE, in);
    return !feof(in);
}

void studentWriteBin(Student* s, FILE* out) {
    fwrite(s->surname, sizeof(char), STRSIZE, out);
    fwrite(s->initials, sizeof(char), 3, out);
    fwrite(&s->gender, sizeof(char), 1, out);
    fwrite(&s->course, sizeof(int), 1, out);
    fwrite(&s->group, sizeof(char), 1, out);
    fwrite(s->university, sizeof(char), STRSIZE, out);
    fwrite(s->job, sizeof(char), STRSIZE, out);
} 

