#ifndef STUDENT_H
#define STUDENT_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define STR_SIZE 256
#define TABLE_SIZE 100
#define MAX_SIZE 24


// структура ученика
typedef struct student {
    char surname[MAX_SIZE];
    char initials[MAX_SIZE];
    char gender[MAX_SIZE];
    int class_num;
    char index;
    int school_num;
} student;

// структура элемента таблицы
typedef struct cell {
    char key[STR_SIZE]; // ключ
    student* data; // пассажир
} cell;

// структура хеш-таблицы
typedef struct hash_table {
    cell cells[TABLE_SIZE];
} hash_table;

// функции чтения и записи
int read_student_bin(student* s, FILE* in);
void write_student_txt(student* s, FILE* in);
void write_student_bin(student* s, FILE* in);
void read_from_str(student* s, char* line);
int read_string_bin(char* str, FILE* in);
void write_string_bin(const char* str, FILE* out);

// функции для пассажира
char* get_surname(student* s);
char* get_initials(student* s); 
student* create_student();
void print_student(student* s);
void print_table(hash_table* table);
void insert_student(const char* key, char* in, hash_table* table);
void erase_student(const char* filename, const char* key, hash_table* table);
void destructor_student(student* s);
bool found_student(hash_table* table, const char* key);

// функции хеш-таблицы
void init_hash_table(hash_table* table);
unsigned int hash(const char* key);
void insert_element(hash_table* table, const char* key, student* value);
student* find_element(hash_table* table, const char* key);
void erase_element(hash_table* table, const char* key);
void destructor_hash_table(hash_table* table);
#endif