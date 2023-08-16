#include "tree.h"

Tree* createTree(int value) {
    Tree* new_Tree = (Tree*)malloc(sizeof(Tree));
    new_Tree->value = value;
    new_Tree->left = NULL;
    new_Tree->right = NULL;
    return new_Tree;
}//функция создания нового узла

Tree* insertTree(Tree* root, int value) {
	if(root == NULL) {
		return createTree(value);
    }
    if(value < root->value) { // если значение меньше узла, то идем в левое поддерево
    	root->left = insertTree(root->left, value);
    } else if(value > root->value) { // наоборот идем в правое поддерево
    	root->right = insertTree(root->right, value);
    }
    return root;
}

Tree* findMinimum(Tree* root) {
    while (root->left != NULL) { // движемся по самым левым вершинам пока не достигнем последней
        root = root->left;
    }
    return root;
}

Tree* removeTree(Tree* root, int value) {
    if (root == NULL) { // дерево пустое
        return root;
    }
    if (value < root->value) { //поиск удаляемого элемента
        root->left = removeTree(root->left, value);
    } else if (value > root->value) {
        root->right = removeTree(root->right, value);
    } else { // найден
        if (root->left == NULL) { //когда у элемента есть только правое поддерево
            Tree* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) { //когда у элемента есть только левое поддерево
            Tree* temp = root->left;
            free(root);
            return temp;
        }
        //случай если есть оба потомков
        Tree* temp = findMinimum(root->right); //находим наименьший элемент в правом поддереве и заменяем, чтоб не нарушить конструкцию
        root->value = temp->value;
        root->right = removeTree(root->right, temp->value);
    }
    return root;
}


void printTree(Tree* root, int n) {//вывод дерева
    if (root == NULL) {
        return;
    }
    printTree(root->right, n + 1);
    for (int i = 0; i < n; i++) {
        printf("\t");
    }
    printf("%d\n", root->value);
    printTree(root->left, n + 1);
}

void freeTree(Tree* root) {
    if(root == NULL) { // если пустое дерево
        return;
    }
    freeTree(root->left); //рекурсивный вызов у поддеревьев
    freeTree(root->right);
    free(root); 
}