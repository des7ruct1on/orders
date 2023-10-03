#ifndef tree_h
#define tree_h
#include <stdlib.h>

typedef struct Tree {
    int value;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* create_Tree(int value);
Tree* add_node(Tree* root, int value);
Tree* erase_node(Tree* root, int key);
Tree* get_minimum(Tree* root);
void print_tree(Tree* root, int n);
void destructor_tree(Tree* root);
#endif