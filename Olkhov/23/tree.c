#include "tree.h"
#include <stdio.h>

Tree* create_Tree(int value) {
    Tree* new_Tree = (Tree*)malloc(sizeof(Tree)); // выделяем память под вершину
    new_Tree->value = value;
    new_Tree->left = NULL;
    new_Tree->right = NULL;
    return new_Tree;
}

//функция вставки новой вершины в дерево если элемент меньше корневого - влево, если больше - вправо.
Tree* add_node(Tree* root, int value) {
	if(root == NULL) {
		return create_Tree(value);
    }
    if(value < root->value) {
    	root->left = add_node(root->left, value);
    } else if(value > root->value) {
    	root->right = add_node(root->right, value);
    }
    return root;
}

Tree* get_minimum(Tree* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Tree* erase_node(Tree* root, int value) {
    if (root == NULL) { // дерево пустое
        return root;
    }
    if (value < root->value) {
        root->left = erase_node(root->left, value);
    } else if (value > root->value) {
        root->right = erase_node(root->right, value);
    } else { // нашли удаляемый элемент
        if (root->left == NULL) { //когда удаляемый элемент имеет только правого потомка
            Tree* tmp = root->right;
            free(root);
            return tmp;
        } else if (root->right == NULL) { //когда удаляемый элемент имеет только левого потомка
            Tree* tmp = root->left;
            free(root);
            return tmp;
        }
        //если не сработали два условия выше
        Tree* tmp = get_minimum(root->right); //находим наименьший элемент в правом поддереве
        root->value = tmp->value;
        root->right = erase_node(root->right, tmp->value);
    }
    return root;
}


void print_tree(Tree* root, int n) {//форматированный вывод дерева
    if (root == NULL) {
        return;
    }
    print_tree(root->right, n + 1);
    for (int i = 0; i < n; i++) {
        printf("\t");
    }
    printf("%d\n", root->value);
    print_tree(root->left, n + 1);
}

void destructor_tree(Tree* root) {
    if(root == NULL) {
        return;
    }
    destructor_tree(root->left);
    destructor_tree(root->right);
    free(root);
}