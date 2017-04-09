/*
 * Coding: UTF-8
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bmp.h"

// RGB_555
int create_bmp_file(int width, int height, BITMAP_S **Bitmap)
{
    BITMAP_S *pstBitmap =  (BITMAP_S *)malloc(sizeof(BITMAP_S));
    if (pstBitmap == NULL)
    {
        printf("malloc pstBitmap error.");
        return 1;
    }
    memset(pstBitmap, 0, sizeof(BITMAP_S));

    pstBitmap->bfHeader.bfType[0] = 'B';
    pstBitmap->bfHeader.bfType[1] = 'M';
    pstBitmap->bfHeader.bfOffbits = 54; /* 14(BFS_S) +  40(BIH_S)*/

    pstBitmap->biHeader.biSize = 40;
    pstBitmap->biHeader.biWidth  = width;
    pstBitmap->biHeader.biHeight = height;
    pstBitmap->biHeader.biPlanes = 1;
    pstBitmap->biHeader.biBitCount = 16;    /* RGB_555 */

    int n_bytes_per_row = (width * (pstBitmap->biHeader.biBitCount) + 7) >> 3;
    int pad_bytes_per_row = (4 - n_bytes_per_row) & 3;
    pstBitmap->biHeader. biSizeImage = height * (pad_bytes_per_row + n_bytes_per_row);
    pstBitmap->bfHeader.bfSize = pstBitmap->biHeader. biSizeImage + pstBitmap->bfHeader.bfOffbits;

    pstBitmap->bmpData = (uint8_t*)malloc((size_t) (pstBitmap->biHeader. biSizeImage));  /*include padding data*/
//    pstBitmap->bmpData = (uint8_t*)malloc(sizeof(uint8_t) * (width * height * pstBitmap->biHeader.biBitCount / 8));
    if (pstBitmap->bmpData == NULL)
    {
        printf("malloc bmpData error.");
        return 1;
    }
    memset(pstBitmap->bmpData, 0, sizeof(uint8_t)*(pstBitmap->biHeader. biSizeImage));
    *Bitmap = pstBitmap;
    return 0;
}

int write_bmp_file(BITMAP_S *pstBitmap, char *file)
{
    FILE *fd;
    if((fd = fopen(file, "wb")) == NULL)
    {
        printf("Can't open font file!");
    }

    fwrite(pstBitmap, sizeof(char), (size_t) pstBitmap->bfHeader.bfOffbits, fd);
    fwrite(pstBitmap->bmpData, sizeof(char), (size_t) pstBitmap->biHeader. biSizeImage, fd);
    fclose(fd);
    return 0;
}