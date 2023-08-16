#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>

typedef struct Node { //структура списка
    int data; 
    struct Node* next; //указатель на следующий
} Node;

void pushFront(Node** head, int data);
void pushBack(Node** head, int data);
void pushIndex(Node** head, int data, int k);
void deleteBack(Node** head);
void deleteFront(Node** head);
void deleteIndex(Node** head, int k);
void printList(Node* head);
void destroy(Node* head);
int sizeList(Node* head);

#endif