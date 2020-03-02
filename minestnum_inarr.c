#include<stdio.h>
//the max heap

//partation function
int partation(int* num,int start, int end){
        //each time is the last number
        int key = num[end];
        int j = start - 1;
        int i = start;
        int tmp;
        for(;i<end;++i){//do not include the last number
                if(num[i] < key){
                        ++j;
                        tmp = num[i];
                        num[i] = num[j];
                        num[j] = tmp;
                }
        }
        //exchange the j+1 with the end number
        tmp = num[end];
        num[end] = num[j+1];
        num[j+1] = tmp;
        return j+1;//return the index seperate the array

}

//two ways 
//one use the partation in quick sort to find the minest k numbers before the index after
// the partation function
int minest_x(int* num, int len, int k,int* output){
        if(num == NULL || output == NULL || len<=0 || k<=0 || k>len)
                return -1;
        int start = 0;
        int end = len-1;
        int index = partation(num,start,end);
        int i;
        while(index != k-1){
                if(index < k-1){
                        start = index + 1;
                        index = partation(num,start,end);

                }
                if(index > k-1){
                        end = index -1;
                        index = partation(num,start,end);
                }

        }
        for(i=0;i<k;++i){
                output[i] = num[i];
        }
        return 0;

}

//another is use the max heap or the rb_tree to save the maxest num in the k numbers 
// each time compare the num to the maxest num push or change the maxest make the k numbers minest
// the second way suit the big data enviroment

int main(){
        int num[8] = {4,5,1,6,2,7,3,8};
        int output[8] = {0};
        int k = 4;
        int i;
        minest_x(num,8,k,output);
        for(i=0;i<k;++i)
                printf("%d\n",output[i]);
        printf("%d\n",sizeof(int));
        return 0;
}
