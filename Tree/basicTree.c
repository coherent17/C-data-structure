#include <stdio.h>
#include <stdlib.h>

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

    node *node1 = createNode(5);
    node *node2 = createNode(6);
    node *node3 = createNode(7);
    node *node4 = createNode(8);
    node *node5 = createNode(9);

    node1->left = node2;
    node1->right = node3;
    node3->left = node4;
    node3->right = node5;

    printTree(node1);

    free(node1);
    free(node2);
    free(node3);
    free(node4);
    free(node5);

    return 0;
}