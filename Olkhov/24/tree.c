#include "tree.h"

Tree* create_tree(Symbol value) {
    Tree* new_tree = (Tree*)malloc(sizeof(Tree));
    new_tree->value = value;
    new_tree->parent = NULL;
    new_tree->left = NULL;
    new_tree->right = NULL;
    return new_tree;
}

char opp_to_char(Operator op) {
    switch(op) {
        case OP_MINUS:
        case OP_PLUS:
        case OP_MULTIPLY:
        case OP_DIVIDE:
        case OP_POW:
            return op;
        case OP_UNARY_MINUS:
            return '-';
        case OP_MISTAKE:
            return ';';
    }
    return -1;
}

Operator char_to_op(char c) {
    if (c == '*') {
        return OP_MULTIPLY;
    } else if (c == '/') {
        return OP_DIVIDE;
    } else if (c == '+') {
        return OP_PLUS;
    } else if (c == '-') {
        return OP_MINUS;
    } else if (c == '^') {
        return OP_POW;
    } else if (c == '!') {
        return OP_UNARY_MINUS;
    } else {
        return OP_MISTAKE;
    }

}

void print_tree(Tree* tree, int lvl){
    if(tree->value.type == symb_OP) {
        print_tree(tree->right, lvl + 1);
    }
    for (int i = 0; i < lvl; i++) {
        printf("\t");
    }
    switch(tree->value.type) {
        case symb_NUMBER:
            printf("%.2lf\n", tree->value.data.number);
            break;
        case symb_VAR:
            if(tree->value.data.op == '-'){
                printf("-\n");
                print_tree(tree->right, lvl + 1);
            } else {
                printf("%c\n", tree->value.data.c);
            }
            break;
        case symb_OP:
            if(tree->value.data.op == OP_UNARY_MINUS) {
                printf("-\n");
                print_tree(tree->right, lvl + 1);
            } else {
                printf("%c\n", opp_to_char(tree->value.data.op));
            }
            break;
        default:
            fprintf(stderr, "Ошибка, не существует такого символа");
            return;
    }
    if (tree->value.type == symb_OP) {
        print_tree(tree->left, lvl + 1);
    }
}

Tree* add_node(Tree* t, Symbol value) {
    if (t == NULL) {
        return create_tree(value);
    } 
    if (value.data.c < t->value.data.c) {
        t->left = add_node(t->left, value);
    } else if (value.data.c > t->value.data.c) {
        t->right = add_node(t->right, value);
    }
    return t;
}

void clear_tree(Tree* tree) {
    if (tree == NULL) {
        return;
    }
    clear_tree(tree->left);
    clear_tree(tree->right);
    free(tree);
}


void init_stack(stack* s) {
    s->top = NULL;
    s->size = 0;
}

bool stack_empty(stack* s) {
    return s->size == 0;
}

int stack_size(stack* s) {
    return s->size;
}

void stack_push_tree(stack* s, Tree* value) {
    stack_node* tmp = malloc(sizeof(stack_node));
    tmp->type = TREE;
    tmp->value.tree_value = value;
    tmp->prev = s->top;
    s->top = tmp;
    s->size++;
}

void stack_push_symbol(stack* s, Symbol value) {
    stack_node* tmp = malloc(sizeof(stack_node));
    tmp->type = SYMBOL;
    tmp->value.symbol_value = value;
    tmp->prev = s->top;
    s->top = tmp;
    s->size++;
}

Tree* stack_pop_tree(stack* s) {
    if (stack_size(s) == 0) {
        printf("Стек пуст!\n");
        return NULL;
    }
    stack_node* tmp = s->top;
    Tree* result = tmp->value.tree_value;
    s->top = s->top->prev;
    free(tmp);
    s->size--;
    return result;
}

Symbol stack_pop_symbol(stack* s) {
    if (stack_size(s) == 0) {
        printf("Стек пуст!\n");
        Symbol empty;
        empty.type = symb_NONE;
        empty.data.c = '\0';
        return empty;
    }
    stack_node* tmp = s->top;
    Symbol result = tmp->value.symbol_value;
    s->top = s->top->prev;
    free(tmp);
    s->size--;
    return result;
}

void stack_destroy(stack* s) {
    while (!stack_empty(s)) {
        stack_node* current = s->top;
        s->top = s->top->prev;
        free(current);
    }
    free(s);
}

Tree* stack_top_tree(stack* s) {
    if (stack_size(s) == 0) {
        printf("Стек пуст!\n");
        return NULL;
    }
    return s->top->value.tree_value;
}

Symbol stack_top_symbol(stack* s) {
    if (stack_size(s) == 0) {
        printf("Стек пуст!\n");
        Symbol empty;
        empty.type = symb_NONE;
        empty.data.c = '\0';
        return empty;
    }
    return s->top->value.symbol_value;
}

void push_front(node** head, Symbol data) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = *head;
    new_node->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = new_node;
    }
    *head = new_node;
}

void push_back(node** head, Symbol data) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        new_node->prev = NULL;
        *head = new_node;
        return;
    }

    node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = new_node;
    new_node->prev = current;
}

void delete_back(node* head) {
    if (head == NULL) {
        printf("Список пуст!\n");
        return;
    }

    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }

    node* current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->prev->next = NULL;
    free(current);
}

void delete_front(node* head) {
    if (head == NULL) {
        printf("Список пуст!\n");
        return;
    }

    node* temp = head;
    head = head->next;

    if (head != NULL) {
        head->prev = NULL;
    }

    free(temp);
}

void print_list(node* head) {
    node* current = head;
    while (current != NULL) {
        printf("%c ", current->data.data.c); // Выводим символ из Symbol
        current = current->next;
    }
    printf("\n");
}

void destroy_list(node* head) { // функция очистки списка
    node* current = head;
    while (current != NULL) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

int size_list(node* head) {
    int count = 0;
    node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

bool is_operator(char ch) {
    return (ch == '+' || ch == '*' || ch == '/' || ch == '^');
}

int get_priority(char ch) {
    if (ch == '*' || ch == '/') {
        return 2;
    } else if (ch == '+' || ch == '-') {
        return 1;
    } else {
        return 3;
    }
}

OperatorAssociation op_association(char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/')
        return ASSOC_LEFT;
    else
        return ASSOC_RIGHT;
}
