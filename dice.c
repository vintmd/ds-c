#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
  while or recursive
  while use two array to rember the n-1 n-2 n-3 n-4 n-5 n-6
 */


int g_maxvalue = 6;//the dice max number

void s_get_probable(int original, int current, int sum, int* probable){
        if(1 == current){
                probable[sum - original]++;
        }else{
                int i = 1;
                for(;i<=g_maxvalue;++i)
                        s_get_probable(original,current-1,sum+i,probable);
        }
}

void get_probable(int count, int* probable){
        int i = 1; 
        for(;i<=g_maxvalue;++i){
                s_get_probable(count,count,i,probable);
        }
}

void print_probable(int count){
        if(count < 1)
                return ;
        int max = count * g_maxvalue;
        int* probable = (int*)malloc( (max - count + 1)*sizeof(int) );
        if(probable == NULL)
                return;
        int i = count;
        double total;
        int race;
        for(;i<=max;++i){
                probable[i-count] = 0;
        }
        get_probable(count,probable);
        total = pow((double)g_maxvalue,count);
        for(i=count;i<=max;i++){
                race = probable[i-count] / total;
                printf("%d: %e\n",i,race);
        }
}
