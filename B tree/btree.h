#ifndef _BTREE_H_
#define _BTREE_H_

//the macro define the minimum degree of the b tree
#define BTREE_MIN_M 2

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
btree_node *create_EmptyBtreeNode(btree tree);						//allocate memory for the btree_node
btree_node *create_btreeNode(btree tree, int key, void *val);	//put the node information into btree_node
void		free_btreeNode(btree_node *root, btree tree);

//search method for the btree
void *btree_search(btree tree, int key);								//return the val of the corresponding key
btree_node *btree_node_search(btree_node *root, int key, int *index);	//return the target node address and the index of the key in that node 

//insert method for the btree
void btree_insert(btree *tree, int key, void *val);										//since the root node may change, pass in the pointer of the btree
void btree_moveKeyVal(btree_node *inNode, int InIndex, btree_node *outNode, int OutIndex);	//move the key from the source node with specific index to the destination node with specific index
void btree_node_split(btree_node *root, btree tree, btree_node *newnode, int i);
btree_node *btree_node_insert(btree_node *root, btree tree, int key, void *val);		//if return the node that be upshifted, then you must update the root

#endif