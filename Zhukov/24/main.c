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

void dejikstra_algorithm(char exp[], node** expression) {
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

Tree* tree_cpy(Tree* t) { //функция копирования дерева
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

// функция сравнения чисел
bool are_symbol_data_numbers_equal(symbol_data data1, symbol_data data2) {
    return data1.number == data2.number;
}

// функция сравнения переменных
bool are_symbol_data_vars_equal(symbol_data data1, symbol_data data2) {
    return data1.c == data2.c;
}

// функция сравнения операторов
bool are_symbol_data_operators_equal(symbol_data data1, symbol_data data2) {
    return data1.op == data2.op;
}

bool are_trees_equal(Tree* tree1, Tree* tree2) {
    if (tree1 == NULL && tree2 == NULL) {
        // оба пустые
        return true;
    }

    if (tree1 == NULL || tree2 == NULL) {
        // одно пустое, другое нет
        return false;
    }

    // Проверяем каждый символ
    if (tree1->value.type == symb_NUMBER ) {
        if (tree2->value.type != tree1->value.type || !are_symbol_data_numbers_equal(tree1->value.data, tree2->value.data)) {
            return false;
        }
    } else if (tree1->value.type == symb_VAR) {
        if (tree2->value.type != tree1->value.type || !are_symbol_data_vars_equal(tree1->value.data, tree2->value.data)) {
            return false;
        }
    } else if (tree1->value.type == symb_OP) {
        if (tree2->value.type != tree1->value.type || !are_symbol_data_operators_equal(tree1->value.data, tree2->value.data)) {
            return false;
        }
    } else {
        // неизвестный тип
        return false;
    }

    // рекурсия для других под-деревьев
    bool left_equal = are_trees_equal(tree1->left, tree2->left);
    bool right_equal = are_trees_equal(tree1->right, tree2->right);

    // если равны, то выводим равенство
    return left_equal && right_equal;
}

void remove_ones(Tree** node) {
    if (!(*node)) return;
    const double epsilon = 1e-8;
    remove_ones(&(*node)->left);
    remove_ones(&(*node)->right);
    if ((*node)->value.type == symb_OP && (*node)->value.data.op == OP_DIVIDE) {
        Tree* left = (*node)->left;
        Tree* right = (*node)->right;
        //сравниваем вещественные числа при помощи эпсилона
        if (right->value.type == symb_NUMBER) {
            if (fabs(right->value.data.number - 1.0) < epsilon) {
                free(right);
                right = NULL;
                free(*node);
                *node = left;
            }
        } else if (right->value.data.op == OP_MULTIPLY) {
            Tree* cur = right;
            Tree* next = right->left;
            while (next->value.data.op == OP_MULTIPLY) {
                if (fabs(cur->right->value.data.number - 1.0) < epsilon) {
                    free(cur->right);
                    cur->right = NULL;
                    Tree* new_next = next->left;
                    free(next);
                    cur->left = new_next;
                    next = new_next;
                }
                cur = cur->left;
                next = next->left;
            }
            if (fabs(next->value.data.number - 1.0) < epsilon) {
                free(next);
                cur->value.data = cur->right->value.data;
                cur->value.type = cur->right->value.type;
                free(cur->right);
            } else if (fabs(cur->right->value.data.number - 1.0) < epsilon) {
                free(cur->right);
                cur->value.data = next->value.data;
                cur->value.type = next->value.type;
                free(next);
            }
            remove_ones(node);
        }
    }
}


void task(Tree* node) {//функция преобразования
    if (node == NULL) {
        return;
    }
    task(node->left);
    task(node->right);
    if (node->value.type == symb_OP && node->value.data.op == OP_DIVIDE) {
        Tree* left_tree = node->left;
        Tree* right_tree = node->right;
        if (left_tree->value.type == symb_OP && left_tree->value.data.op == OP_MULTIPLY && right_tree->value.data.op != OP_MULTIPLY) {
            Tree* current = left_tree;
            Tree* check;
            bool found = false;
            Tree* new_next;
            if (current->left->value.data.op != OP_MULTIPLY) {
                found = are_trees_equal(current->left, right_tree);
                if (found) {
                    right_tree->value.type = symb_NUMBER;
                    right_tree->value.data.number = 1.0;
                    new_next = current->right;
                    clear_tree(current->left);
                    free(left_tree);
                    node->left = new_next;
                } else {
                    found = are_trees_equal(current->right, right_tree);
                    if (found) {
                        right_tree->value.type = symb_NUMBER;
                        right_tree->value.data.number = 1.0;
                        new_next = current->left;
                        clear_tree(current->right);
                        free(left_tree);
                        node->left = new_next;
                    }
                }
            } else {
                Tree* cur_next = current->left;
                found = are_trees_equal(current->right, right_tree);
                if (found) {
                    right_tree->value.type = symb_NUMBER;
                    right_tree->value.data.number = 1.0;
                    free(current->right);
                    node->left = cur_next;
                    free(current);
                }
                while (cur_next->value.data.op == OP_MULTIPLY) {
                    check = cur_next->right;
                    found = are_trees_equal(check, right_tree);
                    if (found) {
                        right_tree->value.type = symb_NUMBER;
                        right_tree->value.data.number = 1.0;
                        new_next = cur_next->left;
                        free(check);
                        free(cur_next);
                        current->left = new_next;
                        break;
                    }
                    current = current->left;
                    cur_next = cur_next->left;
                }
                if (!found) {
                    found = are_trees_equal(cur_next, right_tree);
                    if (found) {
                        right_tree->value.type = symb_NUMBER;
                        right_tree->value.data.number = 1.0;
                        clear_tree(current->left);
                        current->value.data = current->right->value.data;
                        current->value.type = current->right->value.type;
                        clear_tree(current->right);
                        current->left = NULL;
                        current->right = NULL;
                    } else {
                        found = are_trees_equal(current->right, right_tree);
                        if (found) {
                            right_tree->value.type = symb_NUMBER;
                            right_tree->value.data.number = 1.0;
                            clear_tree(current->right);
                            current->value.data = current->left->value.data;
                            current->value.type = current->left->value.type;
                            clear_tree(current->left);
                            current->left = NULL;
                            current->right = NULL;
                        }
                    }
                }

            }
        } else if (left_tree->value.data.op != OP_MULTIPLY && right_tree->value.type == symb_OP && right_tree->value.data.op == OP_MULTIPLY) {
            Tree* current = right_tree;
            Tree* check;
            bool found = false;
            Tree* new_next;
            if (current->left->value.data.op != OP_MULTIPLY) {
                found = are_trees_equal(current->left, left_tree);
                if (found) {
                    left_tree->value.type = symb_NUMBER;
                    left_tree->value.data.number = 1.0;
                    new_next = current->right;
                    clear_tree(current->left);
                    free(right_tree);
                    node->right = new_next;
                } else {
                    found = are_trees_equal(current->right, left_tree);
                    if (found) {
                        left_tree->value.type = symb_NUMBER;
                        left_tree->value.data.number = 1.0;
                        new_next = current->left;
                        clear_tree(current->right);
                        free(right_tree);
                        node->right = new_next;
                    }
                }
            } else {
                Tree* cur_next = current->left;
                found = are_trees_equal(current->right, left_tree);
                if (found) {
                    left_tree->value.type = symb_NUMBER;
                    left_tree->value.data.number = 1.0;
                    free(current->right);
                    node->right = cur_next;
                    free(current);
                }
                while (cur_next->value.data.op == OP_MULTIPLY) {
                    check = cur_next->right;
                    found = are_trees_equal(check, left_tree);
                    if (found) {
                        left_tree->value.type = symb_NUMBER;
                        left_tree->value.data.number = 1.0;
                        new_next = cur_next->left;
                        free(check);
                        free(cur_next);
                        current->left = new_next;
                        break;
                    }
                    current = current->left;
                    cur_next = cur_next->left;
                }
                if (!found) {
                    found = are_trees_equal(cur_next, left_tree);
                    if (found) {
                        left_tree->value.type = symb_NUMBER;
                        left_tree->value.data.number = 1.0;
                        clear_tree(current->left);
                        current->value.data = current->right->value.data;
                        current->value.type = current->right->value.type;
                        clear_tree(current->right);
                        current->left = NULL;
                        current->right = NULL;
                    } else {
                        found = are_trees_equal(current->right, left_tree);
                        if (found) {
                            left_tree->value.type = symb_NUMBER;
                            left_tree->value.data.number = 1.0;
                            clear_tree(current->right);
                            current->value.data = current->left->value.data;
                            current->value.type = current->left->value.type;
                            clear_tree(current->left);
                            current->left = NULL;
                            current->right = NULL;
                        }
                    }
                }

            }
        } else if (left_tree->value.type == symb_OP && left_tree->value.data.op == OP_MULTIPLY && right_tree->value.type == symb_OP && right_tree->value.data.op == OP_MULTIPLY ){
            Tree* check_compare = right_tree->right;
            Tree* current = right_tree;
            Tree* cur_next = current->left;
            Tree* new_tmp;
            Tree* tmp_check;
            check_compare = current->right;
            new_tmp = tree_cpy(node);
            clear_tree(new_tmp->right);
            tmp_check = tree_cpy(check_compare);
            new_tmp->right = tmp_check;
            task(new_tmp);
            clear_tree(left_tree);
            node->left = new_tmp->left;
            check_compare->value.type = new_tmp->right->value.type;
            check_compare->value.data = new_tmp->right->value.data;
            clear_tree(new_tmp->right);
            free(new_tmp);
            new_tmp = NULL;
            cur_next = current->left;
            while (cur_next->left->value.data.op == OP_MULTIPLY) {
                left_tree = node->left;
                check_compare = cur_next->right;
                new_tmp = tree_cpy(node);
                clear_tree(new_tmp->right);
                tmp_check = tree_cpy(check_compare);
                new_tmp->right = tmp_check;
                print_tree(new_tmp, 0);
                task(new_tmp);
                clear_tree(left_tree);
                node->left = new_tmp->left;
                check_compare->value.type = new_tmp->right->value.type;
                check_compare->value.data = new_tmp->right->value.data;
                clear_tree(new_tmp->right);
                free(new_tmp);
                new_tmp = NULL;
                current = current->left;
                cur_next = cur_next->left;
            }
            if (cur_next->left->value.data.op != OP_MULTIPLY) {
                check_compare = cur_next->right;
                new_tmp = tree_cpy(node);
                clear_tree(new_tmp->right);
                tmp_check = tree_cpy(check_compare);
                new_tmp->right = tmp_check;
                task(new_tmp);
                left_tree = node->left;
                clear_tree(left_tree);
                node->left = new_tmp->left;
                check_compare->value.type = new_tmp->right->value.type;
                check_compare->value.data = new_tmp->right->value.data;
                
                clear_tree(new_tmp->right);
                free(new_tmp);
                new_tmp = NULL;
                check_compare = cur_next->left;
                new_tmp = tree_cpy(node);
                clear_tree(new_tmp->right);
                tmp_check = tree_cpy(check_compare);
                new_tmp->right = tmp_check;
                task(new_tmp);
                left_tree = node->left;
                clear_tree(left_tree);
                node->left = new_tmp->left;
                check_compare->value.type = new_tmp->right->value.type;
                check_compare->value.data = new_tmp->right->value.data;
                clear_tree(new_tmp->right);
                free(new_tmp);
                new_tmp = NULL;
            }
            task(node);
            //remove_ones(&node); // пробовал удалять единицы из дерева, но где-то есть косяк(по варианту этого не требуется(это уже другой вариант лабы))

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
    stack* Stack = malloc(sizeof(stack));
    init_stack(Stack);
    char exp[MAX_EXPRESSION_LENGTH];
    if (fgets(exp, MAX_EXPRESSION_LENGTH, file) == NULL) {
        printf("Не удалось прочитать данные из файла.\n");
        fclose(file);
        return 1;
    }
    fclose(file);
    node* expression = NULL;
    dejikstra_algorithm(exp, &expression);
    Tree* tree = create_tree_arpihm(expression);
    destroy_list(expression);
    printf("\nИсходное дерево выражений:\n");
    print_tree(tree, 0);
    task(tree);
    print_tree(tree, 0);
    //remove_ones(&tree);
    printf("\nПреобразованное дерево выражений:\n");
    print_tree(tree, 0);
    tree_to_expresion(tree);
    //clear_tree(tree);
    stack_destroy(Stack);
    return 0;
}