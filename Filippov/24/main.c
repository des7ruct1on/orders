#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "tree.h"

void nextToken(Symbol* symbol, char input[]) {
    static int index = 0;
    char c = input[index];
    static SymbolType prev = symb_NONE;
    if (c == '\0') {  // проверка на конец выражения
        symbol->type = symb_NONE;
        prev = symb_NONE;
        return;
    }

    if (isdigit(c)) {
        symbol->type = symb_NUMBER;
        symbol->data.number = c - '0';
        index++;  // двигаемся дальше по выражению

        // Считываем все цифры числа
        while (isdigit(input[index])) {
            symbol->data.number = symbol->data.number * 10 + (input[index] - '0');
            index++;
        }
    } else if (isOperator(c)) {
        symbol->type = symb_OP;
        symbol->data.op = c;
        index++;  // двигаемся дальше по выражению
    } else if (isalpha(c)) {
        symbol->type = symb_VAR;
        symbol->data.c = c;
        index++;  // двигаемся дальше по выражению
    } else if (c == '(') {
        symbol->type = symb_LEFT_BR;
        symbol->data.c = c;
        index++;  // двигаемся дальше по выражению
    } else if (c == ')') {
        symbol->type = symb_RIGHT_BR;
        symbol->data.c = c;
        index++;  // двигаемся дальше по выражению
    } else if (c == '-') {
        symbol->type = symb_OP;
        if (prev == symb_OP || prev == symb_NONE) {
            symbol->data.op = OP_UNARY_MINUS;
        } else {
            symbol->data.op = OP_MINUS;
        }
        index++;  // двигаемся дальше по выражению
    } else {
        symbol->type = symb_NONE;
        index++;  // двигаемся дальше по выражению
    }
    prev = symbol->type;
}

void deikstraAlgorithm(char exp[], node** expression) {
    //создаем стек
    stack* s = malloc(sizeof(stack));
    initStack(s);

    Symbol t;
    nextToken(&t, exp);//считываем лексему

    while (t.type != symb_NONE) { // пока лексемы есть
        switch (t.type) {
            case symb_NONE://случай ошибок
                fprintf(stderr, "Ошибка! символ %c не распознан\n", t.data.c);
                return;

            case symb_OP://если оператор
                while(true) {
                    if (stackEmpty(s)) {//если пусто
                        break;
                    }

                    Symbol top = stackTopSymbol(s);//берем со стека 

                    if (top.type != symb_OP) { //если достали не оператор
                        break;
                    }
                    //если лексема-оператор левоассоциативен и приоритет меньше либо равен оператору сверху или приоритет ниже когда правоассоциативен
                    if ((opAssociation(t.data.op) == ASSOC_LEFT && getPriority(t.data.op) <= getPriority(top.data.op)) ||
                        (opAssociation(t.data.op) == ASSOC_RIGHT && getPriority(t.data.op) < getPriority(top.data.op))) {
                        pushBack(expression, top); //пушим верхуушку стека в выходную строку
                        stackPopSymbol(s);//берем со стека символ
                    } else {
                        break;
                    }
                }
                stackPushSymbol(s, t);//кладем оператор на стек
                break;

            case symb_NUMBER:
            case symb_VAR:
                pushBack(expression, t);//пушим в выходную строку
                break;

            case symb_LEFT_BR:
                stackPushSymbol(s, t);//пушим в стек
                break;

            case symb_RIGHT_BR:
                while (!stackEmpty(s) && stackTopSymbol(s).type != symb_LEFT_BR) {//пока не пуст и не дошли до левой скобки
                    pushBack(expression, stackPopSymbol(s));//выкладываем в выходную строку
                }

                if (stackEmpty(s)) {//если пустота то потеряли скобку
                    fprintf(stderr, "Ошибка: пропущена скобка\n");
                    return;
                }

                stackPopSymbol(s);//вытаскиваем лексему скобки
                break;
        }

        nextToken(&t, exp);//считываем лексему
    }

    while (!stackEmpty(s)) {//если лексемы кончились, но стек не пуст
        if (stackTopSymbol(s).type == symb_LEFT_BR) {//если лежит левая скобка на стеке
            fprintf(stderr, "Ошибка: пропущена скобка\n");
            return;
        }

        pushBack(expression, stackPopSymbol(s));//добавляем остатки в строку
    }

    stackDestroy(s);//очищаем стек
}

