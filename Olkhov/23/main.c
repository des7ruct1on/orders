#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

// Вывода меню
void print_menu() {
    printf("1. Добавить вершину\n");
    printf("2. Удалить вершину\n");
    printf("3. Распечатать дерево\n");
    printf("4. Проверить дерево на линейный список\n");
    printf("5. Закончить работу программы\n");
}

void task(Tree* tree, bool* result) {
    if (tree == NULL) {
        return;
    }
    if (tree->left != NULL && tree->right != NULL) {
        *result = false;
        return;
    }
    if (tree->left != NULL && tree->right == NULL) {
        task(tree->left, result);
    } else if (tree->left == NULL && tree->right != NULL) {
        task(tree->right, result);
    }
}

int main() {
    Tree* root = NULL; //изначально нулевой указатель
    int value; // переменная для значения вершины
    int choice = 0;
    bool result = true;
    while (true) {
        print_menu();

        printf("Введите номер команды: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение элемента: ");
        		scanf("%d", &value);
       	 		root = add_node(root, value);
                break;
            case 2:
                printf("Введите значение элемента для удаления: ");
        		scanf("%d", &value);
        		root = erase_node(root, value);
                break;
            case 3:
                printf("\nБинарное дерево: ");
    			printf("\n----------------------------------------\n");
    			print_tree(root, 1);
    			printf("\n----------------------------------------\n");
                break;
            case 4:
                task(root, &result);
                if (result) {
                    printf("Дерево является линейным списком\n");
                } else {
                    printf("Дерево не является линейным списком\n");
                }
                break;
            case 5:
                destructor_tree(root);
    			return 0;
                break;
            default:
                printf("Ошибка! Несуществующее действие\n");
                break;
        }
    }
    destructor_tree(root);
    
    return 0;
}