#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

btree create_btree(int m){
	if(m < BTREE_MIN_M){
		m = BTREE_MIN_M;
	}

	btree result = {m, ceilf( (float)m / 2.0f) - 1, NULL};
	return result;
}

void free_btree(btree *tree){
	//recursivly free all nodes in the btree by DFS
	free_btreeNode(tree->root, *tree);
}

//allocate memory for the btree node
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

//search method in btree
void *btree_search(btree tree, int key){
	int index;
	btree_node *result = btree_node_search(tree.root, key, &index);

	/*
	//not found the key in the btree
	if(result == NULL){
		return NULL;
	}
	else return result->vals[index];
	*/
	return result ? result->vals[index] : NULL;
}							

btree_node *btree_node_search(btree_node *root, int key, int *index){
	for(*index = 0; *index < root->n && key >= root->keys[*index]; i++){
		//if find the key in this node
		if(key == root->keys[*index]) return root;
	}

	/*
	//if the node has children(internal node), traverse the children node
	if(root ->number_of_children > 0) return btree_node_search(root->children[*index], key, index);
	
	//if not found the key in the btree return NULL
	return NULL;
	*/
	return root -> number_of_children > 0 ? btree_node_search(root->children[*index], key, index) : NULL;
}