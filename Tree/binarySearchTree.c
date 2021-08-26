#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int value;
    struct node *left;
    struct node *right;
} node;

node *createNode(int value){
    node *newnode = malloc(sizeof(node));
    newnode->value = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

/*
since we need to change the root address in every recursive state
therefore, passing the pointer to root to change the address
*/
bool insertNumber(node **rootptr, int value){
    node *root = *rootptr;

    //empty tree, the first element to build the tree
    if(root==NULL){
        (*rootptr)=createNode(value);
        return true;
    }

    //if the element had been in the tree
    if(root->value==value){
        //do nothing
        return false;
    }

    //recursive to insert the number into tree
    else{
        if(value < root->value)
            return insertNumber(&(root->left), value);
        else
            return insertNumber(&(root->right), value);
    }
}

bool findNumber(node *root, int value){
    if(root==NULL)
        return false;
    if(root->value==value)
        return true;
    else{
        if(value < root->value)
            return findNumber(root->left, value);
        else
            return findNumber(root->right, value);
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
    printf("value = %d\n", root->value);

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
    printTreeRecursive(root, 0);
}

int main(){

    node *root=NULL;

    insertNumber(&root, 85);
    insertNumber(&root, 100);
    insertNumber(&root, 26);
    insertNumber(&root, 71);
    insertNumber(&root, 1);
    insertNumber(&root, 4);
    insertNumber(&root, 3);
    insertNumber(&root, 2);
    insertNumber(&root, 5);
    insertNumber(&root, 16);
    insertNumber(&root, 24);
    insertNumber(&root, 8);
    insertNumber(&root, 96);
    insertNumber(&root, 17);

    printTree(root);

    printf("%d (%d)\n", 17, findNumber(root, 17));
    printf("%d (%d)\n", 4, findNumber(root, 4));
    printf("%d (%d)\n", 24, findNumber(root, 24));
    printf("%d (%d)\n", 98, findNumber(root,98));
    printf("%d (%d)\n",13, findNumber(root, 13));
    printf("%d (%d)\n", 25, findNumber(root, 25));


    return 0;
}