#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void print_menu() {
    printf("1. Добавить вершину\n");
    printf("2. Удалить вершину\n");
    printf("3. Распечатать дерево\n");
    printf("4. Определить количество нетерминальных вершин\n");
    printf("5. Закончить работу программы\n");
}

int count_non_terminal_nodes(Tree* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 0; // Вершина является терминальной, не считаем её
    }
    int left_count = count_non_terminal_nodes(root->left);
    int right_count = count_non_terminal_nodes(root->right);
    return left_count + right_count + 1; // Учитываем текущую вершину
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
                printf("Количество вершин: %d\n", count_non_terminal_nodes(root));
                break;
            case 5:
                free_tree(root);
    			return 0;
                break;
            default:
                printf("Ошибка! Не существует такого действия\n");
                break;
        }
    }
    free_tree(root);
    
    return 0;
}