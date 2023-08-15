#ifndef AEROFLOT_H
#define AEROFLOT_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define STR_SIZE 256
#define TABLE_SIZE 100
#define MAX_SIZE 24

// структура времени
typedef struct time_value {
    int hour;
    int minute;
} time_value;

// структура пассажира
typedef struct passenger {
    char surname[MAX_SIZE];
    char initials[3];
    int items_num;
    int total_weight;
    char destination[MAX_SIZE];
    time_value time;
    int transfer;
    int num_childrens;
} passenger;

// структура элемента таблицы
typedef struct cell {
    char key[STR_SIZE]; // ключ
    passenger* data; // пассажир
} cell;

// структура хеш-таблицы
typedef struct hash_table {
    cell cells[TABLE_SIZE];
} hash_table;

// функции чтения и записи
int read_passenger_bin(passenger* p, FILE* in);
void write_passenger_txt(passenger* p, FILE* in);
void write_passenger_bin(passenger* p, FILE* in);
void read_from_str(passenger* p, char* line);
int read_string_bin(char* str, FILE* in);
void write_string_bin(const char* str, FILE* out);

// функции для пассажира
char* get_surname(passenger* p);
char* get_initials(passenger* p); 
passenger* create_passenger();
void print_passenger(passenger* p);
void print_table(hash_table* table);
void insert_passenger(const char* key, char* in, hash_table* table);
void erase_passenger(const char* filename, const char* key, hash_table* table);
void destructor_passenger(passenger* p);
bool found_passenger(hash_table* table, const char* key);

// функции хеш-таблицы
void init_hash_table(hash_table* table);
unsigned int hash(const char* key);
void insert_element(hash_table* table, const char* key, passenger* value);
passenger* find_element(hash_table* table, const char* key);
void erase_element(hash_table* table, const char* key);
void destructor_hash_table(hash_table* table);
#endif