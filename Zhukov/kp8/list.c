#include "list.h"

// Инициализация пустого списка с барьерным элементом
void init_list(Linked_list* list) {
    list->barrier = (Node*)malloc(sizeof(Node));
    list->barrier->next = NULL;
    list->size = 0;
}

// Добавление элемента в конец списка
void append(Linked_list* list, Complex data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    Node* current = list->barrier;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    list->size++;
}

// Удаление элемента по индексу k
void remove_index(Linked_list* list, int k) {
    if (k < 0 || k >= list->size) {
        printf("Ошибка: недопустимый индекс\n");
        return;
    }

    Node* current = list->barrier;
    for (int i = 0; i < k; i++) {
        current = current->next;
    }
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);

    list->size--;
}

// Вывод списка на экран
void print_list(Linked_list* list) {
    Node* current = list->barrier->next; // Пропускаем барьерный элемент
    int count = 0;
    int size = get_size(&list);
    printf("(");
    while (current != NULL) {
        if (current->data.real == 0) {
            printf("%di",current->data.im);
        } else if (current->data.im == 0) {
            printf("%d", current->data.real);
        } else {
            printf("%d + %di", current->data.real, current->data.im);
        }
        count++;
        if (count != size) {
            printf(", ");
        }
        current = current->next;
    }
    printf(")");
    printf("\n");
}

// Получение размера списка
int get_size(Linked_list* list) {
    return list->size;
}

void clear_list(Linked_list* list) {
    Node* current = list->barrier;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->barrier = NULL;
    list->size = 0;
}

void pop_back(Linked_list* list) {
    if (list->size == 0) {
        printf("Ошибка: список пуст\n");
        return;
    }

    Node* current = list->barrier;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;

    list->size--;
}
void insert_at(Linked_list* list, int index, Complex data) {
    if (index < 0 || index > list->size) {
        printf("Ошибка: недопустимый индекс\n");
        return;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;

    Node* current = list->barrier;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
    list->size++;
}