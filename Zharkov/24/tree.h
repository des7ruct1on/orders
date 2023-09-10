#ifndef tree_h
#define tree_h

#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define MAX_EXPRESSION_LENGTH 100


typedef enum { // операторы
    OP_PLUS = '+',
    OP_MINUS = '-',
    OP_MULTIPLY = '*',
    OP_DIVIDE = '/',
    OP_UNARY_MINUS ='!',
    OP_POW = '^',
    OP_MISTAKE = ';'
} Operator;


typedef union { // данные символа
    char c;
    float number;
    Operator op;
} symbol_data;

typedef enum { // тип символа
    symb_NONE,
    symb_OP,
    symb_NUMBER,
    symb_VAR,
    symb_LEFT_BR,
    symb_RIGHT_BR
} symbol_type;

typedef struct { // структура символа
    symbol_type type;
    symbol_data data;
} Symbol;

typedef struct Tree { // структура дерева
    Symbol value;
    struct Tree* parent;
    struct Tree* left;
    struct Tree* right;
} Tree;

typedef struct node { //структура списка
    Symbol data;
    struct node* next;
    struct node* prev;
} node;

typedef enum { // типы данных стека
    TREE,
    SYMBOL
} node_type;

typedef union { // струтура узла
    char char_value;
    Tree* tree_value;
    Symbol symbol_value;
} node_value;

typedef enum { // ассоциативность
    ASSOC_LEFT,
    ASSOC_RIGHT
} OperatorAssociation;

typedef struct stack_node { // структура элемента стека на односвязном списке
    node_type type;
    node_value value;
    struct stack_node* prev;
} stack_node;

typedef struct stack { // структура стека
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

// функции списка 
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
