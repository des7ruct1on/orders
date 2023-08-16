#ifndef tree_h
#define tree_h
#include <stdio.h>
#include <stdlib.h>

typedef struct Tree { // структура бинарного дерева
    int value; // хранимое значение
    struct Tree* left; // указатель на левое поддерево 
    struct Tree* right; // указатель на правое поддерево
} Tree;

Tree* createTree(int value); // функция создания дерева
Tree* insertTree(Tree* root, int value); // функция добавления в дерево
Tree* removeTree(Tree* root, int key); // функция удаления из дерева
Tree* findMinimum(Tree* root); // поиск минимума в дереве
void printTree(Tree* root, int n); // вывод дерева
void freeTree(Tree* root); // освобождение дерева из памяти
#endif