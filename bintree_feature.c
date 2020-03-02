#include <stdio.h>
struct node{
        int value;
        struct node* pleft;
        struct node* pright;
};

// count the depth of the binary tree
// the longest path(from the root to the leave node) length
int depth(struct node* root){
        if(root == NULL)
                return 0;
        int left = depth(root->pleft);
        int right = depth(root->pright);
        return (left > right)?(left + 1):(right+1);
}

//judge balance binary tree

// one way to count the depth whether limit 1
int is_bbt(struct node* root){
        if(root == NULL) 
                return 0;
        int left = depth(root->pleft);
        int right = depth(root->pright);
        int diff = left - right;
        if(diff > 1 || diff < -1)
                return -1;
        //return is_bbt(root->pleft) && is_bbt(root->pright);
        return ( (is_bbt(root->pleft) == 0) && (is_bbt(root->pright) == 0) )?0:-1;
}


//another way use the last order in tree to according the child node depth decide the father node
int is_bbt_other(struct node* root, int* depth){
        if(root == NULL){
                *depth = 0 ;
                return 0;
        }
        int left_depth ;
        int right_depth;
        if( (is_bbt_other(root->pleft,&left_depth) == 0) &&
            (is_bbt_other(root->pright,&right_depth) == 0) ){
                int diff = left_depth - right_depth;
                if(diff <= 1 && diff >= -1){
                        //balanced
                        *depth = 1 + ((left_depth > right_depth)?left_depth:right_depth);
                        return 0;
                }
        }
        return -1;
}
int is_balance(struct node* root){
        int depth = 0;
        int result = is_bbt_other(root,&depth);
        return  result;
}

int main(){
        printf("%d\n",(-1)&&(-1));
        printf("%d\n",(0)&&(0));
        printf("%d\n",(-1)&&(0));
        return 0;
}
