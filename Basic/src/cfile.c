/**
 * @author climatex
 * @date 2023-Sep-15
 * @version 1.0.1
 * @file cfile.c
*/

#include "cfile.h"

char * fread_all(char *fpath)
{
    FILE *fp;
    fp = fopen(fpath, "r");
    if(fp == NULL)
    {
        perror("in func fread_all: fopen failed");
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    int fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *fcontent = (char *)malloc(sizeof(char) * fsize);
    int read_size = fread(fcontent, sizeof(char), fsize, fp);
    if(read_size != fsize)
    {
        perror("in func fread_all: readed size is not equal to expected size\n");
        printf("read %d bytes, expected %d bytes\n", read_size, fsize);
    }
    
    return fcontent;
}

void fwrite_all(char *fpath, char *data)
{
    FILE *fp;
    fp = fopen(fpath, "w");
    if(fp == NULL)
    {
        perror("in func fwrite_all: fopen failed");
        return;
    }

    int fsize = strlen(data);
    int write_size = fwrite(data, sizeof(char), fsize, fp);
    if(fsize != write_size)
    {
        perror("in func fwrite_all: writed size is not equal to expected size\n");
        printf("write %d bytes, expected %d bytes\n", write_size, fsize);
    }
}