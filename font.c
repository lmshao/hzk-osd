/*
 * Coding: UTF-8
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 *
 */

#include "font.h"
#include "bmp.h"


void get_zimo(char *str, char *buff)
{
    char *p = buff;
    int len = strlen(str);
    int image_width = len * 16;
    int image_height = 16;
    printf("Length of String:%d\n%s",len, str);
    printf("W:H =%dx%d", image_width, image_height);

//    get_hzk_code((unsigned char*)str, buff);
    BITMAP_S *bmp;
    create_bmp_file(image_width, image_height, &bmp);
    printf("Size:%d\r",bmp->biHeader.biSizeImage);

    for(int i=0; i<len; i++)
    {
        if( str[i] & 0x80)  //汉字
        {
            printf("H");
            i++;
        }
        else    // ASCII字符
        {
            printf("z");
        }
    }
}

void get_hzk_code(unsigned char *c, char buff[])
{
    FILE *HZK;
    if((HZK = fopen("./font/hzk16s", "rb")) == NULL)
    {
        printf("Can't open font file!");
    }

    int hv = *c - 0xa1;
    int lv = *(c+1) - 0xa1;
    long offset = (long) (94 * hv + lv) * 32;

    fseek(HZK, offset, SEEK_SET);
    fread(buff, 32, 1, HZK);
    fclose(HZK);
}

/* unsigned char buffer[32]; */
void print_character(char buff[])
{
    int i, j, k;

    printf("\n");
    for(k=0; k<16; k++){    /* 16*16 pixels */
        for(j=0; j<2; j++){     /* 2 bytes */
            for(i=0; i<8; i++){     /* 8 bits */
                int flag = buff[k*2+j]&(0x80 >> i);
                printf("%s", flag?".":" ");
            }
        }
        printf("\n");
    }
}
