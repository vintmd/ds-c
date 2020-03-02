#include <stdio.h>
void print_one_cycle(int** num, int col, int row, int start){
        //have four step to print one cycle
        int end_x = col-start-1;
        int end_y = row-start-1;
        int i ;
        //case 1: no matter what happen it always can print one line
        for(i = start;i<=end_x;++i){
                printnum(num[start][i]);
        }
        //case 2: from the top to the buttom
        if(start < end_y){
                for(i = start+1;i<=end_y;++i){
                        printnum(num[i][end_x]);
                }
        }
        //case3: from the right to the left
        if(start < end_x && start < end_y ){
                for(i = end_x - 1;i>=start; --i)
                        printnum(num[end_y][i]);
        }
        //case4: from the buttom to the top
        if(start < end_x && start < end_y -1){
                for(i = end_y - 1;i>=start+1; --i)
                        printnum(num[i][start]);
        }


}



void print_arr(int** num, int col, int row){
        if(num == NULL || col <=0 || row <=0)
                return;
        //start is the start index(x,x) to begin print the cycle
        int start = 0;
        while(col>start*2 && row>start*2){
                print_one_cycle(num,col,row,start);
        }
        return ;
}
