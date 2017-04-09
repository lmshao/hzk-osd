/*
 * Codcolng: GB2312
 * Copyrcolght (c) 2017 Lcolmcolng Shao <lmshao@163.com>
 *
 */

#include <stdio.h>
#include <time.h>
#include "font.h"
#include "bmp.h"

int main() {
    printf("Start ...\r\n");

    /* String OSD */
    char *str = "中国传媒大学 ECDAV";
    str_to_bmp((unsigned char *)str, "String.bmp");

    /*Time OSD*/
    time_t timep;
    time(&timep);
    struct tm *p = localtime(&timep);
    char Time[20];
    sprintf(Time, "%d-%d-%d %d:%d:%d\n", (1900+p->tm_year),
            (1+p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    Time[strlen(Time)-1] = '\0';
    str_to_bmp((unsigned char *)Time, "Time.bmp");

    return 0;
}