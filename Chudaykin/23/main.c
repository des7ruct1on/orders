#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

// Вывода меню
void print_menu() {
    printf("1. Добавить вершину\n");
    printf("2. Удалить вершину\n");
    printf("3. Распечатать дерево\n");
    printf("4. Количество вершин\n");
    printf("5. Закончить работу программы\n");
}

// Функция для нахождения количества вершин дерева
int get_num_edges(Tree* root) {
    if (root == NULL) {
        return 0;
    }

    int left_count = get_num_edges(root->left);
    int right_count = get_num_edges(root->right);

    return left_count + right_count + 1;
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
                printf("Количество вершин дерева: %d\n", get_num_edges(root));
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