/*
 * Coding: GB2312
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 *
 */

#include <stdio.h>

#include "zimo.h"

int main() {
    printf("Hello, World!\n");
    char *str = "中国传媒大学ecdav";

    char buff[32];
    for(int i=0;i<8;i++)
    {
        get_zimo(str+=2, buff);
        print_character(buff);
    }

    return 0;
}