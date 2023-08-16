#ifndef io_h
#define io_h

#include "student.h"

int studentReadTxt(Student* s, FILE* in);
int studentReadBin(Student* s, FILE* in);
void studentWriteBin(Student* s, FILE* out);
void studentWriteTxt(Student* s, FILE* file);

#endif
