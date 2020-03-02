#include<stdio.h>
#include<stdlib.h>
/*
  the inverse pairs in the array
*/
int inverse_pair(int* num, int* copy, int start, int end){
        if(start == end){
                copy[start] = num[start];
                return 0;
        }
        int len = (end - start)/2;
        //NOTIC 
        int left = inverse_pair(copy,num,start,start + len);
        int right = inverse_pair(copy,num,start+len+1,end);
        int count = 0;

        int i = start + len;
        int j = end;
        int index = end;//copy index
        while(i>= start && j >= start+len+1){
                //seperate two array rebuild and sort
                if(num[i] > num[j]){
                        copy[index--] = num[i--];
                        count += j - start - len;
                }else{
                        copy[index--] = num[j--];
                }
        }
        //when after copy there may be have left
        for(;i>=start;--i)
                copy[index--] = num[i];
        for(;j>=start+len+1;--j)
                copy[index--] = num[j];
        return count + left + right;
}
int inverse(int* num, int len){
        if(num == NULL || len <=1)
                return -1;
        int* copy = (int*)malloc(sizeof(int) * len);
        int i;
        int count;
        for(i=0;i<len;++i){
                copy[i] = num[i];
        }
        for(i=0;i<len;++i){

                printf("%d\n",copy[i]);
        }
        printf("------------------------------\n");
        count = inverse_pair(num, copy, 0, len-1);
        for(i=0;i<len;++i){

                printf("%d\n",copy[i]);
        }
        return count;
}
int main(){
        int num[5] = {7,5,6,4,3};
        int count = inverse(num,5);
        printf("------------%d\n",count);
        //5
        return 0;
}
