/*
 * Coding: UTF-8
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 *
 */

#include "font.h"
#include "bmp.h"
#include "mask.h"

void str_to_bmp(unsigned char *str, char *bmp_file)
{

    int len = strlen((const char *) str);
    int image_width = len * 8;
    int image_height = 16;

    printf("String: \"%s\"\n", str);
    printf("Generate bmp: %s\n", bmp_file);


    BITMAP_S *bmp;
    create_bmp_file(image_width, image_height, &bmp);
    printf("Size of bmp: %d Bytes\n",(*bmp).bfHeader.bfSize);

    for(int i=0; i<len; i++)
    {
        if( str[i] & 0x80)  //汉字
        {
            unsigned char character[32];
            get_hzk_code(str+i, character);

            fill_pixels( (*bmp).bmpData, character, 0, i, len);
            i++;
        }
        else    // ASCII字符
        {
            unsigned char character[16];
            memcpy(character, &ascii_mask[(str[i]-0x1f)*16], 16);

            fill_pixels( (*bmp).bmpData, character, 1, i, len);
        }
    }
    write_bmp_file(bmp,bmp_file);
}

void fill_pixels(unsigned char *bmp_data, unsigned char *font_data,
                 int type, int seq, int bmp_width)
{
    unsigned char *pixel = bmp_data;
    if(!type){
        int col, j, row, m=0;
        for(row=0; row<16; row++) {    /* 16*16 pixels */
            for (j = 0; j < 2; j++) {     /* 2 bytes */
                for (col = 0; col < 8; col++) {     /* 8 bits */
                    if (font_data[row * 2 + j] & (0x80 >> col)) {
                        pixel[(col + (seq + j) * 8 + (15 - row) * 8 * bmp_width) * 2] = 0x7c;
                        pixel[(col + (seq + j) * 8 + (15 - row) * 8 * bmp_width) * 2 + 1] = 0x00;
                    } else {
                        pixel[(col + (seq + j) * 8 + (15 - row) * 8 * bmp_width) * 2] = 0xff;
                        pixel[(col + (seq + j) * 8 + (15 - row) * 8 * bmp_width) * 2 + 1] = 0xff;
                    }
                }
            }
        }

    }else{
        int col, j, row;
        for(row=0; row<16; row++)
        {    /* 16*16 pixels */
            for (col = 0; col < 8; col++) {     /* 8 bits */
                if (font_data[row] & (0x80 >> col)) {
                    pixel[(col + seq * 8 + (15 - row) * 8 * bmp_width) * 2] = 0x7c;
                    pixel[(col + seq * 8 + (15 - row) * 8 * bmp_width) * 2 + 1] = 0x00;
                } else {
                    pixel[(col + seq * 8 + (15 - row) * 8 * bmp_width) * 2] = 0xff;
                    pixel[(col + seq * 8 + (15 - row) * 8 * bmp_width) * 2 + 1] = 0xff;
                }
            }
        }
    }
}


void get_hzk_code(unsigned char *c, unsigned char buff[])
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
