#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {
    One,
    Two,
    Three,
    Four,
    Five
} numbers;

typedef struct node { //структура списка
    numbers data; // цифры
    struct node* prev; //указатель на предыдущий
    struct node* next; //указатель на следующий
} Node;

void pushFront(Node** head, numbers data);
void pushBack(Node** head, numbers data);
void pushIndex(Node** head, numbers data, int k);
void deleteBack(Node** head);
void deleteFront(Node** head);
void deleteIndex(Node** head, int k);
void printList(Node* head);
void destroyList(Node* head);
int sizeList(Node* head);
numbers convertToNum(char* str);
char* convertToStr(numbers num);
#endif