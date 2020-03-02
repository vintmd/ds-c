#include <stdio.h>
/*
  use the binary search way to dirct find the first index and the last index
  the accurtimes is the last index - first index + 1
 */
static int get_first(int* num, int len, int k, int start, int end){
        if(start > end)
                return -1;
        int mid_index = (end + start)/2;
        int mid_num = num[mid_index];
        if(k == mid_num){
                //whether is the first
                if(mid_index == 0 || (mid_index > 0 && num[mid_index - 1] != k)){
                        //is the first accur
                        return mid_index;
                }else
                        end = mid_index - 1;
        }else if(k > mid_num){
                start = mid_index + 1;
        }else
                end = mid_index - 1;
        return get_first(num,len,k,start,end);
}

static int get_last(int* num, int len, int k, int start,int end){
        if(start > end)
                return -1;
        int mid_index = (end + start)/2;
        int mid_num = num[mid_index];
        if(k == mid_num){
                if(mid_index == len-1 || (mid_index < len -1 && num[mid_index + 1] != k)){
                        return mid_index;
                }
                else{
                        start = mid_index + 1;
                }

        }else if(k > mid_num){
                start = mid_index + 1;
        }else
                end = mid_index - 1;
        return get_last(num,len,k,start,end);
}
//true return the times shown
int accur_times(int* num, int len, int key){
        if(num == NULL || len <=0)  
                return -1;
        int first = get_first(num,len,key,0,len-1);
        int last = get_last(num,len,key,0,len-1);
        int times = 0;

        if(first > -1 &&  last > -1)
                times = last - first + 1;

        return times;

}

int main(){
        int test[8] = {1,2,3,3,3,3,4,5};
        int times = accur_times(test,8,3);
        printf("%d\n",times);
        return 0;
}
