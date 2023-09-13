#include "cchar.h"

CChar * create_cchar(char * data)
{
    CChar *cchar = (CChar *)malloc(sizeof(struct _CChar));
    cchar -> data = data;
    cchar -> len = strlen(data);
    return cchar;
}

int isequal_cchar(CChar * c1, CChar * c2)
{
    int res = strcmp(c1 -> data, c2 -> data);
    if(res == 0) return 1;
    else return -1;
}