#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void printMenu() {
    printf("1. Добавить вершину\n");
    printf("2. Удалить вершину\n");
    printf("3. Распечатать дерево\n");
    printf("4. Определить значение нетерминальной вершины с максимальной глубиной\n");
    printf("5. Закончить работу программы\n");
}

int maxDepth(Tree* root) { //функция определения максимальной глубины
    if (root == NULL)
        return 0;

    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);

    return (leftDepth > rightDepth) ? leftDepth + 1 : rightDepth + 1;
}

void printNonTerminalNodesAtMaxDepth(Tree* root, int currentDepth, int maxDepth) {
    if (root == NULL) { //если дерево пустое
        return;
    }
    //printf("|%d|\n", currentDepth);
    if (currentDepth == maxDepth - 1 && (root->left != NULL || root->right != NULL)) { //проверка на нетерминальность вершины и ее нахождение на опр уровне
        printf("%d ", root->value);
        return;
    }

    printNonTerminalNodesAtMaxDepth(root->left, currentDepth + 1, maxDepth); //рекурсивный вызов от двух поддеревьев
    printNonTerminalNodesAtMaxDepth(root->right, currentDepth + 1, maxDepth);
}


int main() {
    Tree* tree = NULL; //изначальное дерево
    int value; //значение вершин
    int choice = 0;
    int depth = 0; //значение глубины
    while (1) {
        printMenu();
        printf("Введите номер действия: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение элемента: ");
        		scanf("%d", &value);
       	 		tree = insertTree(tree, value);
                break;
            case 2:
                printf("Введите значение элемента для удаления: ");
        		scanf("%d", &value);
        		tree = removeTree(tree, value);
                break;
            case 3:
                printf("\nБинарное дерево: ");
    			printf("\n----------------------------------------\n");
    			printTree(tree, 1);
    			printf("\n----------------------------------------\n");
                break;
            case 4:
                depth = maxDepth(tree);
                printf("(%d)\n", depth);
                printNonTerminalNodesAtMaxDepth(tree, 1, depth);
                break;
            case 5:
                freeTree(tree);
    			return 0;
                break;
            default:
                printf("Ошибка! Не существует такого действия\n");
                break;
        }
    }
    freeTree(tree);
    
    return 0;
}