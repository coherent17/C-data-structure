#ifndef _BST_H_
#define _BST_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int key;
    struct _node *left;
    struct _node *right;
    struct _node *parent;
} node;

node *createNode(int key);
void BST_insert(node **rootptr, node *z);
node *BST_search(node *root, int key);
node *BST_min(node *root);
node *BST_max(node *root);
node *BST_successor(node *x);
node *BST_predecessor(node *x);
void printNode(node *x);
void printTree(node *root);
void BST_inorder_tree_walk(node *root);

#endif