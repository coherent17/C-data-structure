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

btree_node *init_btreeNode(btree tree, int key, void *val){
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

//move the key from the source node with specific index to the destination node with specific index
void moveKeyValue(btree_node *inNode, int InIndex, btree_node *outNode, int OutIndex){
	outNode->keys[OutIndex] = inNode->keys[InIndex];
	outNode->vals[OutIndex] = inNode->vals[InIndex];
}

void btree_insert(btree *tree, int key, void *val){
	//if the root node doesn't exist, create it!
	if(tree->root == NULL){
		tree->root = init_btreeNode(*tree, key, val);
	}
	else{
		btree_node *newRoot = btree_node_insert(tree->root, *tree, key, val);	//if return the node that be upshifted, then you must update the root
		if(newRoot != NULL) tree->root = newRoot;
	}
}

btree_node *btree_node_spilt(btree_node *root, btree tree, btree_node *newnode, int newNodeindex){

}

btree_node *btree_node_insert(btree_node *root, btree tree, int key, void *val){
	//using a while loop to find the place to insert
	int i = 0;
	while(i < root->n && key > root->keys[i]) i++;

	//if there is a duplicate key, replace the original value with the new value
	if(i < root->n && key == root->keys[i]){	//if i == root->n, violate the max degree of the node, we should spilt the node
		root->vals[i] = val;
		return NULL;	//since no upshift node exist, return NULL
	}

	//if we didn't find the key in this node 
}