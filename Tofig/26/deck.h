#ifndef deck_h
#define deck_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct element {
    int value; //значение
    struct element *next; //указ на след элемент
    struct element *prev; //указ на пред элемент
} element;

typedef struct deck {
    element *first; //первый элемент
    element *last; //последний элемент
    int size; //рамзер
} deck;

void initDeck(deck *D);
int size(deck *D);
bool empty(deck *D);
void pushFront(deck *D, int value);
void pushBack(deck *D, int value);
int popFront(deck *D);
int popBack(deck *D);
int topFront(deck *D);
int topBack(deck *D);
void deleteDeck(deck *D);
deck *cat(deck *D1, deck *D2);
void append(deck *D1, deck *D2);
void printDeck(deck *D);

#endif
