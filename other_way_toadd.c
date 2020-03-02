#include <stdio.h>
/* 

   the other way to sum two number without use the signal 
   1）不考虑进位 结果与抑或的结果相同
   2)考虑进位的结果与按位与相同
   3）俩结果相加得到最终求和结果
 */ 
int sum(int num1, int num2){
        int sum, carry;
        do{//until the carry sumed don't have carry then have the asked sum number
                sum = num1 ^ num2;
                carry = (num1 & num2) << 1;
                num1 = sum;
                num2 = carry;
        }while(num2 != 0);
        return sum;
}
/*

  the other way to change two number with each other

 */
int change1(int num1, int num2){
        num1 = num1 ^ num2;
        num2 = num1 ^ num2;
        num1 = num1 ^ num2;
        printf("%d %d\n",num1,num2);
        return 0;

}
int change2(int num1, int num2){
        num1 = num1 + num2;
        num2 = num1 - num2;
        num1 = num1 - num2;
        printf("%d %d\n",num1,num2);
        return 0;
}


int main(){
        int a = 10;
        int b = 3;
        int ret;
        ret = sum(a,b);
        printf("%d\n",ret);
        ret = change1(a,b);
        ret = change2(a,b);
        return 0;
}
