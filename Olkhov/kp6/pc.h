#ifndef list_h
#define list_h
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// константы
#define STR_SIZE 24
#define TABLE_SIZE 100
#define MAX_SIZE 256

// структура накопителя
typedef struct solid_driver {
    char name[STR_SIZE];
    char type[2];
    int amount;
} solid_driver;

// структура пользователя
typedef struct person {
    char surname[STR_SIZE];
    char name[STR_SIZE];
    char cpu[STR_SIZE];
    char gpu[STR_SIZE];
    int ram;
    char os[STR_SIZE];
    int num_drivers;
    solid_driver* disks;
} person;

// структура элемента хеш-таблицы и самой таблицы
typedef struct elem_table {
    char key[STR_SIZE];
    person* data;
} elem_table;

typedef struct hash_table {
    elem_table elements[TABLE_SIZE];
} hash_table;

// функции-методы для каждого пользователя
person* create_person();
char* get_surname(person* p);
char* get_name(person* p);
char* get_cpu(person* p);
char* get_gpu(person* p);
int get_ram(person* p);
char* get_os(person* p);
int get_amount_disks(person* p);
solid_driver* get_driver(person* p);

// вспомогательные функции и функции взаимодействия с таблицей
void print_person(person* p);
void print_table(hash_table* table);
void insert_person(const char* key, char* in, hash_table* table);
void erase_person(const char* filename, const char* key, hash_table* table);
void destructor_person(person* p);
bool found_passenger(hash_table* table, const char* key);
bool found_person(hash_table* table, const char* key);

// функции хеш-таблицы
void init_hash_table(hash_table* table);
unsigned int hash(const char* key);
void insert_element(hash_table* table, const char* key, person* value);
person* find_element(hash_table* table, const char* key);
void erase_element(hash_table* table, const char* key);
void destructor_hash_table(hash_table* table);

// чтение и запись файлов
void read_str(person* p, char* str);
void write_person_txt(person* p, FILE* file);
int read_bin(person* p, FILE* in);
void write_person_bin(person* p, FILE* out);
#endif