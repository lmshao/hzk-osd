/*
 * Coding: UTF-8
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 *
 */

#ifndef HZK_OSD_BMP_H
#define HZK_OSD_BMP_H

#include <stdint.h>
#pragma pack(2)

/* Bitmap File Header 14 Bytes*/
typedef struct BitmapFileHeader
{
    int8_t bfType[2];       /* "BM" */
    int32_t bfSize;         /* Bitmap size =  */
    uint16_t bfReserved1;   /* 0x00 */
    uint16_t bfReserved2;   /* 0x00 */
    int32_t bfOffbits;      /* Offset where the bitmap data can be found */
}BFH_S;

/* Windows V3: 40 Bytes */
typedef struct BitmapInfoHeader
{
    int32_t biSize;     /* BIH size: 0x28 */
    int32_t biWidth;    /* Bitmap's width */
    int32_t biHeight;   /* Bitmap's height */
    int16_t biPlanes;   /*0x01*/
    int16_t biBitCount; /*1,4,8,16,32*/
    int32_t biCompression;  /* 0-RGB, 1-BLE8, 2-RLE4 */
    int32_t biSizeImage;    /* RGB: 0 */
    int32_t biXpelsPerMeter;    /*default: 0*/
    int32_t biYpelsPerMeter;    /*default: 0*/
    int32_t biClrUsed;       /*default: 0*/
    int32_t biClrImportant;  /*default: 0*/
}BIH_S;

typedef struct BITMAP_S
{
    BFH_S   bfHeader;
    BIH_S   biHeader;
    uint8_t *bmpData;                /* Address of Bitmap's data */
}BITMAP_S;

#pragma pack()

/*
 * @param width: input
 * @param height: input
 * @param pstBitmap: output
 */
int create_bmp_file(int width, int height, BITMAP_S **pstBitmap);

int write_bmp_file(BITMAP_S *pstBitmap, char *file);

/* generate RGB555 example bitmap */
void gen_test_rgb();

#endif //HZK_OSD_BMP_H
