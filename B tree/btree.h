#ifndef _BTREE_H_
#define _BTREE_H_

//the macro define the minimum degree of the b tree
#define BTREER_MIN_M 2

typedef struct _btree_node{
	int n;							// 	how many integers in the keys array
	int number_of_children;			//	# of existing children (0 for leaf node)
	int *keys;						//	array of the keys
	void **vals;					//	the data corresponding to the key (an array of void pointer)
	struct _btree_node **children;	//	children array
} btree_node;

typedef struct _btree{
	int max_degree;
	int min_degree;
	btree_node *root;
} btree;

//constructor and destructor for btree
btree 	create_btree(int m);
void 	free_btree(btree *tree);

//constructor and destructor for btreeNode
btree_node *create_btreeNode(btree tree);
btree_node *init_btreeNode(btree tree, int *key, void *vals);
void		free_btreeNode(btree_node *root, btree tree);

#endif