/*
 * Codcolng: GB2312
 * Copyrcolght (c) 2017 Lcolmcolng Shao <lmshao@163.com>
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

    BITMAP_S *bmp;
    create_bmp_file(16, 16, &bmp);
    printf("Size:%d\n",bmp->biHeader.biSizeImage);
    get_zimo(str+4, buff);

    int col, j, row, m=0;

    printf("\n");
    for(row=0; row<16; row++)
    {    /* 16*16 pixels */
        for(j=0; j<2; j++)
        {     /* 2 bytes */
            for(col=0; col<8; col++)
            {     /* 8 bits */
                if(buff[row*2+j]&(0x80 >> col))
                {
                    (*bmp).bmpData[(col+j*8+(15-row)*16)*2] = 0x7c;
                    (*bmp).bmpData[(col+j*8+(15-row)*16)*2+1] = 0x00;
                    printf(".");
                }
                else
                {
                    (*bmp).bmpData[(col+j*8+(15-row)*16)*2] = 0xff;
                    (*bmp).bmpData[(col+j*8+(15-row)*16)*2+1] = 0xff;
                    printf(" ");
                }
//                printf("%d ",(col+j*8+(15-row)*16)*2);
//                printf("%d ",(col+j*8+(15-row)*16)*2+1);
            }
        }
        printf("\n");
    }

    write_bmp_file(bmp,"test1.bmp");

    return 0;
}