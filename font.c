/*
 * Coding: UTF-8
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 *
 */

#include <stdlib.h>
#include "font.h"
#include "bmp.h"
#include "mask.h"

void str_to_bmp(unsigned char *str, char *bmp_file)
{
    int len = strlen((const char *) str);
    int image_width = len * 8;
    int image_height = 16;

    printf("String: \"%s\"\n", str);
    printf("Generate bmp file: %s\n", bmp_file);

    BITMAP_S *bmp;
    create_bmp_file(image_width, image_height, &bmp);
    printf("Size of bmp: %d Bytes\n",(*bmp).bfHeader.bfSize);

    for(int i=0; i<len; i++) {
        if(str[i] & 0x80) {     /* Chinese character */
            unsigned char character[32];
            get_hzk_code(str+i, character);
            fill_pixels( (*bmp).bmpData, character, 0, i, len);
            i++;
        } else {    /* ASCII character */
            unsigned char character[16];

            if(str[i]<0x20) {
                memcpy(character, ascii_mask, 16);
            } else{
                memcpy(character, &ascii_mask[(str[i]-0x1f)*16], 16);
            }

            fill_pixels( (*bmp).bmpData, character, 1, i, len);
        }
    }
    write_bmp_file(bmp, bmp_file);
    printf("Save bmp file successfully!\n");
    free(bmp->bmpData);
    free(bmp);
}

void fill_pixels(unsigned char *bmp_data, unsigned char *font_data,
                 int type, int seq, int bmp_width)
{
    unsigned char *pixel = bmp_data;
    if(!type) {     /* Chinese character */
        int col, i, row;
        for(row=0; row<16; row++) {
            for (i = 0; i < 2; i++) { /* 2 bytes */
                for (col = 0; col < 8; col++) { /* 8 bits */
                    int pos = (15 - row) * 8 * bmp_width + (seq + i) * 8 + col;
                    if (font_data[row * 2 + i] & (0x80 >> col)) {
                        pixel[pos * 2] = 0x7c;
                        pixel[pos * 2 + 1] = 0x00;
                    } else {
                        pixel[pos * 2] = 0xff;
                        pixel[pos * 2 + 1] = 0xff;
                    }
                }
            }
        }
    } else {
        int col, row;
        for(row=0; row<16; row++) {
            for (col = 0; col < 8; col++) {     /* 8 bits */
                int pos = (15 - row) * 8 * bmp_width + seq * 8 + col;
                if (font_data[row] & (0x80 >> col)) {
                    pixel[pos * 2] = 0x7c;
                    pixel[pos * 2 + 1] = 0x00;
                } else {
                    pixel[pos * 2] = 0xff;
                    pixel[pos * 2 + 1] = 0xff;
                }
            }
        }
    }
}


void get_hzk_code(unsigned char *c, unsigned char buff[])
{
    FILE *HZK;
    if((HZK = fopen("./font/hzk16s", "rb")) == NULL) {
        printf("Can't open font file!");
    }

    int hv = *c - 0xa1;
    int lv = *(c+1) - 0xa1;
    long offset = (long) (94 * hv + lv) * 32;

    fseek(HZK, offset, SEEK_SET);
    fread(buff, 32, 1, HZK);
    fclose(HZK);
}
