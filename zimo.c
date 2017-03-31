#include "zimo.h"

void get_zimo(char *str, char *buffer)
{

}

void get_hzk_code(unsigned char *c, char buff[])
{
    FILE *HZK;
    if((HZK = fopen("/font/hzk16s", "rb")) == NULL)
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
    unsigned char key[8] = {
            0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
    };

    printf("\n");
    for(k=0; k<16; k++){
        for(j=0; j<2; j++){
            for(i=0; i<8; i++){
                int flag = buff[k*2+j]&key[i];
                printf("%s", flag?"●":"○");
            }
        }
        printf("\n");
    }
}
