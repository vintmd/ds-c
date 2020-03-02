#include <stdio.h>
#include <stdlib.h>
struct node{
        int num;
        struct node* pleft;
        struct node* pright;
};
struct node* rebuild_process(int* pre_start, int* pre_end, int* in_start, int* in_end){
        int value = pre_start[0];
        struct node* root = (struct node*)malloc(sizeof(struct node));
        root->num = value;
        root->pleft = root->pright = NULL;
        //judge whether only one node
        if(pre_start == pre_end){
                if(in_start == in_end && *pre_start == *in_start)
                        return root;
                else
                        return NULL;
        }


        //already know the root to find index in the inorder arr
        //the root_inorder show the root node addr in the inorder array
        int* root_inorder = in_start;
        while(root_inorder <= in_end && *root_inorder != value){
                ++root_inorder;
        }
        if(root_inorder == in_end && *root_inorder != value)
                return NULL;
        int left_len = root_inorder - in_start;
        int* left_pre_end = pre_start + left_len;//the offset 
        //sperate the left and right child trees
        if(left_len > 0){
                //build left child tree
                root->pleft = rebuild_process(pre_start+1,left_pre_end,in_start,root_inorder-1);
        }
        if(left_len < in_end - in_start){

                //build right child tree
                root->pright =  rebuild_process(left_pre_end + 1,pre_end,root_inorder+1 ,in_end);
        }
        return root;


}
struct node* rebuild(int* preorder, int* inorder, int len){
        if(preorder == NULL || inorder == NULL || len <=0)
                return NULL;
        return rebuild_process(preorder,preorder+len-1,inorder,inorder+len-1);

}
void show_last(struct node* root){
        if(NULL == root)
                return ;
        show_last(root->pleft);
        show_last(root->pright);
        printf("%d\n",root->num);
        return;
}

int main(){
        int pre[8] = {1,2,4,7,3,5,6,8};
        int in[8] = {4,7,2,1,5,3,8,6};
        struct node* root = rebuild(pre,in,8);
        show_last(root);
        return 0;
}
