#include <stdio.h>
int partation(int* num,int start, int end){
        //each time find the last num or other ways
        int x = num[end];
        int i = start;
        int j = i - 1;
        int tmp;
        for(;i<end;i++){
                if(num[i] <= x){
                        ++j;
                        tmp = num[i];
                        num[i] = num[j];
                        num[j] = tmp;
                }
        }
        //exchange j+1 with the end
        tmp = num[end];
        num[end] = num[j+1];
        num[j+1] = tmp;
        return j+1;

}
int more_than_half(int* num, int len){
        int mid = len >> 1;
        int end = len - 1;
        int start = 0;
        //use the quick sort partaion way to find the mid num
        int index = partation(num,start,end);
        int result;
        while(index != mid){
                if(index < mid){
                        start = index + 1;
                        index = partation(num,start,end);
                }
                if(index > mid){
                        end = index - 1;
                        index = partation(num, start,end);
                }


        }
        result = num[mid];

        //check for the result 
        return result;

}
/*
  prove this method in pointer offer is wrong


 */
int over_halfarr(int* num, int len){
        if(num == NULL || len <= 0)
                return -1;
        int result = num[0];
        int count = 1;
        int i = 1;
        for(;i<len;i++){
                if(count == 0){
                        result = num[i];
                        count = 1;
                }else if(result == num[i])
                        ++count;
                else
                        --count;


        }
        //check for 
        //TODO : check(num,len,result);
        return result;

}
int main(){
        int test[9] = {1,2,3,2,2,3,5,4,4};
        int result = over_halfarr(test,9);
        int result2 = more_than_half(test,9);
        printf("%d\n",result);
        printf("%d\n",result2);
        return 0;
}
