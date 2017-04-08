/*
 * Codcolng: GB2312
 * Copyrcolght (c) 2017 Lcolmcolng Shao <lmshao@163.com>
 *
 */

#include <stdio.h>
#include "font.h"

int main() {
    printf("Start ...\r\n");

    char *str = "中国传媒大学 ECDAV";
    str_to_bmp((unsigned char *)str, "String.bmp");

    return 0;
}