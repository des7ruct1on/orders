#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void print_menu() {
    printf("|=============================================================|\n");
    printf("| 1. Добавить вершину                                         |\n");
    printf("| 2. Удалить вершину                                          |\n");
    printf("| 3. Распечатать дерево                                       |\n");
    printf("| 4. Определить уровень дерева с наибольшим количеством вершин|\n");
    printf("| 5. Закончить работу программы                               |\n");
    printf("|=============================================================|\n");
}

void dfs(Tree* tree, int level, int** levels_ptr, int* size) {
    if (tree == NULL) {
        return;
    }
    if (level >= *size) {
        *size = level + 1;
        *levels_ptr = realloc(*levels_ptr, *size * sizeof(int));
        (*levels_ptr)[level] = 0;
    }
    (*levels_ptr)[level]++;
    dfs(tree->left, level + 1, levels_ptr, size);
    dfs(tree->right, level + 1, levels_ptr, size);
}

int max_level_with_max_nodes(Tree* tree) {
    int max_sum = 0;
    int max_level = 0;
    int size = 0;
    int* levels = NULL;
    dfs(tree, 0, &levels, &size);
    for (int i = 0; i < size; i++) {
        if (levels[i] > max_sum) {
            max_sum = levels[i];
            max_level = i;
        }
    }
    free(levels);
    return max_level;
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
                printf("Уровень: %d\n", max_level_with_max_nodes(root));
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