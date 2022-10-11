#include "BST.h"
#include <stdio.h>

int main(){
    node *root=NULL;

    BST_insert(&root, createNode(15));
    BST_insert(&root, createNode(6));
    BST_insert(&root, createNode(3));
    BST_insert(&root, createNode(2));
    BST_insert(&root, createNode(4));
    BST_insert(&root, createNode(7));
    BST_insert(&root, createNode(13));
    BST_insert(&root, createNode(9));
    BST_insert(&root, createNode(18));
    BST_insert(&root, createNode(20));
    BST_insert(&root, createNode(17));


    printf("test for BST search\n");
    printNode(BST_search(root, 9));
    printNode(BST_search(root, 4));
    printNode(BST_search(root, 5));
    printNode(BST_search(root, 7));
    printf("\n");

    printf("test for BST min & max\n");
    printNode(BST_min(root));
    printNode(BST_max(root));
    printf("\n");

    printf("test for BST successor\n");
    printNode(BST_successor(BST_search(root, 15)));
    printNode(BST_successor(BST_search(root, 13)));
    printNode(BST_successor(BST_max(root)));    //no successor for max element in BST
    printf("\n");

    printf("test for BST predecessor\n");
    printNode(BST_predecessor(BST_search(root, 3)));
    printNode(BST_predecessor(BST_search(root, 4)));
    printNode(BST_predecessor(BST_min(root)));
    printf("\n");

    printTree(root);

    printf("test for BST_delete\n");
    //case 1:
    BST_delete(&root, BST_search(root, 4));

    //case 2:
    BST_delete(&root, BST_search(root, 18));

    //case 3:
    BST_delete(&root, BST_search(root, 20));


    printTree(root);

    //inorder tree walk on BST to get sorted element
    BST_inorder_tree_walk(root);
    printf("\n");


    freeBST(root);
    return 0;
}
