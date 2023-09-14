/**
 * @author climatex
 * @date 2023-Sep-11
 * @version 1.0.1
 * @file cstring.h
*/

#ifndef __CSTRING_H__
#define __CSTRING_H__

//charset encoding definitions
#define ENCODING_1          1
#define ENCODING_2          2
#define ENCODING_3          3
#define ENCODING_4          4

#define ENCODING_1_MASK     0x80
#define ENCODING_1_RESULT   0x0

#define ENCODING_2_MASK     0xE0
#define ENCODING_2_RESULT   0xC0

#define ENCODING_3_MASK     0xF0
#define ENCODING_3_RESULT   0xE0

#define ENCODING_4_MASK     0xF8
#define ENCODING_4_RESULT   0xF0

#define INIT_CSTRING_LEN            100

//status codes
#define SUCCESS             0
#define NULL_PTR            -1
#define REALLOC_FAIL        -2
#define MALLOC_FAIL         -3    
#define UNKNOWN_WORD        -4

#include <string.h>
#include "cchar.h"

typedef struct _CString{
    int len;
    CChar **data;
} CString;

CString * create_cstring(char *data);
CString * append_cstring(CString * cstring, char *append_str);
char * raw_cstring(CString * cstring);
CString * substr_cstring(CString *origin, int from, int length);

#endif  //  __CSTRING_H__