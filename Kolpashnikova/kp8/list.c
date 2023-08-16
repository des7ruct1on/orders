#include "list.h"

void pushFront(node** head, float data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = *head;
    newNode->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void pushBack(node** head, float data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

void deleteFront(node** head) {
    if (*head == NULL) {
        printf("Список пуст!\n");
        return;
    }

    node* temp = *head;
    *head = (*head)->next;

    if (*head != NULL) {
        (*head)->prev = NULL;
    }

    free(temp);
}

void deleteBack(node** head) {
    if (*head == NULL) {
        printf("Список пуст!\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    node* current = *head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->prev->next = NULL;
    free(current);
}

void printList(node* head) {
    node* current = head;
    printf("(");
    while (current != NULL) {
        printf("%.3f ", current->data);
        current = current->next;
    }
    printf(")");
    printf("\n");
}

void destroy(node* head) {
    node* current = head;
    while (current != NULL) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
}

void pushIndex(node** head, float data, int index) {
    if (*head == NULL && index > 0) {
        printf("Список пуст!\n");
        return;
    }

    if (index <= 0) {
        pushFront(head, data);
        return;
    }

    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;

    node* current = *head;
    int currentIndex = 0;

    while (current != NULL && currentIndex < index - 1) {
        current = current->next;
        currentIndex++;
    }

    if (current == NULL) {
        printf("Индекс выходит за пределы списка!\n");
        free(newNode);
        return;
    }

    newNode->next = current->next;
    newNode->prev = current;
    
    if (current->next != NULL) {
        current->next->prev = newNode;
    }

    current->next = newNode;
}

void deleteIndex(node** head, int index) {
    if (*head == NULL) {
        printf("Список пуст!\n");
        return;
    }

    if (index <= 0) {
        deleteFront(head);
        return;
    }

    node* current = *head;
    int currentIndex = 0;

    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    if (current == NULL) {
        printf("Индекс выходит за пределы списка!\n");
        return;
    }

    current->prev->next = current->next;

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
}

int sizeList(node* head) {
    int count = 0;
    node* current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}