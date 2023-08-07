#ifndef __CSTRING_H__
#define __CSTRING_H__

#define CODEX_1 1
#define CODEX_2 2
#define CODEX_3 3
#define CODEX_4 4

#define CODEX_1_MASK 0x80
#define CODEX_1_RESULT 0x0

#define CODEX_2_MASK 0xE0
#define CODEX_2_RESULT 0xC0

#define CODEX_3_MASK 0xF0
#define CODEX_3_RESULT 0xE0

#define CODEX_4_MASK 0xF8
#define CODEX_4_RESULT 0xF0

#include <string.h>
#include "cchar.h"
#include "cvector.h"

typedef struct _CString{
    /**
     * @param _len restore the amount of characters in the string
    */
    int _len;
    /**
     * @param _data A CVector, restores values of type CChar *
    */
    CVector *_data;
    char * (*raw_data)(struct _CString *);
    CChar * (*at)(struct _CString *, int);
    
    void (*append_cchar)(struct _CString *, CChar *);
    void (*append_c_char)(struct _CString *, char *, int);
    void (*append_cstring)(struct _CString *, struct _CString *);
    void (*append_c_string)(struct _CString *, char *);
    struct _CString *(*substr)(struct _CString *, int, int);
    

    CVector * (*split)(struct _CString *, CChar *);
} CString;

CString * CStringConstructor(char * __data);
void CStringDestructor(void ** _v_cstring);
char * _CStringRawData(CString * _cstring);
CChar * _CStringAt(CString * _cstring, int _index);
void _CStringAppendCChar(CString * _cstring, CChar * _cchar);
void _CStringAppendChar(CString *_cstring, char *_c_string, int _copy_flag);
void _CStringAppendCString(CString *_cstring, CString *_append_cstring);
void _CStringAppendString(CString *_cstring, char *_append_c_string);

CString * _CStringSubStr(CString * _cstring, int _begin, int _end);

CVector * _CStringSplit(CString * _cstring, CChar * _cchar);


#endif