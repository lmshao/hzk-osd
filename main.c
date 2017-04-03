/*
 * Coding: GB2312
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "zimo.h"
#include "bmp.h"

int main() {
    printf("Hello, World!\n");
    char *str = "中国传媒大学ecdav";

    char buff[32];
    for(int i=0;i<4;i+=2)
    {
        get_zimo(str+i, buff);
        print_character(buff);
    }

    gen_test_rgb();

    return 0;
}