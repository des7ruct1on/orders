#include "deck.h"
void initDeck(deck *D) {
    D->size = 0;
    D->first = NULL;
    D->last = NULL;
}

int size(deck *D) { //функция, вычисляющая значение дека
    return D->size;
}


bool empty(deck *D) {
    if (D->size == 0) {
        return true;
    }
    return false;
}

void pushFront(deck *D, int value) {
    element *tmp = (element *) malloc(sizeof(element)); //выделяем память на элемент
    tmp->value = value;//передаем ему значение из аргумента функции
    tmp->prev = NULL; //так как добавили спереди, то перед ним пусто
    tmp->next = D->first; // следующий для нашего элемента это бывший первый
    if (D->first) {
        D->first->prev = tmp; //теперь предыдущий для бывшего первого - новый
    }
    D->first = tmp; //теперь первый элемент в деке - новый элемент
    if (!D->last) { //если дек пуст
        D->last = tmp;
    }
    D->size++; //увеличиваем размер дека
}

void pushBack(deck *D, int value) { //добавление в конец
    element *tmp = (element *) malloc(sizeof(element)); //выделяем память
    tmp->value = value; //передаем значение
    tmp->next = NULL; //очевидно что след элемент - пустой
    tmp->prev = D->last; //указатель на предыдущий - последний элемент дека
    if (D->last) { //если есть последний
        D->last->next = tmp;
    }
    D->last = tmp; //последний - новый
    if (!D->first) { //если дек пуст
        D->first = tmp;
    }
    D->size++; //увеличиваем размер дека
}

int popFront(deck *D) {//взятие спереди
    if (empty(D)) { //проверка на пустоту дека
        printf("Дек пустой!");
        return -1;
    }
    element *tmp = D->first;
    int value = tmp->value;
    D->first = tmp->next;
    if (D->size == 1) D->last = NULL;
    free(tmp);
    tmp = NULL;
    D->size--; //уменьшаем размер
    return value; //возвращаем значение
}


int popBack(deck *D) { //взятие с конца
    if (empty(D)) { //проверка на пустоту дека
        printf("Дек пустой!");
        return -1;
    }
    element *tmp = D->last;
    int value = tmp->value;
    D->last = tmp->prev;
    if (D->size == 1) D->first = NULL;
    free(tmp);
    tmp = NULL;
    D->size--; //уменьшаем размер
    return value; //возвращаем значение

}

int topFront(deck *D) {
    if (empty(D)) {
        printf("Дек пуст!\n");
        return 1;
    }
    return D->first->value;
}

int topBack(deck *D) {
    if (empty(D)) {
        printf("Дек пуст!\n");
        return 1;
    }
    return D->last->value;
}

/*bool deleteDeck(deck* D) {
    if (empty(D)) { // если дек пуст
        return false;
    }
    element* tmp = D->first->next;
    free(D->first);
    D->size--;
    if (tmp == 0) {
        D->first = D->last = tmp;
        return true;
    }
    D->first = tmp;
    D->first->prev = 0;
    return deleteDeck(D);
}
 */
void deleteDeck(deck *D) {
    int i = 0;
    element *tmp = D->first;
    for (i = size(D); i > 0; i--) {
        element *next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(D);
}

deck *cat(deck *D1, deck *D2) { //конкатенация дека
    while (!empty(D2)) { //пока второй не пуст
        pushBack(D1, popFront(D2)); //добавляем элемент второго
    }
    return D1;
}

void append(deck *D1, deck *D2) {//добавление 1-ого в конец второго
    cat(D1, D2);
    for (int i = 0; i < size(D2); i++) {
        pushBack(D2, popFront(D2));
    }
}

void printDeck(deck *D) { //вывод дека
    if (empty(D)) { //если пустой
        printf("\n Дек пустой! \n");
    } else {
        printf("\n ( "); //скобка для вида
        element *tmp = D->first; //объявляем элемент, который будем выводить
        while (tmp) { //пока элемент существует в деке
            printf("%d ", tmp->value); //вывод
            tmp = tmp->next; //сдвигаем на следующий
        }
        printf(")\n"); //закрываем скобку
    }
}
