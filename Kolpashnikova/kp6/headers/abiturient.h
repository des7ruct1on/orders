#ifndef abiturient_h
#define abiturient_h
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define STRSIZE 256
#define TABLESIZE 100
#define MAXSIZE 24

typedef int Item;


typedef struct value{
    char subject[MAXSIZE];
    int ball;
} value;

typedef struct node { //структура двусвязного списка
    value data;
    struct node* next;
    struct node* prev;
} node;

typedef struct abiturient {
    char surname[MAXSIZE];
    char initials[MAXSIZE];
    char sex[MAXSIZE];
    Item schoolNum;
    char medal[MAXSIZE];
    char composition[MAXSIZE];
    Item numExams;
    node* examStats;
} abiturient;

typedef struct entry {
    char key[STRSIZE];
    abiturient* value;
} Entry;

typedef struct hashtable {
    Entry entries[TABLESIZE];
} HashTable;

void pushFront(node** head, value data);
void pushBack(node** head, value data);
void deleteBack(node* head);
void deleteFront(node* head);
void printList(node* head);
void destroy(node* head);
int sizeList(node* head);

void initHashTable(HashTable* table);
unsigned int hash(const char* key);
void insertElement(HashTable* table, const char* key, abiturient* value);
abiturient* findElement(HashTable* table, const char* key);
void removeElement(HashTable* table, const char* key);
void clearHashTable(HashTable* table);

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
void task(HashTable* table);

void readFromLine(abiturient* s, char* line);
int abiturientReadTxt(abiturient* s, FILE* in);
void abiturientWriteTxt(abiturient* s, FILE* file);
int abiturientReadBin(abiturient* s, FILE* in);
void abiturientWriteBin(abiturient* s, FILE* out);


#endif

