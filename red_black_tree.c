/**
 * @file red_black_tree.c
 * @brief bst缺点 insert delete不支持  动态集合的操作，
 *		  随着每次的删除子树中心偏向左侧节点，导致成为线性搜索降低速度.
 *		  而红黑树则保证能o(lgn)去支持这两个操作
 * nature: 1.每个节点不是黑就是红色 2.根节点是黑色 3.每个叶节点都是黑色NIL 
 *		   4.如果一个节点是红色则子节点都为黑色 5.对每个节点，从该节点到其所有后代叶节
 *		   点上都包含相同数目的黑色节点（黑高相同）
 * @author tmd
 * @version 1.0
 * @date 2016-11-24
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"red_black_tree.h"
//init node
Node* rb_node_init(int key,int color){
	Node* node = (Node*)malloc(sizeof(Node));
	if(node != NULL){
		node->key = key;	
		node->color = color;
		return node;
	}
	return NULL;
}
//init tree
Tree* rb_tree_init(){
	Tree* tree = (Tree*)malloc(sizeof(Tree));	
	if(tree != NULL){
		//nil node
		Node* node = rb_node_init(0,BLACK);
		if(node != NULL){
			//the nil node does not care left,key,right 
			node->left = NULL;					
			node->right = NULL;
			//when insert node the root node pre is the nil node			
			tree->nil = node;
			tree->root = tree->nil;
		}else{
			exit(1);	
		}
	}
	return tree;
}
//left_rotate
void left_rotate(Tree* tree, Node* node){
	Node* y = node->right;	
	node->right = y->left;
	//y left whether null
	if(y->left != tree->nil){//have the left side
		y->left->pre = node;	
	}
	y->pre = node->pre;
	//which side node in nodefather
	if(node->pre == tree->nil){
		tree->root = y;
	}else if(node->pre->left == node){
		node->pre->left = y;			
	}else{
		node->pre->right = y;	
	} 
	//y and node
	y->left = node;
	node->pre = y;
	return ;
}
//right_rotate is symmetry to the left_rotate
void right_rotate(Tree* tree, Node* node){
	Node* y = node->left;
	node->left = y->right;
	if(y->right != tree->nil){
		y->right->pre = node;	
	}
	y->pre = node->pre;
	if(node->pre == tree->nil){
		tree->root = y;	
	}else if(node->pre->left == node){
		node->pre->left = y;	
	}else{
		node->pre->right = y;	
	}
	y->right = node;
	node->pre = y;
	return ;
}
/**
 * @brief rb_tree_insert_fixup 
 * 改变分支使整体满足红黑树性质
 * 有三种情况:1. node的叔节点是红色 2. node的叔节点是黑色且node为于父节点右侧
 * 3. node的叔节点是黑色且node为于父节点左侧
 * 情况二将父节点左旋转即可得到情况3
 * ps:当改变节点颜色时应该考虑红黑树性质保持黑高不变左旋或右旋
 * @param tree
 * @param node the insert node
 */
void  rb_tree_insert_fixup(Tree* tree, Node* node){
	Node* y = NULL;//to rember the uncle node
	while(node->pre->color == RED){//父节点为红色时需要作调整
		if(node->pre == node->pre->pre->left){//父节点在哪一测
			y = node->pre->pre->right;//to rember the uncle node		
			if(y->color == RED){//case 1
				//change the father and uncle into BLACK and the grandfather is RED		
				node->pre->color = BLACK;
				y->color = BLACK;
				node->pre->pre->color = RED;
				node = node->pre->pre;
			}else{ 
				if(node == node->pre->right){
					//node on the right side(case2) can change into
					//left side(case3)
					node = node->pre;
					left_rotate(tree,node);//change into case3
				}
				//case3
				node->pre->color = BLACK;
				node->pre->pre->color = RED;
				right_rotate(tree,node->pre->pre);
			}
			
				
		}else{//父节点在右侧
			y = node->pre->pre->left;	
			if(y->color == RED){//case1
				node->pre->pre->color = RED;	
				node->pre->color = BLACK;
				y->color = BLACK;	
				node = node->pre->pre;
			}else{
				if(node == node->pre->left){//case2 change into case3
					node = node->pre;
					right_rotate(tree, node);
				}
				//case3
				node->pre->color = BLACK;
				node->pre->pre->color = RED;
				left_rotate(tree, node->pre->pre);
			}
		}
	}
	tree->root->color = BLACK;
	return;
}
/**
 * @brief rb_tree_insert 
 * 按照bst的插入方式将节点插入，并将插入节点置为红色，同时改变分支
 * 利用fixup函数使其满足红黑树性质
 * @param tree
 * @param node
 * @return 
 */
int rb_tree_insert(Tree* tree, Node* node){
	Node* pre = tree->nil;//rember the insert node father
	Node* tmp = tree->root;
	while(tmp != tree->nil){
		pre = tmp;	
		if(node->key < tmp->key){
			tmp = tmp->left;	
		}else{
			tmp = tmp->right;	
		}
	}
	node->pre = pre;
	if(pre == tree->nil){//node is root
		tree->root = node;	
	}else if(node->key < pre->key){//node on left
		pre->left = node;	
	}else{
		pre->right = node;	
	}
	//init node
	node->left = tree->nil;
	node->right = tree->nil;
	node->color = RED;//don't change the black high in the breach tree
	//according to the rb tree nature exchange the node loction in breach tree
	rb_tree_insert_fixup(tree,node);
	return 0;
}
/**
 * @brief rb_tree_transplant 
 * use aim node to replace the node
 * same to the BST but the null node point to the nil node
 * @param tree
 * @param node
 * @param aim
 * @return 
 */
