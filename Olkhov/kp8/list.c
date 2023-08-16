#include "list.h"

void push_front(Node** head, num val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = val;
    new_node->next = *head;
    *head = new_node;
}

void push_back(Node** head, num val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = val;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
}

void push_index(Node** head, num val, int k) {
    if (k == 0) {
        push_front(head, val);
        return;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = val;

    Node* current = *head;
    for (int i = 0; i < k - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return; 
    }

    new_node->next = current->next;
    current->next = new_node;
}

void pop_front(Node** head) {
    if (*head == NULL) {
        return;
    }

    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void pop_back(Node** head) {
    if (*head == NULL) {
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Node* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
}

void pop_index(Node** head, int k) {
    if (*head == NULL) {
        return;
    }

    if (k == 0) {
        pop_front(head);
        return;
    }

    Node* current = *head;
    for (int i = 0; i < k - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL || current->next == NULL) {
        return; 
    }

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        num tmp = current->value;
        printf("%s ", convert_str(tmp));
        current = current->next;
    }
    printf("\n");
}

void delete_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int size_list(Node* head) {
    int size = 0;
    Node* current = head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}


num convert_num(char* str) { 
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

char* convert_str(num number) { 
    switch (number) {
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