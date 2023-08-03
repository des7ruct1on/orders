#ifndef arifmtree_h
#define arifmtree_h

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
} symbol_data;

// тип символа
typedef enum {
    symb_NONE,
    symb_OP,
    symb_NUMBER,
    symb_VAR,
    symb_LEFT_BR,
    symb_RIGHT_BR
} symbol_type;

// структура символа
typedef struct {
    symbol_type type;
    symbol_data data;
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
} node_type;

// струтура узла
typedef union {
    char char_value;
    Tree* tree_value;
    Symbol symbol_value;
} node_value;

// структура ассоциативности
typedef enum {
    ASSOC_LEFT,
    ASSOC_RIGHT
} OperatorAssociation;

// структура элемента стека на односвязном списке
typedef struct stack_node {
    node_type type;
    node_value value;
    struct stack_node* prev;
} stack_node;

// структура стека
typedef struct stack {
    stack_node* top;
    int size;
} stack;

//функции дерева
Tree* create_tree(Symbol value);
Tree* add_node(Tree* t, Symbol value);
void print_tree(Tree* tree, int lvl);
void clear_tree(Tree* tree);

// функции стека
void init_stack(stack* s);
bool stack_empty(stack* s);
int stack_size(stack* s);
void stack_push_tree(stack* s, Tree* value);
void stack_push_symbol(stack* s, Symbol value);
Tree* stack_pop_tree(stack* s);
Symbol stack_pop_symbol(stack* s);
void stack_destroy(stack* s);
Tree* stack_top_tree(stack* s);
Symbol stack_top_symbol(stack* s);

// функции списка (можно было реализовать очередь)
void push_front(node** head, Symbol data);
void push_back(node** head, Symbol data);
void delete_back(node* head);
void delete_front(node* head);
void print_list(node* head);
void destroy_list(node* head);
int size_list(node* head);

// функции с лексемами
bool is_operator(char ch);
int get_priority(char ch);
char opp_to_char(Operator op);
Operator char_to_op(char c);
OperatorAssociation op_association(char op);

#endif