int rb_tree_transplant(Tree* tree, Node* node, Node* aim){
	if(node->pre == tree->nil){
		tree->root = aim;	
	}else if(node == node->pre->left){//node in left side
		node->pre->left = aim;	
	}else{//in right side
		node->pre->right = aim;	
	}	
	//this place dont need to judge node whether have pre
	aim->pre = node->pre;
	return 0;
}
/**
 * @brief rb_tree_delete_fixup 
 *  通过记录需要改变的节点上次出现的位置x，去判断改变后的
 *  红黑树是否满足性质从而改变删除某节点后的情况
	case1:x的兄弟节点为红色
	case2:x的兄弟节点w为黑色，且w左右均为黑
	case3:x的兄弟节点w为黑色，且左红右黑
	case4:x的兄弟节点w为黑色，且w右为红
	case1 into case2 or case3 or case4
	case3 into case4
	case2 and case4 can sovle the problem direct
 * @param tree
 * @param node :the node which have changed .last location
 * @return 
 */
int rb_tree_delete_fixup(Tree* tree, Node* node){
	Node* brother = NULL;
	//if color is black if changed must be fixed
	while(node != tree->root && node->color == BLACK){
		if(node == node->pre->left){//left side
			brother = node->pre->right;
			//case1 can change into case2 or case3 or case4
			if(brother->color == RED){//case1
				brother->color = BLACK;	
				node->pre->color = RED;
				left_rotate(tree,node->pre);
				brother = node->pre->right;
			}
			//case2 to sovle the problem
			if(brother->right->color == BLACK && 
				brother->left->color == BLACK){
				brother->color = RED;	
				node = node->pre;
			}else{
				//case3	change into case4
				if(brother->right->color == BLACK){
					brother->color = RED;	
					brother->left->color = BLACK;
					right_rotate(tree, brother);
					brother = node->pre->right;
				}
				//case4	
				brother->color = node->pre->color;
				node->pre->color = BLACK;
				brother->right->color = BLACK;
				left_rotate(tree,node->pre);	
				node = tree->root;//end the while
			}
		}else{//if(node == node->pre->left) right side
			//clause with "right" and "left" exchanged
			brother = node->pre->left;
			//case1 can change into case2 or case3 or case4
			if(brother->color == RED){//case1
				brother->color = BLACK;	
				node->pre->color = RED;
				right_rotate(tree,node->pre);
				brother = node->pre->left;
			}
			//case2 to sovle the problem
			if(brother->right->color == BLACK && 
				brother->left->color == BLACK){
				brother->color = RED;	
				node = node->pre;
			}else{
				//case3	change into case4
				if(brother->left->color == BLACK){
					brother->color = RED;	
					brother->right->color = BLACK;
					left_rotate(tree, brother);
					brother = node->pre->left;
				}
				//case4	
				brother->color = node->pre->color;
				node->pre->color = BLACK;
				brother->left->color = BLACK;
				right_rotate(tree,node->pre);	
				node = tree->root;//end the while
			}
		}		
	
	}
	node->color = BLACK;
	return 0;
}

Node* rb_tree_minnum(Tree* tree, Node* root){
	while(root->left != tree->nil){
		root = root->left;	
	}
	return root;
}
/**
 * @brief rb_tree_delete same to the BST delete
 * add two point 1:rember the successer node y color(if is black 
 * show it have changed the rb tree nature)
 * 2:rember the successer node y last loction in tree x
 *
 * @param tree
 * @param node
 *
 * @return 
 */
int rb_tree_delete(Tree* tree, Node* node){
	//init y
	Node* y = node;//the node need to change loction
	Node* x = NULL;//rember the y last loction in tree
	//rember the color of which node you want change
	int y_origin_color = y->color;
	if(node->left == tree->nil){//node have no left
		x = node->right;
		rb_tree_transplant(tree, node,node->right);
	}else if(node->right == tree->nil){//have no right
		x = node->left;	
		rb_tree_transplant(tree, node,node->left);
	}else{//have two side
		//find successer node y judge y whether is node right side	
		y = rb_tree_minnum(tree,node->right);
		y_origin_color = y->color;
		x = y->right;
		//judge y pre whether node
		if(y->pre == node){//is the node right side
			x->pre = y;	
		}else{//the y have no left side
			//transplant y with y right	
			rb_tree_transplant(tree, y,y->right);
			y->right = node->right;
			y->right->pre = y;
		}
		//transplant y with node;
		rb_tree_transplant(tree,node,y);
		y->left = node->left;
		y->left->pre = y;
		y->color = node->color;//became node color keep black tree high
	}
	//if change node is red do not change nature
	if(y_origin_color == BLACK)
		rb_tree_delete_fixup(tree,x);
	return 0;
}
//show
void show(Tree* tree, Node* node){
	if(node != NULL){
		printf("-----------\n")	;
		if(node->left != tree->nil)
			printf("left %d\n",node->left->key);
		if(node->right != tree->nil)
			printf("right %d\n",node->right->key);
		if(node->pre != tree->nil)
			printf("pre %d\n",node->pre->key);
		printf("-----------\n")	;
	}
	return ;
}

//Free
//void Free(Tree* tree){}

//test main funciton
int main()
{
	Tree* tree = rb_tree_init();
	Node* tmp = rb_node_init(11,RED);		
	Node* tmp1 = rb_node_init(14,RED);
	//.....
	rb_tree_insert(tree, tmp);
	rb_tree_insert(tree, tmp1);
	show(tree,tmp1);
	rb_tree_delete(tree, tmp1);
	show(tree,tmp);
	//Free(tree);
	return 0;
}

