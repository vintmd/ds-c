#ifndef __AVL_H__
#define __AVL_H__

typedef struct node{
	int key;
	int hight;
	struct node* left;
	struct node* right;
	struct node* pre;
}Node;
typedef struct tree{
	struct node* root;
}Tree;

//get high
int get_hight(Node* node);
//maxnum
int max(int a, int b);
//get_stat
int get_stat(Node* node);
//minnum
Node* minnum(Node* node);
//init node
Node* avl_init_node(int key);
//init tree
Tree* avl_init_tree();
//left_rotate
Node* left_rotate(Tree* tree,Node* node);
//right_rotate
Node* right_rotate(Tree* tree,Node* node);
//balance
int get_balance(Node* node);
//search
Node* avl_search(Tree* tree, int key);
//insert
Node* avl_insert(Tree* tree,Node* root, Node* node);
//delete
int avl_delete(Tree* tree, Node* root,Node* node);


#endif
