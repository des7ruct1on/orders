#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void print_menu() {
    printf("1. Добавить вершину\n");
    printf("2. Удалить вершину\n");
    printf("3. Распечатать дерево\n");
    printf("4. Определить число вершин двоичного дерева, степень которых совпадает со значением элемента\n");
    printf("5. Закончить работу программы\n");
}

int count_nodes_with_matching_degree(Tree* root) {
    if (root == NULL)
        return 0;
    
    int count = 0;
    
    if (root->left != NULL && root->right != NULL) {
        if (root->value == 2) // Проверяем, совпадает ли степень с значением
            count++;
    }
    
    count += count_nodes_with_matching_degree(root->left); // Рекурсивный вызов для левого поддерева
    count += count_nodes_with_matching_degree(root->right); // Рекурсивный вызов для правого поддерева
    
    return count;
}

int main() {
    Tree* root = NULL;
    int value;
    int choice = 0;

    while (1) {
        print_menu();

        printf("Введите номер команды: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение элемента: ");
        		scanf("%d", &value);
       	 		root = insert(root, value);
                break;
            case 2:
                printf("Введите значение элемента для удаления: ");
        		scanf("%d", &value);
        		root = remove_Tree(root, value);
                break;
            case 3:
                printf("\nБинарное дерево: ");
    			printf("\n----------------------------------------\n");
    			print_tree(root, 1);
    			printf("\n----------------------------------------\n");
                break;
            case 4:
                printf("Число вершин с совпадающей степенью: %d\n", count_nodes_with_matching_degree(root));
                break;
            case 5:
                free_tree(root);
    			return 0;
                break;
            default:
                printf("Ошибка: неправильный ввод. Попробуйте еще раз.\n");
                break;
        }
    }
    free_tree(root);
    
    return 0;
}