/*
 * Coding: UTF-8
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 *
 */

#ifndef HZK_OSD_ZIMO_H
#define HZK_OSD_ZIMO_H

#include<stdio.h>
#include <string.h>

void get_zimo(char *str, char *buffer);

/*
 *
 */
void get_hzk_code(unsigned char *c, char buff[]);

void print_character(char buff[]);

#endif //HZK_OSD_ZIMO_H