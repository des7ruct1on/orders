#ifndef tree_h
#define tree_h

#include <ctype.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define MAX_EXPRESSION_LENGTH 100

// операторы
typedef enum {
    OP_PLUS = '+',
    OP_MINUS = '-',
    OP_MULTIPLY = '*',
    OP_DIVIDE = '/',
    OP_UNARY_MINUS ='!',
    OP_POW = '^',
    OP_MISTAKE = ';'
} Operator;

// данные символа
typedef union {
    char c;
    float number;
    Operator op;
} SymbolData;

// тип символа
typedef enum {
    symb_NONE,
    symb_OP,
    symb_NUMBER,
    symb_VAR,
    symb_LEFT_BR,
    symb_RIGHT_BR
} SymbolType;

// структура символа
typedef struct {
    SymbolType type;
    SymbolData data;
} Symbol;

// структура дерева
typedef struct Tree {
    Symbol value;
    struct Tree* parent;
    struct Tree* left;
    struct Tree* right;
} Tree;

//структура списка
typedef struct node { 
    Symbol data;
    struct node* next;
    struct node* prev;
} node;

// типы данных для стека(нужен для создания дерева из выражения)
typedef enum { 
    TREE,
    SYMBOL
} NodeType;

// струтура узла
typedef union {
    char charValue;
    Tree* treeValue;
    Symbol symbolValue;
} NodeValue;

// структура ассоциативности
typedef enum {
    ASSOC_LEFT,
    ASSOC_RIGHT
} OperatorAssociation;

// структура элемента стека на односвязном списке
typedef struct stackNode {
    NodeType type;
    NodeValue value;
    struct stackNode* prev;
} stackNode;

// структура стека
typedef struct stack {
    stackNode* top;
    int size;
} stack;

//функции дерева
Tree* createTree(Symbol value);
Tree* newNode(Tree* t, Symbol value);
void printTree(Tree* tree, int lvl);
void clearTree(Tree* tree);

// функции стека
void initStack(stack* s);
bool stackEmpty(stack* s);
int stackSize(stack* s);
void stackPushTree(stack* s, Tree* value);
void stackPushSymbol(stack* s, Symbol value);
Tree* stackPopTree(stack* s);
Symbol stackPopSymbol(stack* s);
void stackDestroy(stack* s);
Tree* stackTopTree(stack* s);
Symbol stackTopSymbol(stack* s);

// функции списка (можно было реализовать очередь)
void pushFront(node** head, Symbol data);
void pushBack(node** head, Symbol data);
void deleteBack(node* head);
void deleteFront(node* head);
void printList(node* head);
void destroyList(node* head);
int sizeList(node* head);

// функции с лексемами
bool isOperator(char ch);
int getPriority(char ch);
char oppToChar(Operator op);
Operator charToOp(char c);
OperatorAssociation opAssociation(char op);

#endif
