#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

btree create_btree(int m){
	if(m < BTREER_MIN_M){
		m = BTREER_MIN_M;
	}

	btree result = {m, ceilf( (float)m / 2.0f) - 1, NULL};
	return result;
}

void free_btree(btree *tree){
	//recursivly free all nodes in the btree by DFS
	free_btreeNode(tree->root, *tree);
}

btree_node *create_btreeNode(btree tree){
	btree_node *newnode = malloc(sizeof(btree_node));
	newnode->n = 0;
	newnode->number_of_children = 0;
	newnode->keys = malloc((tree.m - 1) * sizeof(int));
	newnode->vals = malloc((tree.m - 1) * sizeof(void *));
	newnode->children = malloc(tree.m * sizeof(btree_node *));
	return newnode;
}

btree_node *init_btreeNode(btree tree, int *key, void *vals){
	btree_node *newnode = create_btreeNode(tree);
	newnode->keys[0] = key;
	newnode->vals[0] = val;
	newnode->n = 1;
	return newnode;
}

void free_btreeNode(btree_node *root, btree tree){
	if(root){
		//DFS to free the allocate node memory
		for(int i = 0; i < root->number_of_children; i++){
			free_btreeNode(root->children[i], tree);
		}
		free(root->children);
		free(root->keys);
		free(root->vals);
		free(root);
	}
}