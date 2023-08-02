#include "list.h"

void push_front(Node** head, char* data) { //функция добавления спереди
    Node* new_node = (Node*)malloc(sizeof(Node)); //выделяем память
    new_node->data = data; //присваиваем значение литеры
    if (*head == NULL) { //если "голова" пустая
        *head = new_node; //добавленный элемент - голова списка
        new_node->prev = new_node->next = new_node; //ссылка на самого себя
    } else { // иначе
        Node* last = (*head)->prev; 
        new_node->prev = last; //предыдущий нового элемента - предыдущий у головы
        new_node->next = *head; //некст - head
        (*head)->prev = new_node; //связываем голову и новый элемент сзади
        last->next = new_node; //связываем некст и новый
        *head = new_node;
    }
}

void push_index(Node** head, char* data, int k) {
    int size = size_list(*head);
    if (k > size || k < 0) {
        printf("Выход за границы списка!\n");
        return;
    }
    Node* new_node = (Node*)malloc(sizeof(Node)); //выделяем память под новый элемент
    new_node->data = data; //присваиваем значение стркои
    Node* current = *head;
    if (*head == NULL && k == 0) {
        *head = new_node;
        current = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    } else if (k == 0) {
        Node* last = current->prev;
        last->next = new_node;
        new_node->prev = last;
        current->prev = new_node;
        new_node->next = current;
        *head = new_node;
    } else {    
        for (int i = 0; i < k; i++) { // движемся до k
            current = current->next;
        }
        Node* left = current->prev;
        left->next = new_node;
        new_node->prev = left;
        current->prev = new_node;
        new_node->next = current;
    }
}

void delete_index(Node** head, int k) {
    int size = size_list(*head);
    if (k > size || k < 0) {
        printf("Выход за границы списка!\n");
        return;
    }
    if(*head == NULL) {
        return;
    }
    if (k == 0) {
        if ((*head)->next == *head) { // если в списке 1 элемент
            free((*head)->data);
            free(*head);
            *head = NULL;
        } else {
            Node* last = (*head)->prev;
            Node* second = (*head)->next;
            last->next = second;
            second->prev = last;
            free((*head)->data);
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
        free(current->data);
        free(current);
    }
}

void push_back(Node** head, char* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));//выделяем память
    new_node->data = data;
    if (*head == NULL) {//если list пустой
        *head = new_node;//добавленный элемент теперь головной
        new_node->prev = new_node->next = new_node;//ссылка на самого себя
    } else {
        Node* last = (*head)->prev;
        new_node->prev = last;
        new_node->next = *head;
        (*head)->prev = new_node;
        last->next = new_node;
    }
}

void delete_front(Node** head) { //функция удаления спереди
    if (*head == NULL) { 
        printf("Список пуст!\n");
    } else if ((*head)->next == *head) { //если только один элемент в списке
        free((*head)->data);
        free(*head);
        *head = NULL;
    } else {
        Node* last = (*head)->prev; //заопминаем предыдуший и некст
        Node* second = (*head)->next;
        last->next = second; //вычленяем голову и связываем запомнившиеся элементы
        second->prev = last;
        free((*head)->data);
        free(*head);
        *head = second; //нвоая голова
    }
}

void delete_back(Node** head) { //функция удаления сзади
    if (*head == NULL) {
        printf("Список пуст!\n");
    } else if ((*head)->next == *head) { //если только один элемент в списке
        free((*head)->data);
        free(*head);
        *head = NULL;
    }else {  // инверсия функции удаления спереди
        Node* last = (*head)->prev;
        Node* second = last->prev;
        second->next = *head;
        (*head)->prev = second;
        free(last->data);
        free(last);
    }
}

void destroy_list(Node* head) { //функция очистки 
    if (head == NULL) {
        return;
    } else {
        Node* current = head; //начинаем с головы
        do {
            Node* tmp = current->next; //пока не вернулись к голове, движемся 
            free(current->data);
            free(current); //освобождаем 
            current = tmp;
        } while (current != head);
    }
}


void print_list(Node* head) { //функция вывода списка
    if (head == NULL) {
        printf("Список пуст!\n");
    } else {
        Node* current = head;
        printf("("); //печатаем скобку для красоты
        do {
            printf("%s", current->data); //двигаемся пока не дошли до головы
            current = current->next;
            if(current != head) { //печатаем запятую
                printf(", ");
            }
        } while (current != head);
        printf(")");
    }
}

int size_list(Node* head) { //функция вывода размера списка
    if (head == NULL) {
        return 0;
    } else {
        Node* current = head;
        int counter = 0;
        do { //пока не дошли до головы увеличиваем счетчик
            counter++;
            current = current->next;
        } while (current != head);
        return counter;
    }
}