/**
 * @author climatex
 * @date 2023-Sep-11
 * @version 1.0.1
 * @file cchar.h
*/

#ifndef __CCHAR_H__
#define __CCHAR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _CChar{
    int len;
    char * data;
} CChar;

CChar * create_cchar(char * data);
int isequal_cchar(CChar * c1, CChar * c2);

#ifdef __cplusplus
}
#endif

#endif