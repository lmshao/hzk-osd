cmake_minimum_required(VERSION 3.6)
project(hzk_osd)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c zimo.c zimo.h mask.c mask.h bmp.c bmp.h)
add_executable(hzk_osd ${SOURCE_FILES})