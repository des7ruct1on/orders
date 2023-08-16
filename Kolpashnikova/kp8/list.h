#ifndef list_h
#define list_h
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    float data;
    struct node* next;
    struct node* prev;
} node;

void destroy(node* head);
void printList(node* head);
void deleteBack(node** head);
void deleteFront(node** head);
void pushBack(node** head, float data);
void pushFront(node** head, float data);
void deleteIndex(node** head, int index);
void pushIndex(node** head, float data, int index);
int sizeList(node* head);
#endif