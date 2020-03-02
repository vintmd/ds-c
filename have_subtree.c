#include <stdio.h>
struct node{
        int value;
        struct node* pleft;
        struct node* pright;
};
int pro_have(struct node* root, struct node* s_root){
        if(s_root == NULL)
                return 1;
        if(root == NULL)
                return -1;
        if(root->value != s_root->value)
                return -1;
        return pro_have(root->pleft,s_root->pleft) &&
                pro_have(root->pright,s_root->pright);


}
int have_subtree(struct node* root, struct node* s_root){
        int result = -1;
        if(root != NULL && s_root != NULL){
                if(root->value == s_root->value){
                        result = pro_have(root,s_root);
                }
                if(!result)
                        result = have_subtree(root->pleft);
                if(!result)
                        result = have_subtree(root->pright);

        }
        return result;
}


