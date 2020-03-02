#include <stdio.h>
struct node{
        int value;
        struct node* pleft;
        struct node* pright;
};
int mirror_tree(struct node* root){
        if(root == NULL)
                return -1;
        if(root->pleft == NULL && root->pright == NULL)
                return -1;
        //exchange the root left and right child tree node
        struct node* tmp = root->pleft;
        root->pleft = root->pright;
        root->pright = tmp;
        if(root->pleft)
                mirror_tree(root->pleft);
        if(root->pright)
                mirror_tree(root->pright);
        return 0;
}
