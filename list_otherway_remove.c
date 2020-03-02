#include <stdio.h>
#include <stdlib.h>
typedef struct list_node* list_index;
struct list_node{
        int num;
        list_index pnext;
};
struct list{
        list_index phead;
        int count;
};
//the linus way to delete the entry node
int remove_new(struct list* p_list,struct list_node*p){
        struct list_node** aim = &p_list->phead;
        while(*aim != p){
                //not found
                aim = &(*aim)->pnext;
        }
        //put the addr of which node need to be delete use for the next node
        *aim = p->pnext;
        return 0;
}
//to remove the node
int remove_past(struct list* p_list,struct list_node* p){
        struct list_node* tmp =  p_list->phead;
        struct list_node* pre = NULL;
        while(tmp != p){
                pre = tmp;
                tmp = tmp->pnext;
        }
        if(!pre){
                //the head node need to be delete;
                p_list->phead = p->pnext; 
        }
        else
                pre->pnext = p->pnext;
        return 0;
}
int main(){
        struct list* p = (struct list*)malloc(sizeof(struct list));
        struct list_node* p1 = (struct list_node*)malloc(sizeof(struct list_node));
        struct list_node* p2 = (struct list_node*)malloc(sizeof(struct list_node));
        struct list_node* p3 = (struct list_node*)malloc(sizeof(struct list_node));

        struct list_node* head = NULL; 
        p->phead = p1;
        p1->pnext = p2;
        p2->pnext = p3;
        p1->num = 1;
        p2->num = 2;
        p3->num = 3;
        //remove_past(p,p2);
        remove_new(p,p2);
        head = p->phead;
        while(head != NULL){
                printf("%d\n",head->num);
                head = head->pnext;
        }
        return 0;
}