Tree* createAriphmTree(node* queue) {
    stack* s = malloc(sizeof(stack)); //создаем стек
    initStack(s);
    for(node* current = queue; current != NULL; current = current->next) {//проходим по всему списку
        Symbol c = current->data;
        if (c.type != symb_OP) {// если не оператор то создаем узел и добавляем его в стек
            Tree* tmp = createTree(c);
            stackPushTree(s, tmp);
        } else if (c.type == symb_OP) {//если оператор, то берем два из стека и создаем узел с потомками, затем кладем обратно в стек
            Tree* right = stackPopTree(s);
            Tree* left = stackPopTree(s);
            Tree* op = createTree(c);
            op->left = left;
            op->right = right;
            stackPushTree(s, op);
        }
    }
    Tree* res = stackPopTree(s);//вытаскиваем дерево-результат
    stackDestroy(s);
    return res;
}

Tree* treeCopy(Tree* t) { //функция копирования дерева
    if (t == NULL) {
        return NULL;
    }

    Tree* tmp = malloc(sizeof(Tree));
    Symbol s= t->value;
    tmp->value = s;
    if (t->left != NULL) {
        tmp->left = treeCopy(t->left);
    } else {
        tmp->left = NULL;
    }
    if (t->right != NULL) {
        tmp->right = treeCopy(t->right);
    } else {
        tmp->right = NULL;
    }
    return tmp;
}

void task(Tree* node) {//функция преобразования
    if (node == NULL) {
        return;
    }
    task(node->left);
    task(node->right);
    if (node->value.type == symb_OP && node->value.data.op == OP_MULTIPLY) {
        Tree* leftTree = node->left;
        Tree* rightTree = node->right;
        if (leftTree->value.data.op == OP_POW && rightTree->value.data.op != OP_POW) {
            if (rightTree->value.data.c == leftTree->left->value.data.c || rightTree->value.data.number == leftTree->left->value.data.number) {
                node->value.data.op = OP_POW;
                leftTree->value.data.op = OP_PLUS;
                leftTree->left->value.type = symb_NUMBER;
                leftTree->left->value.data.number = 1;

                node->right = leftTree;
                node->left = rightTree;
            }
        } else if (rightTree->value.data.op == OP_POW && leftTree->value.data.op != OP_POW) {
            if (leftTree->value.data.c == rightTree->left->value.data.c || leftTree->value.data.number == rightTree->left->value.data.number) {
                node->value.data.op = OP_POW;
                rightTree->value.data.op = OP_PLUS;
                rightTree->left->value.type = symb_NUMBER;
                rightTree->left->value.data.number = 1;
            }
        } else {
            return;
        }
    }
}
 


void treeToExpresion(Tree* tree) { //обратный алгоритм дейкстры
    switch (tree->value.type) {
        case symb_NUMBER:
            printf("%.2lf", tree->value.data.number);
            break;
        case symb_VAR:
            printf("%c", tree->value.data.c);
            break;
        case symb_OP:
            if (tree->value.data.op == OP_UNARY_MINUS) {
                printf("-");
                treeToExpresion(tree->right);
            } else {
                bool addParenthesesLeft = (tree->left->value.type == symb_OP && getPriority(tree->value.data.op) > getPriority(tree->left->value.data.op));
                bool addParenthesesRight = (tree->right->value.type == symb_OP && getPriority(tree->value.data.op) > getPriority(tree->right->value.data.op));

                if (tree->value.data.op == OP_DIVIDE && !addParenthesesLeft && !addParenthesesRight) {
                    // В случае деления добавляем скобки только для нумератора и знаменателя, если они сами являются операторами
                    addParenthesesLeft = (tree->left->value.type == symb_OP);
                    addParenthesesRight = (tree->right->value.type == symb_OP);
                }

                if (addParenthesesLeft) {
                    printf("(");
                }
                treeToExpresion(tree->left);
                if (addParenthesesLeft) {
                    printf(")");
                }

                printf("%c", oppToChar(tree->value.data.op));

                if (addParenthesesRight) {
                    printf("(");
                }
                treeToExpresion(tree->right);
                if (addParenthesesRight) {
                    printf(")");
                }
            }
            break;
        default:
            fprintf(stderr, "Ошибка, такого символа нет");
            return;
    }
}



int main(int argc, char const* argv[]) {
    if (argc != 2) {
        printf("Используйте: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }
    stack* st = malloc(sizeof(stack));
    initStack(st);
    char exp[MAX_EXPRESSION_LENGTH];
    if (fgets(exp, MAX_EXPRESSION_LENGTH, file) == NULL) {
        printf("Не удалось прочитать данные из файла.\n");
        fclose(file);
        return 1;
    }
    fclose(file);
    node* expression = NULL;
    deikstraAlgorithm(exp, &expression);
    Tree* tree = createAriphmTree(expression);
    destroyList(expression);
    printf("\nИсходное дерево выражений:\n");
    printTree(tree, 0);
    task(tree);
    printf("\nПреобразованное дерево выражений:\n");
    printTree(tree, 0);
    treeToExpresion(tree);
    clearTree(tree);
    stackDestroy(st);
    return 0;
}