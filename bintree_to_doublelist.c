#include<iostream>
struct node{
        int value;
        struct node* pleft;
        struct node* pright;
};
//plastnode to rember the lastnode in double list
//use the inorder print
void change(struct node* root, struct node** plastnode){
        if(root == NULL) 
                return;
        struct node* cur = root;
        if(cur->pleft != NULL)
                change(cur->pleft,plastnode);

        cur->pleft = *plastnode;
        if(*plastnode != NULL)
                //have the node in the double list
                (*plastnode)->pright = cur;
        *plastnode = cur;


        if(cur->pright != NULL)
                change(cur->pright,plastnode);
}
struct node* to_double_list(struct node* root){
        if(root == NULL)
                return NULL;
        struct node* plastnode = NULL; 
        change(root, &plastnode);

        //return the head of the double list;
        while(plastnode->pleft != NULL && plastnode != NULL){
                plastnode = plastnode->pleft;
        }
        return plastnode;
}

