#include "list.h"


numbers convertToNum(char* str) { // функция конвертации из строки в numbers(проверяем верхние и нижние регистры)
    if ((!strcmp(str, "One")) || (!strcmp(str, "one"))) {
        return One;
    } else if ((!strcmp(str, "Two")) || (!strcmp(str, "two"))) {
        return Two;
    } else if ((!strcmp(str, "Three")) || (!strcmp(str, "three"))) {
        return Three;
    } else if ((!strcmp(str, "Four")) || (!strcmp(str, "four"))) {
        return Four;
    } else if ((!strcmp(str, "Five")) || (!strcmp(str, "five"))) {
        return Five;
    } else {
        printf("Этой цифры нет!\n");
        return -1; 
    }
}

char* convertToStr(numbers num) { //функция конвертации из элемента enum`а в строку
    switch (num) {
        case 0:
            return "One";
            break;
        case 1:
            return "Two";
            break;
        case 2:
            return "Three";
            break;
        case 3:
            return "Four";
            break;
        case 4:
            return "Five";
            break;
    }
    return NULL; 
}

void pushFront(Node** head, numbers data) { //добавление спереди
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if (*head == NULL) {
        *head = newNode;
        newNode->prev = newNode->next = newNode;
    } else {
        Node* last = (*head)->prev;
        newNode->prev = last;
        newNode->next = *head;
        (*head)->prev = newNode;
        last->next = newNode;
        *head = newNode;
    }
}

void pushIndex(Node** head, numbers data, int k) { //добавление по индексу
    int size = sizeList(*head);
    if (k > size || k < 0) {
        printf("Выход за границы списка!\n");
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    Node* current = *head;
    if (*head == NULL && k == 0) {
        *head = newNode;
        current = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else if (k == 0) {
        Node* last = current->prev;
        last->next = newNode;
        newNode->prev = last;
        current->prev = newNode;
        newNode->next = current;
        *head = newNode;
    } else {
        for (int i = 0; i < k; i++) {
            current = current->next;
        }
        Node* left = current->prev;
        left->next = newNode;
        newNode->prev = left;
        current->prev = newNode;
        newNode->next = current;
    }
}

void deleteIndex(Node** head, int k) { //удаление по индексу
    int size = sizeList(*head);
    if (k > size || k < 0) {
        printf("Выход за границы списка!\n");
        return;
    }
    if(*head == NULL) {
        return;
    }
    if (k == 0) {
        if ((*head)->next == *head) {
            free(*head);
            *head = NULL;
        } else {
            Node* last = (*head)->prev;
            Node* second = (*head)->next;
            last->next = second;
            second->prev = last;
            free(*head);
            *head = second;
        }
    } else {
        Node* current = *head;
        for(int i = 0; i < k; i++) {
            current = current->next;
        }
        Node* left = current->prev;
        Node* right = current->next;
        left->next = right;
        right->prev = left;
        free(current);
    }
}

void pushBack(Node** head, numbers data) { //добавление в конец
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if (*head == NULL) {
        *head = newNode;
        newNode->prev = newNode->next = newNode;
    } else {
        Node* last = (*head)->prev;
        newNode->prev = last;
        newNode->next = *head;
        (*head)->prev = newNode;
        last->next = newNode;
    }
}

void deleteFront(Node** head) { //удаление спереди
    if (*head == NULL) {
        printf("Список пуст!\n");
    } else if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
    } else {
        Node* last = (*head)->prev;
        Node* second = (*head)->next;
        last->next = second;
        second->prev = last;
        free(*head);
        *head = second;
    }
}

void deleteBack(Node** head) { //удаление сзади
    if (*head == NULL) {
        printf("Список пуст!\n");
    } else if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
    } else {
        Node* last = (*head)->prev;
        Node* second = last->prev;
        second->next = *head;
        (*head)->prev = second;
        free(last);
    }
}

void destroyList(Node* head) { //функция очистки списка
    if (head == NULL) {
        return;
    } else {
        Node* current = head;
        do {
            Node* tmp = current->next;
            free(current);
            current = tmp;
        } while (current != head);
    }
}

void printList(Node* head) { //функция вывода значений из списка
    if (head == NULL) {
        printf("Список пуст!\n");
    } else {
        Node* current = head;
        printf("(");
        char* tmp;
        do {
            tmp = convertToStr(current->data);//конвертируем в строку
            printf("%s", tmp);
            current = current->next;
            if(current != head) {
                printf(", ");
            }
        } while (current != head);
        printf(")");
    }
}

int sizeList(Node* head) { //функция размера списка
    if (head == NULL) {
        return 0;
    } else {
        Node* current = head;
        int counter = 0;
        do {
            counter++;
            current = current->next;
        } while (current != head);
        return counter;
    }
}
