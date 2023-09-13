#ifndef __CCHAR_H__
#define __CCHAR_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _CChar{
    int len;
    char * data;
} CChar;

CChar * create_cchar(char * data);
int isequal_cchar(CChar * c1, CChar * c2);

#endif