#ifndef __CSTRING_H__
#define __CSTRING_H__

#include <string.h>

typedef struct _CString{
    char *data;
    
} CString;

CString * CStringConstructor(const char * data);

#endif