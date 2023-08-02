#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

// Вывода меню
void print_menu() {
    printf("1. Добавить вершину\n");
    printf("2. Удалить вершину\n");
    printf("3. Распечатать дерево\n");
    printf("4. Ширину дерева\n");
    printf("5. Закончить работу программы\n");
}

// Функция для нахождения максимального значения
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Функция для нахождения высоты дерева
int get_height(Tree* root) {
    if (root == NULL) {
        return 0;
    }
    int left_height = get_height(root->left);
    int right_height = get_height(root->right);
    return 1 + max(left_height, right_height);
}

// Функция для заполнения динамического массива
void fill_level_array(Tree* root, int** level_array, int level) {
    if (root == NULL) {
        return;
    }
    (*level_array)[level]++;
    fill_level_array(root->left, level_array, level + 1);
    fill_level_array(root->right, level_array, level + 1);
}
// Функция для нахождения ширины дерева
int find_tree_width(Tree* root) {
    if (root == NULL) {
        return 0;
    }

    int height = get_height(root);
    int* level_array = (int*)calloc(height, sizeof(int));

    fill_level_array(root, &level_array, 0);

    int max_width = level_array[0];
    for (int i = 1; i < height; i++) {
        max_width = max(max_width, level_array[i]);
    }

    free(level_array);
    return max_width;
}

int main() {
    Tree* root = NULL;
    int value;
    int choice = 0;

    while (true) {
        print_menu();

        printf("Введите номер команды: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение элемента: ");
        		scanf("%d", &value);
       	 		root = insert_tree(root, value);
                break;
            case 2:
                printf("Введите значение элемента для удаления: ");
        		scanf("%d", &value);
        		root = erase_tree(root, value);
                break;
            case 3:
                printf("\nБинарное дерево: ");
    			printf("\n----------------------------------------\n");
    			print_tree(root, 1);
    			printf("\n----------------------------------------\n");
                break;
            case 4:
                printf("Ширина дерева: %d\n", find_tree_width(root));
                break;
            case 5:
                free_tree(root);
    			return 0;
                break;
            default:
                printf("Ошибка! Несуществующее действие\n");
                break;
        }
    }
    free_tree(root);
    
    return 0;
}