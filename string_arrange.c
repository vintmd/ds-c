#include <iostream>
//
int change(char* str, char* begin){
        if(*begin == '\0'){
                printf("%s\n",str);
        }
        char* ch = begin;
        for( ;(*ch) != '\0';++ch){
                char tmp = *ch;
                *ch = *begin;
                *begin = tmp;

                change(str, begin+1);

                tmp = *ch;
                *ch = *begin;
                *begin = tmp;

        }
        return 0;

}
int full_arrange(char* str){
        if(str == NULL)
                return -1;
        return change(str, str);
}
