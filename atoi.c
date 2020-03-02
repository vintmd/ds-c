#include <stdio.h>
/*
  complete atoi

 */
int core(const char* str, int minus){
        int ret = 0;
        int flag = (minus == 0)?-1:1;
        while(*str != '\0'){
                if(*str >= '0' && *str <='9'){
                        ret = ret*10 + flag*(*str - '0');
                        if( (minus == 0 && ret < 0x80000000) ||
                            (minus == -1 && ret > 0x7FFFFFFF) ){
                                ret = -1;
                                break;
                        }
                        ++str;
                }else{
                        ret = -1;
                        break;
                }
        }
        if(*str != '\0')
                return -1;
        return ret;
}
int my_atoi(const char* str){
        int ret = 0;
        int minus = -1;
        if(str == NULL || *str != '\0'){
                if(*str == '+'){
                        ++str;
                }
                if(*str == '-'){
                        ++str;
                        minus = 0;
                }
                if(*str != '\0'){
                        ret = core(str,minus);
                }
                return ret;
        }
}


int main(){
        char test[3] = {'a','b','c'};
        char* test1 = "-100";
        int ret;
        int a =1;
        int b =-1;
        printf("%d %d\n",!a, !b);
        printf("%d\n",sizeof(long long));
        printf("%s\n", test);
        ret = my_atoi((const char*)test1);
        printf("%d\n",ret);
        return 0;
}
