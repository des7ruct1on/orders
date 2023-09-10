#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "tree.h"

void next_token(Symbol* symbol, char input[]) {
    static int index = 0;
    char c = input[index];
    static symbol_type prev = symb_NONE;
    if (c == '\0') {  // проверка на конец выражения
        symbol->type = symb_NONE;
        prev = symb_NONE;
        return;
    }

    if (isdigit(c) || c == '.') {
        symbol->type = symb_NUMBER;
        sscanf(&input[index], "%f", &symbol->data.number); // считываем float число
        while (isdigit(input[index]) || input[index] == '.') {
            index++;  // двигаемся дальше по выражению
        }
    } else if (is_operator(c)) {
        Operator tmp = char_to_op(c);
        symbol->type = symb_OP;
        symbol->data.op = tmp;
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

void parse_algorithm(char exp[], node** expression) {
    //создаем стек
    stack* s = malloc(sizeof(stack));
    init_stack(s);

    Symbol t;
    next_token(&t, exp);//считываем лексему

    while (t.type != symb_NONE) { // пока лексемы есть
        switch (t.type) {
            case symb_NONE://случай ошибок
                fprintf(stderr, "Ошибка! символ %c не распознан\n", t.data.c);
                return;

            case symb_OP://если оператор
            
                while(true) {
                    if (stack_empty(s)) {//если пусто
                        break;
                    }

                    Symbol top = stack_top_symbol(s);//берем со стека 

                    if (top.type != symb_OP) { //если достали не оператор
                        break;
                    }
                    //если лексема-оператор левоассоциативен и приоритет меньше либо равен оператору сверху или приоритет ниже когда правоассоциативен
                    if ((op_association(t.data.op) == ASSOC_LEFT && get_priority(t.data.op) <= get_priority(top.data.op)) ||
                        (op_association(t.data.op) == ASSOC_RIGHT && get_priority(t.data.op) < get_priority(top.data.op))) {
                        push_back(expression, top); //пушим верхуушку стека в выходную строку
                        stack_pop_symbol(s);//берем со стека символ
                    } else {
                        break;
                    }
                }
                stack_push_symbol(s, t);//кладем оператор на стек
                break;

            case symb_NUMBER:
                push_back(expression, t);//пушим в выходную строку
                break;
            case symb_VAR:
                push_back(expression, t);//пушим в выходную строку
                break;

            case symb_LEFT_BR:
                stack_push_symbol(s, t);//пушим в стек
                break;

            case symb_RIGHT_BR:
                while (!stack_empty(s) && stack_top_symbol(s).type != symb_LEFT_BR) {//пока не пуст и не дошли до левой скобки
                    push_back(expression, stack_pop_symbol(s));//выкладываем в выходную строку
                }

                if (stack_empty(s)) {//если пустота то потеряли скобку
                    fprintf(stderr, "Ошибка: пропущена скобка\n");
                    return;
                }

                stack_pop_symbol(s);//вытаскиваем лексему скобки
                break;
        }

        next_token(&t, exp);//считываем лексему
    }

    while (!stack_empty(s)) {//если лексемы кончились, но стек не пуст
        if (stack_top_symbol(s).type == symb_LEFT_BR) {//если лежит левая скобка на стеке
            fprintf(stderr, "Ошибка: пропущена скобка\n");
            return;
        }

        push_back(expression, stack_pop_symbol(s));//добавляем остатки в строку
    }

    stack_destroy(s);//очищаем стек
}

Tree* create_tree_arpihm(node* queue) {
    stack* s = malloc(sizeof(stack)); //создаем стек
    init_stack(s);
    for(node* current = queue; current != NULL; current = current->next) {//проходим по всему списку
        Symbol c = current->data;
        if (c.type != symb_OP) {// если не оператор то создаем узел и добавляем его в стек
            Tree* tmp = create_tree(c);
            stack_push_tree(s, tmp);
        } else if (c.type == symb_OP) {//если оператор, то берем два из стека и создаем узел с потомками, затем кладем обратно в стек
            Tree* right = stack_pop_tree(s);
            Tree* left = stack_pop_tree(s);
            Tree* op = create_tree(c);
            op->left = left;
            op->right = right;
            stack_push_tree(s, op);
        }
    }
    Tree* res = stack_pop_tree(s);//вытаскиваем дерево-результат
    stack_destroy(s);
    return res;
}

//функция копирования дерева

Tree* tree_cpy(Tree* t) {
    if (t == NULL) {
        return NULL;
    }

    Tree* tmp = malloc(sizeof(Tree));
    Symbol s= t->value;
    tmp->value = s;
    if (t->left != NULL) {
        tmp->left = tree_cpy(t->left);
    } else {
        tmp->left = NULL;
    }
    if (t->right != NULL) {
        tmp->right = tree_cpy(t->right);
    } else {
        tmp->right = NULL;
    }
    return tmp;
}
//функция преобразования
void task(Tree* node) {
    if (node == NULL) {
        return;
    }
    if (node->value.type == symb_OP && node->value.data.op == OP_POW) {
        //Tree* _left = node->left;
        Tree* _right = node->right;
        if (_right->value.type == symb_OP && _right->value.data.op == OP_PLUS) {
            Tree* _right_l = tree_cpy(node->right->left);
            Tree* _right_r = tree_cpy(node->right->right);
            Tree* tmp = tree_cpy(node);

            
            clear_tree(tmp->right->left);
            clear_tree(tmp->right->right);
            Tree* tmp2 = tree_cpy(node);
            clear_tree(tmp2->right->left);
            clear_tree(tmp2->right->right);
            free(tmp->right);
            free(tmp2->right);
            tmp->right = _right_l;
            tmp2->right = _right_r;
            
            clear_tree(node->left);
            clear_tree(node->right);
            node->value.data.op = OP_MULTIPLY;
            node->left = tmp;
            node->right = tmp2;
            task(node->left);
            task(node->right);

            
        }
    }
}





void tree_to_expresion(Tree* tree) { //обратный алгоритм дейкстры
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
                tree_to_expresion(tree->right);
            } else {
                bool add_parent_left = (tree->left->value.type == symb_OP && get_priority(tree->value.data.op) > get_priority(tree->left->value.data.op));
                bool add_parent_right = (tree->right->value.type == symb_OP && get_priority(tree->value.data.op) > get_priority(tree->right->value.data.op));

                if (tree->value.data.op == OP_DIVIDE && !add_parent_left && !add_parent_right) {
                    // В случае деления добавляем скобки только для нумератора и знаменателя, если они сами являются операторами
                    add_parent_left = (tree->left->value.type == symb_OP);
                    add_parent_right = (tree->right->value.type == symb_OP);
                }

                if (add_parent_left) {
                    printf("(");
                }
                tree_to_expresion(tree->left);
                if (add_parent_left) {
                    printf(")");
                }

                printf("%c", opp_to_char(tree->value.data.op));

                if (add_parent_right) {
                    printf("(");
                }
                tree_to_expresion(tree->right);
                if (add_parent_right) {
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
    init_stack(st);
    char exp[MAX_EXPRESSION_LENGTH];
    if (fgets(exp, MAX_EXPRESSION_LENGTH, file) == NULL) {
        printf("Не удалось прочитать данные из файла.\n");
        fclose(file);
        return 1;
    }
    fclose(file);
    node* expression = NULL;
    parse_algorithm(exp, &expression);
    Tree* tree = create_tree_arpihm(expression);
    destroy_list(expression);
    printf("\nИсходное дерево выражений:\n");
    print_tree(tree, 0);
    task(tree);
    printf("\nПреобразованное дерево выражений:\n");
    print_tree(tree, 0);
    tree_to_expresion(tree);
    clear_tree(tree);
    stack_destroy(st);
    return 0;
}