#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INT_MAX 2147483648

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
btree_node *create_EmptyBtreeNode(btree tree){
	btree_node *newnode = malloc(sizeof(btree_node));
	newnode->n = 0;
	newnode->number_of_children = 0;
	newnode->keys = malloc((tree.max_degree - 1) * sizeof(int));
	newnode->vals = malloc((tree.max_degree - 1) * sizeof(void *));
	newnode->children = malloc(tree.max_degree * sizeof(btree_node *));
	return newnode;
}

btree_node *create_btreeNode(btree tree, int key, void *val){
	btree_node *newnode = create_EmptyBtreeNode(tree);
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
	for(*index = 0; *index < root->n && key >= root->keys[*index]; (*index)++){
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
void btree_moveKeyVal(btree_node *inNode, int InIndex, btree_node *outNode, int OutIndex){
	outNode->keys[OutIndex] = inNode->keys[InIndex];
	outNode->vals[OutIndex] = inNode->vals[InIndex];
}

void btree_insert(btree *tree, int key, void *val){
	//if the root node doesn't exist, create it!
	if(tree->root == NULL){
		tree->root = create_btreeNode(*tree, key, val);
	}
	else{
		btree_node *newRoot = btree_node_insert(tree->root, *tree, key, val);	//if return the node that be upshifted, then you must update the root
		if(newRoot != NULL) tree->root = newRoot;
	}
}

void btree_node_split(btree_node *root, btree tree, btree_node *newnode, int i){
	//set the newnode as the upshift root node

	int has_children = root->number_of_children;
	btree_node *temp = create_EmptyBtreeNode(tree);

	//copy children
	memcpy(temp->children, newnode->children, 2 * sizeof(btree_node *));

	//swap the newnode with the upshift node

	//insert before median & the upshift node will not be itself, need to update with the new median
	//(median at  index = min_degree - 1) 
	if(i < tree.min_degree){
		btree_moveKeyVal(root, tree.min_degree - 1, temp, 0);	//upshift element will e one before median

		//right shift to insert the newkey
		for(int j = tree.min_degree - 2; j >= i; j--){
			btree_moveKeyVal(root, j, root, j + 1);
		}

		//insert the new key
		btree_moveKeyVal(newnode, 0, root, i);
	}

	//insert after median
	else if(i > tree.min_degree){
		btree_moveKeyVal(root, tree.min_degree, temp, 0);

		//left shift to insert the new key
		for(int j = tree.min_degree + 1; j <= i && j <= root->n - 1; j++){
			btree_moveKeyVal(root, j, root, j - 1);
		}

		//insert the new key
		btree_moveKeyVal(newnode, 0, root, i - 1);
	}

	else{
		//newnode is the upshift key
		btree_moveKeyVal(newnode, 0, temp, 0);
	}

	//pop the newnode

	//get the actual upshift key value into newnode 
	btree_moveKeyVal(temp, 0, newnode, 0);

	//divide the current node into two children node (left child is the original root, and the right child allocate new empty node) 
	newnode->children[0] = root;
	newnode->children[1] = create_EmptyBtreeNode(tree);

	//copy the key value into the right child from left child
	for(int j = tree.min_degree; j <= root->n - 1; j++){
		btree_moveKeyVal(root, j, newnode->children[1], j - tree.min_degree);
		
		//delete the key value pair in the left child
		root->keys[j] = INT_MAX;
		root->vals[j] = NULL;
	}

	if(has_children){

		if(i < tree.min_degree - 1){
			//copy the children of the right children node
			for(int j = tree.min_degree; j < tree.max_degree; j++){
				newnode->children[1]->children[j - tree.min_degree] = newnode->children[0]->children[j - 1];
			}

			//right shift the children on the left side
			for(int j = tree.min_degree; j > i + 1; j--){
				newnode->children[0]->children[j] = newnode->children[0]->children[j - 1];
			}

			//insert the temp child
			newnode->children[0]->children[i + 1] = temp->children[1];			
		}

		else{
			//copy children to the right side
			for(int j = tree.min_degree + 1; j < tree.max_degree; j++){
				newnode->children[1]->children[j - tree.min_degree - 1] = newnode->children[0]->children[j];
			}

			//right shift children on the right side
			for(int j = tree.min_degree; j > i - tree.min_degree; j--){
				newnode->children[1]->children[j] = newnode->children[1]->children[j - 1];
			}

			//insert extra child on the right side
			newnode->children[1]->children[i - tree.min_degree] = temp->children[1];
		}

		//update children count
		newnode->children[0]->number_of_children = tree.min_degree + 1;
		newnode->children[1]->number_of_children = tree.max_degree - tree.min_degree;
	}

	//update key count
	newnode->children[0]->n = tree.min_degree;
	newnode->children[1]->n = tree.max_degree - 1 - tree.min_degree;
	newnode->n = 1;
	newnode->number_of_children = 2;
}

btree_node *btree_node_insert(btree_node *root, btree tree, int key, void *val){
	//using a while loop to find the place to insert
	int i = 0;
	while(i < root->n && key > root->keys[i]) i++;

	//if there is a duplicate key, replace the original value with the new value

	//if i == root->n, violate the max degree of the node, we should spilt the node
	if(i < root->n && key == root->keys[i]){	
		root->vals[i] = val;
		//since no upshift node exist, return NULL
		return NULL;
	}

	//if we didn't find the key in this node
	btree_node *upshiftNode = NULL;

	//leaf node
	if(root->number_of_children == 0){

		//if this node is full (max_degree - 1 keys), need to split and upshift
		if(root->n == tree.max_degree - 1){

			//???????????????????????????????????
			//???????????????????????????????????
			upshiftNode = create_btreeNode(tree, key, val); 

			//split the node
			btree_node_split(root, tree, upshiftNode, i);
		}

		//simply insert without the violation
		else{
			//right shift the key-value pair s.t. you create a empty space to the new key-value pair
			for(int j = root->n - 1; j >= i; j--){
				btree_moveKeyVal(root, j, root, j + 1);
			}
			//insert the element
			root->keys[i] = key;
			root->vals[i] = val;
			root->n++;
		}
	}
	else{
		//internal node, need to traverse and insert into the children
		upshiftNode = btree_node_insert(root->children[i], tree, key, val);
		if(upshiftNode != NULL){

			//if the current subtree root node is full
			if(root->n == tree.max_degree - 1){
				btree_node_split(root, tree, upshiftNode, i);
			}

			//if there exist a space for this key
			else{
				//right shift the keys
				for(int j = root->n - 1; j >= i; j--){
					btree_moveKeyVal(root, j, root, j + 1);
				}

				//insert the upshift key-value pair
				btree_moveKeyVal(upshiftNode, 0, root, i);

				//right shift the children
				for(int j = root->number_of_children - 1; j >= i + 1; j--){
					root->children[j + 1] = root->children[j];
				}

				//insert the children from the upshift key
				//???????????????????????????????????
				//???????????????????????????????????
				//the left children using the original node, but allocate new children for the right children
				root->children[i + 1] = upshiftNode->children[1];
				root->children[i] = upshiftNode->children[0];

				//update the counters
				root->n++;
				root->number_of_children++;


				//free the upshift node
				free(upshiftNode->keys);
				free(upshiftNode->vals);
				free(upshiftNode->children);
				free(upshiftNode);
				upshiftNode = NULL;
			}
		}
	}
	return upshiftNode;
}