#ifndef abiturient_h
#define abiturient_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// константы
#define STRSIZE 256
#define TABLESIZE 100
#define MAXSIZE 24

//структура структура одного экзамена
typedef struct value{
    char subject[MAXSIZE];
    int ball;
} value;

//структура двусвязного списка
typedef struct node { 
    value data;
    struct node* next;
    struct node* prev;
} node;


//структура абитуриента
typedef struct abiturient {
    char surname[MAXSIZE];
    char initials[MAXSIZE];
    char gender[MAXSIZE];
    int schoolNum;
    char medal[MAXSIZE];
    char composition[MAXSIZE];
    int numExams;
    node* examStats;
} abiturient;


//элемент хеш-таблицы
typedef struct element {
    char key[STRSIZE];
    abiturient* value;
} element;

//хеш-таблица
typedef struct hashtable {
    element entries[TABLESIZE];
} HashTable;

// функции списка
void pushFront(node** head, value data);
void pushBack(node** head, value data);
void popBack(node* head);
void popFront(node* head);
void printList(node* head);
void destroy(node* head);
int sizeList(node* head);

// функции хеш-таблицы и хеширования
void initHashTable(HashTable* table);
unsigned int hash(const char* key);
void insertElement(HashTable* table, const char* key, abiturient* value);
abiturient* findElement(HashTable* table, const char* key);
void removeElement(HashTable* table, const char* key);
void clearHashTable(HashTable* table);

//методы абитуриента и функции абитуриента
char* getSurname(abiturient* s);
char* getInitials(abiturient* s);
abiturient* newAbiturient();
void addAbiturient(const char* filename, char* in, HashTable* table);
void addAbiturientBin(const char* filename, char* in, HashTable* table);
void removeStudent(const char* file, const char* id, HashTable* table);
void removeStudentBin(const char* file, const char* id, HashTable* table);
void printAbiturientChars(abiturient* s);
void abiturientFree(abiturient* s);
void printAbiturientStr(HashTable* table);
bool isAbiturientExists(HashTable* table, const char* key);

//функции чтения
void readFromLine(abiturient* s, char* line);
int abiturientReadTxt(abiturient* s, FILE* in);
void abiturientWriteTxt(abiturient* s, FILE* file);
int abiturientReadBin(abiturient* s, FILE* in);
void abiturientWriteBin(abiturient* s, FILE* out);


#endif

