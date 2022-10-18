#include "RBT.h"
#include <stdlib.h>

rb_node *rb_newNode(int key){
    rb_node *newnode = malloc(sizeof(rb_node));
    newnode->key = key;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = NULL;
    return newnode;
}

/*
left rotate: 

     x              y
    / \    ==>     / \
    a  y          x   r
      / \        / \
     b   r      a   b

*/

//Time complexity: O(1)
void rb_left_rotate(rb_node **rootptr, rb_node *x){
    rb_node *y = x->right;      //set y as right child of x
    x->right = y->left;         //turn y's left subtree into x's right subtree

    //update parent pointer of x's right (b) if b is not NULL
    if(y->left != NULL){
        y->left->parent = x;
    }

    //update y's parent pointer
    y->parent = x->parent;

    //if x's parent is NULL, let y as root of tree
    if(x->parent == NULL){
        *rootptr = y;
    }           

    //update x's parent's left/right pointer
    else if(x == x->parent->left){
        x->parent->left = y;
    }   
    else{
        x->parent->right = y;
    }

    y->left = x;                //put x on y's left
    x->parent = y;              //update parent pointer of x
}

/*
right rotate:

        y               x
       / \             / \
      x   r   ==>     a   y
     / \                 / \
    a   b               b   r 

*/

//Time complexity: O(1)
void rb_right_rotate(rb_node **rootptr, rb_node *y){
    rb_node *x = y->left;
    y->left = x->right;     //turn x's right subtree to y's left subtree

    if(x->right != NULL){
        x->right->parent = y;
    }

    x->parent = y->parent;

    if(y->parent == NULL){
        *rootptr = x;
    }

    else if(y == y->parent->left){
        y->parent->left = x;
    }
    else{
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

//maintain red-black property after rb_insert called
void rb_insert_FixUp(rb_node **rootptr, rb_node *z){
    
}

void rb_insert(rb_node **rootptr, int key){
    rb_node *z = rb_newNode(key);

    //if root is NULL, make z as root
    if(*rootptr == NULL){
        *rootptr = z;
        z->color = BLACK;   //root's color = black
        return;
    }

    rb_node *y = NULL;      //y track the parent of x
    rb_node *x = *rootptr;

    //standard BST insert function
    while(x != NULL){
        y = x;
        if(key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    z->parent = y;
    if(key > y->key){
        y->right = z;
    }
    else{
        y->left = z;
    }
    z->color = RED;     //coloring z red might violate red black tree property

    //call rb_insert_fixup to maintain red black tree property
    rb_insert_FixUp(rootptr, z);
}