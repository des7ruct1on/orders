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
} num;

typedef struct Node {
    num value;
    struct Node* next;
} Node;

void push_front(Node** head, num val);
void push_back(Node** head, num val);
void push_index(Node** head, num val, int k);
void pop_back(Node** head);
void pop_front(Node** head);
void pop_index(Node** head, int k);
void print_list(Node* head);
void delete_list(Node* head);
int size_list(Node* head);
num convert_num(char* str);
char* convert_str(num number);

#endif