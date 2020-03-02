/**
 * @file avl.c node contains the hight
 * @brief node contains the hight
 * the hight is the max number in {left , right} +1
 * ps: when i use the function similar to rb tree insert
 * i found avl tree insert a node change the every node member in this son tree
 * the hight all changed but when final to insert need to count the every node in 
 * son tree hight, so i decide to use the recursive way to realize the avl insert
 * @author tmd
 * @version 1.0
 * @date 2016-12-01
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"avl.h"


int get_hight(Node* node){
	if(node == NULL)
		return 0;
	return node->hight;
}
int max(int a, int b){//avl tree not exist equal number
	return a>b?a:b;
}
/**
 * @brief get_stat  get the hight difference 
 * case1 or case2 left-left >1
 * case3 or case4 right-right <-1
 * @param node
 * @return 
 */
int get_stat(Node* node){
	if(node == NULL)
		exit(1);
	return get_hight(node->left)-get_hight(node->right);	
}

Node* avl_init_node(int key){
	Node* tmp = (Node*)malloc(sizeof(Node));
	if(tmp == NULL)
		return NULL;
	tmp->left = NULL;
	tmp->pre = NULL;
	tmp->right = NULL;
	tmp->key = key;
	tmp->hight = 1;
	return tmp;
}

Tree* avl_init_tree(){
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->root = NULL;
	if(tree == NULL)
		return NULL;
	return tree;

}
//return the new root node
Node* left_rotate(Tree* tree, Node* node){
	Node* y = node->right;
	node->right = y->left;
	if(y->left != NULL)
		y->left->pre = node;
	y->pre = node->pre;	
	if(node->pre == NULL){
		tree->root = y;	
	}else if(node->pre->left == node){
		node->pre->left = y;	
	}else{
		node->pre->right = y;	
	}
	y->left = node;
	node->pre = y;
	//change the hight
	node->hight = max(get_hight(node->left),
			get_hight(node->right)) + 1;
	y->hight = max(get_hight(y->left),
			get_hight(y->right)) + 1;
	
	
	return y;
}

Node* right_rotate(Tree* tree, Node* node){
	Node* y = node->left;
	node->left = y->right;
	if(y->right != NULL)
		y->right->pre = node;
	y->pre = node->pre;
	if(node->pre == NULL){
		tree->root = y;	
	}else if(node->pre->left == node){
		node->pre->left = y;	
	}else{
		node->pre->right = y;	
	}
	y->right = node;
	node->pre = y;
	//change the hight
	node->hight = max(get_hight(node->left),
			get_hight(node->right)) + 1;
	y->hight = max(get_hight(y->left),
			get_hight(y->right)) + 1;
	
	return y;
}
//the iter way 
Node* avl_search(Tree* tree, int key){
	while(tree->root != NULL && tree->root->key != key){
		if(key < tree->root->key){
			tree->root = tree->root->left;	
		}else{
			tree->root = tree->root->right;	
		}
	}
	return tree->root;
}

/**
 * @brief balance use the functhion of get_stat
 * according the each case to let the avl tree balance
 * case1 left-left use rightrotate
 * case2 left-right use left then right rotate
 * case3 right-left use right then left rotate
 * case4 right-right use left rotate
 * @param node
 *
 * @return 
 */
int  get_balance(Node* node){
	if(node == NULL)
		return 0;
	return get_hight(node->left) - get_hight(node->right);
}

Node* avl_insert(Tree* tree,Node* root, Node* node){
	//the normal bst also can use this way
	if(root == NULL)	
		return  node;
	if(node->key < root->key){
		root->left = avl_insert(tree,root->left,node);
	}else{
		root->right = avl_insert(tree,root->right,node);	
	}
	//reset the node hight
	root->hight = max(get_hight(root->left),
			get_hight(root->right)) + 1;
	//get balance
	int balance = get_balance(root);	
	//according to the balance judge which case 
	//case1 Left Left
	if(balance > 1 && node->key < root->left->key){
		return right_rotate(tree,root);
	}	
	//case2 Left Right
	if(balance > 1 && node->key > root->right->key){
		left_rotate(tree,root->left);	
		return right_rotate(tree,root);
	}
	//case3 Right Left
	if(balance < -1 && node->key < root->right->key){
		right_rotate(tree,root->right);	
		return left_rotate(tree,root);
	}
	//case4 Right Right
	if(balance < -1 && node->key > root->right->key){
		return left_rotate(tree,root);	
	}
	//return the unchanged root node;	
	return root;

}
//minnum
Node* minnum(Node* node){
	while(node->left != NULL)
		node = node->left;
	return node;
}

/**
 * @brief avl_delete this function only suit for the node 
 * which dont have the pre element
 * @param tree
 * @param root
 * @param node
 *
 * @return 
 */
Node* avl_delete(Tree* tree,Node* root, Node* node){
	//the normal bst delete
	if(root == NULL)
		return root;
	if(node->key < root->key){
		root->left = avl_delete(tree,root->left,node);	
	}else if(node->key > root->key){
		root->right = avl_delete(tree,root->right,node);	
	}else{// find the euqual node
		//have only one child or no child
		if((root->left == NULL)|| (root->right == NULL)){ 
			Node* tmp = root->left?root->left:root->right;	
			//no child
			if(tmp == NULL){
				tmp = root;	
				root = NULL;
			}else{//have only child
				*root = *tmp;//copy the contents 
			}
			free(tmp);
		
		}else{
			//node with two child 	
			Node* successer = minnum(root->right);
			root->key = successer->key;
			//delete this successer node
			root->right = avl_delete(tree,root->right,successer);
		}
	}

	//if tree has only one node then return 
	if(root == NULL){
		return root;	
	}
	//update hight
	root->hight = max(get_hight(root->left),get_hight(root->right)) + 1;
	int balance = get_balance(root);
	// If this node becomes unbalanced, then there are 4 cases
	// Left Left Case
	if (balance > 1 && get_balance(root->left) >= 0)
	    return right_rotate(tree,root);
	
	// Left Right Case
	if (balance > 1 && get_balance(root->left) < 0)
	{
		root->left =  left_rotate(tree,root->left);
		return right_rotate(tree,root);
	}

	// Right Right Case
	if (balance < -1 && get_balance(root->right) <= 0)
		return left_rotate(tree,root);

	// Right Left Case
	if (balance < -1 && get_balance(root->right) > 0)
	{
		root->right = right_rotate(tree,root->right);
		return left_rotate(tree,root);
	}

	return root;
}

int show(Node* root){
	if(root != NULL){
		printf("%d\n",root->key);
		show(root->left);
		show(root->right);
	}
	return -1;
}

//test main function
int main(){
	Tree* tree = avl_init_tree();	
	Node* tmp = avl_init_node(12);
	Node* tmp1 = avl_init_node(9);
	Node* tmp2 = avl_init_node(8);
	tree->root = avl_insert(tree,tree->root,tmp);
	tree->root = avl_insert(tree,tree->root,tmp1); 
	tree->root = avl_insert(tree,tree->root,tmp2); 
	show(tree->root);

	

	return 0;
}
