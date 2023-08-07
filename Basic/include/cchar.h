#ifndef __CCHAR_H__
#define __CCHAR_H__

#define WITH_COPY 1
#define WITHOUT_COPY 0

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _CChar{
    int _len;
    char * _data_ptr;
    char * (*raw_data)(struct _CChar *);
    int (*equal)(struct _CChar *, struct _CChar *);
} CChar;

CChar *CCharConstructor(char * __data, int _copy_flag);
void CCharDestructor(void ** _v_cchar);
char * _CCharRawData(CChar * _cchar);
int _CCharEqual(CChar * _cchar_1, CChar * _cchar_2);

#endif