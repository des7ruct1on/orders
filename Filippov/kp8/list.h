#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>

#define STR_SIZE 24 // константа для строки

//структура списка
typedef struct node { 
    char* data; // строка
    struct node* prev; //указатель на предыдущий
    struct node* next; //указатель на следующий
} Node;

void push_front(Node** head, char* data);
void push_back(Node** head, char* data);
void push_index(Node** head, char* data, int k);
void delete_back(Node** head);
void delete_front(Node** head);
void delete_index(Node** head, int k);
void print_list(Node* head);
void destroy_list(Node* head);
int size_list(Node* head);

#endif