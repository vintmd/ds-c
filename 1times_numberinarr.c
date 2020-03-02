#include <stdio.h>
/*
  use the ^ find the last bit is 1 seperate into two array
  each array use ^ to find these two number which only show one time in array
  

 */

//find the last bit is 1's index
int last_bit_isone(int value){
        int index = 0; 
        //max bit is 31 bits
        while( (value&1)==0 && index < 8*sizeof(int) ){
                value = value >> 1;
                ++index;
        }
        return index;

}
int is_one(int value, int index){
        value = value >> index;
        if(value & 1 == 1)
                return 0;
        else
                return -1;
        
}
//first and second is the addr of these two number which need to be found
void 1times(int* num, int len, int* first, int* second){
        if(num == NULL || len < 2)
                return;
        int value = 0;
        int i;
        for(i = 0;i<len;++i){
                value ^= num[i];
        }
        int index = last_bit_isone(value);
        *first = *second = 0;
        //according to this bit seperate into two array each ^ to find these two 
        for(i = 0; i<len; ++i){
                if( 0 == is_one(num[i],index)){
                        (*first)^=num[i];
                }else
                        (*second)^=num[i];
                
        }
}
