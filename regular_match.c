#include <stdio.h>
/*

  the string regular expression to match
  return: 0 matched -1 failed

 */
int core(char* str, char* pattern){
        if(*str == '\0' && *pattern == '\0'){
                return 0;
        }
        if(*str != '\0' && *pattern == '\0')
                return -1;

        //whether the second char is *
        if(*(pattern+1) == '*'){
                if(*str == *pattern || ( *pattern == '.' && *str != '\0') ){
                        return core(str,pattern+2) ||
                                core(str+1,pattern) ||
                                core(str+1,pattern+2);
                }else
                        return core(str,pattern+2);
        }
        //whether same or pattern has the char of .
        if(*str == *pattern || (*str != '\0' && *pattern == '.')){
                return core(str+1,pattern+1);
        }
        return -1;
}

int match(char* str, char* pattern){
        if(str == NULL || pattern == NULL)
                return -1;
        return core(str,pattern);
}


int main(){
        int ret;
        char* str = "aaa";
        char* pat1 = "a.a";
        char* pat2 = "ab*ac*a";
        char* pat3 = "ab*a";
        ret = match(str,pat1);
        printf("%d\n",ret);
        ret = match(str,pat2);
        printf("%d\n",ret);
        ret = match(str,pat3);
        printf("%d\n",ret);
        return 0;

}
