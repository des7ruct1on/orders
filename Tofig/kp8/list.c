#include "list.h"

void pushFront(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = (*head)->next;
    (*head)->next = newNode;
}

void pushBack(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void pushIndex(Node** head, int value, int index) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;

    Node* current = *head;
    int count = 0;
    while (current->next != NULL && count < index - 1) {
        current = current->next;
        count++;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void deleteFront(Node** head) {
    if ((*head)->next != NULL) {
        Node* toDelete = (*head)->next;
        (*head)->next = toDelete->next;
        free(toDelete);
    }
}

void deleteBack(Node** head) {
    Node* current = *head;
    while (current->next != NULL && current->next->next != NULL) {
        current = current->next;
    }
    if (current->next != NULL) {
        Node* toDelete = current->next;
        current->next = NULL;
        free(toDelete);
    }
}

void deleteIndex(Node** head, int index) {
    Node* current = *head;
    int count = 0;
    while (current->next != NULL && count < index - 1) {
        current = current->next;
        count++;
    }
    if (current->next != NULL) {
        Node* toDelete = current->next;
        current->next = toDelete->next;
        free(toDelete);
    }
}

void printList(Node* head) {
    Node* current = head->next;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void destroy(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* toDelete = current;
        current = current->next;
        free(toDelete);
    }
}

int sizeList(Node* head) {
    Node* current = head->next;
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}