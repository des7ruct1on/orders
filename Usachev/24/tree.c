#include "tree.h"

Tree* createTree(Symbol value) {
    Tree* newTree = (Tree*)malloc(sizeof(Tree));
    newTree->value = value;
    newTree->parent = NULL;
    newTree->left = NULL;
    newTree->right = NULL;
    return newTree;
}

char oppToChar(Operator op) {
    switch(op) {
        case OP_MINUS:
        case OP_PLUS:
        case OP_MULTIPLY:
        case OP_DIVIDE:
        case OP_POW:
            return op;
        case OP_UNARY_MINUS:
            return '-';
    }
    return -1;
}

void printTree(Tree* tree, int lvl){
    if(tree->value.type == symb_OP) {
        printTree(tree->right, lvl + 1);
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
                printTree(tree->right, lvl + 1);
            } else {
                printf("%c\n", tree->value.data.c);
            }
            break;
        case symb_OP:
            if(tree->value.data.op == OP_UNARY_MINUS) {
                printf("-\n");
                printTree(tree->right, lvl + 1);
            } else {
                printf("%c\n", oppToChar(tree->value.data.op));
            }
            break;
        default:
            fprintf(stderr, "Ошибка, не существует такого символа");
            return;
    }
    if (tree->value.type == symb_OP) {
        printTree(tree->left, lvl + 1);
    }
}

Tree* newNode(Tree* t, Symbol value) {
    if (t == NULL) {
        return createTree(value);
    } 
    if (value.data.c < t->value.data.c) {
        t->left = newNode(t->left, value);
    } else if (value.data.c > t->value.data.c) {
        t->right = newNode(t->right, value);
    }
    return t;
}

void clearTree(Tree* tree) {
    if (tree == NULL) {
        return;
    }
    clearTree(tree->left);
    clearTree(tree->right);
    free(tree);
}


void initStack(stack* s) {
    s->top = NULL;
    s->size = 0;
}

bool stackEmpty(stack* s) {
    return s->size == 0;
}

int stackSize(stack* s) {
    return s->size;
}

void stackPushTree(stack* s, Tree* value) {
    stackNode* tmp = malloc(sizeof(stackNode));
    tmp->type = TREE;
    tmp->value.treeValue = value;
    tmp->prev = s->top;
    s->top = tmp;
    s->size++;
}

void stackPushSymbol(stack* s, Symbol value) {
    stackNode* tmp = malloc(sizeof(stackNode));
    tmp->type = SYMBOL;
    tmp->value.symbolValue = value;
    tmp->prev = s->top;
    s->top = tmp;
    s->size++;
}

Tree* stackPopTree(stack* s) {
    if (stackSize(s) == 0) {
        printf("Стек пуст!\n");
        return NULL;
    }
    stackNode* tmp = s->top;
    Tree* result = tmp->value.treeValue;
    s->top = s->top->prev;
    free(tmp);
    s->size--;
    return result;
}

Symbol stackPopSymbol(stack* s) {
    if (stackSize(s) == 0) {
        printf("Стек пуст!\n");
        Symbol emptySymbol;
        emptySymbol.type = symb_NONE;
        emptySymbol.data.c = '\0';
        return emptySymbol;
    }
    stackNode* tmp = s->top;
    Symbol result = tmp->value.symbolValue;
    s->top = s->top->prev;
    free(tmp);
    s->size--;
    return result;
}

void stackDestroy(stack* s) {
    while (!stackEmpty(s)) {
        stackNode* current = s->top;
        s->top = s->top->prev;
        free(current);
    }
    free(s);
}

Tree* stackTopTree(stack* s) {
    if (stackSize(s) == 0) {
        printf("Стек пуст!\n");
        return NULL;
    }
    return s->top->value.treeValue;
}

Symbol stackTopSymbol(stack* s) {
    if (stackSize(s) == 0) {
        printf("Стек пуст!\n");
        Symbol emptySymbol;
        emptySymbol.type = symb_NONE;
        emptySymbol.data.c = '\0';
        return emptySymbol;
    }
    return s->top->value.symbolValue;
}

void pushFront(node** head, Symbol data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = *head;
    newNode->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void pushBack(node** head, Symbol data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

void deleteBack(node* head) {
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

void deleteFront(node* head) {
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

void printList(node* head) {
    node* current = head;
    while (current != NULL) {
        printf("%c ", current->data.data.c); // Выводим символ из Symbol
        current = current->next;
    }
    printf("\n");
}

void destroyList(node* head) { // функция очистки списка
    node* current = head;
    while (current != NULL) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

int sizeList(node* head) {
    int count = 0;
    node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '*' || ch == '/' || ch == '^');
}

int getPriority(char ch) {
    if (ch == '*' || ch == '/') {
        return 2;
    } else if (ch == '+' || ch == '-') {
        return 1;
    } else if (ch == '^' || ch == '!' ){
        return 3;
    } else {
	return 0;
    }
}

OperatorAssociation opAssociation(char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/')
        return ASSOC_LEFT;
    else
        return ASSOC_RIGHT;
}
