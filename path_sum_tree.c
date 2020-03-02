#include<iostream>
using namespaces std;
struct node{
        int value;
        struct node* pleft;
        struct node* pright;

};
int find_path(struct node* root, int sum, vector<int>& path, int cur){
        cur += root->value;
        path.push_back(root->value);
        bool is_leaf = root->pleft == NULL && root->pright == NULL;
        if(cur == sum && is_leaf){
                //print the node in this path 
        }
        if(root->pleft != NULL)
                find_path(root->pleft , sum,path,cur);
        if(root->pright != NULL)
                find_path(root->pright,sum,path,cur);
        //when finish to pop the leaf node when this path is not the sum path
        path.pop_back()

}
int find_sum_path(struct node* root, int sum){
        if(root == NULL)
                return -1;
 std:vector<int> path;
        return find_path(root,sum,path,0);
}
