#include <stdio.h>

#include "zimo.h"

int main() {
    printf("Hello, World!\n");
    char *str = "我中国传媒大学ecdav";

    char buff[32];
    for(int i=0;i<6;i++)
    {
        get_zimo(str+=2, buff);
        print_character(buff);
    }
    
    return 0;
}