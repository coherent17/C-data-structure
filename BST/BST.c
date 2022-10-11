#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

node *createNode(int key){
    node *newnode = (node *)malloc(sizeof(node));
    newnode->key = key;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;
    return newnode;
}

void BST_insert(node **rootptr, node *z){
    node *y = NULL;
    node *x = *rootptr;

    while(x != NULL){
        y = x;
        if(z->key < x->key){
            x = x->left;
        }
        else x = x->right;
    }
    z->parent = y;

    if(y == NULL) *rootptr = z;  //empty BST
    else if(z->key < y->key) y->left = z;
    else y->right = z;

}

node *BST_search(node *root, int key){
    if(root == NULL || key == root->key){
        return root;
    }
    
    if(key < root->key){
        return BST_search(root->left, key);
    }
    else{
        return BST_search(root->right, key);
    }
}

node *BST_min(node *root){
    while (root->left != NULL){
        root = root->left;
    }
    return root;
}

node *BST_max(node *root){
    while (root->right != NULL){
        root = root->right;
    }
    return root;
}

//return the successor node of x
//successor of node x is the node with the smallest key greater than x->key
node *BST_successor(node *x){
    if(x->right != NULL){
        return BST_min(x->right);
    }

    node *y = x->parent;
    while(y != NULL && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}

node *BST_predecessor(node *x){
    if(x->left != NULL){
        return BST_max(x->left);
    }

    node *y = x->parent;
    while(y != NULL && x == y->left){
        x = y;
        y = y->parent;
    }
    return y;
}

void BST_transplant(node *root, node *u, node *v){
    
}

void BST_delete(node **rootptr, node *z){

}

void printNode(node *x){
    if(x == NULL){
        printf("No such node!\n");
    }
    else{
        printf("Node key = %d\n", x->key);
    }
}

void printTabs(int numtabs){
    for (int i = 0; i < numtabs;i++){
        printf("\t");
    }
}

void printTreeRecursive(node *root, int level){
    if(root==NULL){
        printTabs(level);
        printf("---<empty>---\n");
        return;
    }

    printTabs(level);
    printf("value = %d ", root->key);
    if(root->parent){
        printf("parent value = %d", root->parent->key);
    }
    printf("\n");

    //recursive to print the branch of tree

    printTabs(level);
    printf("left\n");
    printTreeRecursive(root->left, level+1);

    printTabs(level);
    printf("right\n");
    printTreeRecursive(root->right, level+1);
    
    printTabs(level);
    printf("Done\n");
}

void printTree(node *root){
    printf("\n\n");
    printTreeRecursive(root, 0);
}

void BST_inorder_tree_walk(node *root){
    if(root != NULL){
        BST_inorder_tree_walk(root->left);
        printf("%d ", root->key);
        BST_inorder_tree_walk(root->right);
    }
}