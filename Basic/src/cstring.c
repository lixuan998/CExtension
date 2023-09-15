/**
 * @author climatex
 * @date 2023-Sep-11
 * @version 1.0.1
 * @file cstring.c
*/

#include "cstring.h"

CString * create_cstring(char *data)
{
    CString *cstring = (CString *)malloc(sizeof(struct _CString));
    if(cstring == NULL)
    {
        perror("in func \"create_cstring\": cstring malloc failed");
        return NULL;
    }
    cstring -> len = 0;
    cstring -> data = (CChar **)malloc(sizeof(struct _CChar *) * INIT_CSTRING_LEN);
    if(cstring -> data == NULL)
    {
        perror("in func \"create_cstring\": cstring -> data malloc failed");
        return NULL;
    }
    append_cstring(cstring, data);
    if(cstring == NULL)
    {
        perror("in func \"create_cstring\": append_cstring failed");
        free(cstring -> data);
        free(cstring);
        cstring = NULL;
    }
    return cstring;
}

void append_cstring(CString * cstring, char *append_str)
{
    if(append_str == NULL)
    {
        return;
    }
    if(cstring == NULL)
    {
        perror("in func \"append_cstring\": cstring is null");
        return;
    }
    char *word;
    while((*append_str) != '\0')
    {
        word = NULL;
        if(cstring -> len % INIT_CSTRING_LEN == 0 && cstring -> len != 0)
        {
            cstring -> data = (CChar **)realloc(cstring -> data, (cstring -> len + INIT_CSTRING_LEN) * sizeof(struct _CChar *));
            if(cstring -> data == NULL)
            {
                perror("in func \"append_cstring\": realloc failed");
                return;
            }
        }
        if(((*append_str) & ENCODING_1_MASK) == ENCODING_1_RESULT)
        {
            word = (char *)malloc(sizeof(char) * 2);
            if(word == NULL)
            {
                perror("in func \"append_cstring\": malloc failed");
                return;
            }
            memcpy(word, append_str, 1 * sizeof(char));
            word[1] = '\0';
            append_str += 1;
        }
        else if(((*append_str) & ENCODING_2_MASK) == ENCODING_2_RESULT)
        {
            word = (char *)malloc(sizeof(char) * 3);
            if(word == NULL)
            {
                perror("in func \"append_cstring\": malloc failed");
                return;
            }
            memcpy(word, append_str, 2 * sizeof(char));
            word[2] = '\0';
            append_str += 2;
        }
        else if(((*append_str) & ENCODING_3_MASK) == ENCODING_3_RESULT)
        {
            word = (char *)malloc(sizeof(char) * 4);
            if(word == NULL)
            {
                perror("in func \"append_cstring\": malloc failed");
                return;
            }
            memcpy(word, append_str, 3 * sizeof(char));
            word[3] = '\0';
            append_str += 3;
        }
        else if(((*append_str) & ENCODING_4_MASK) == ENCODING_4_RESULT)
        {
            word = (char *)malloc(sizeof(char) * 5);
            if(word == NULL)
            {
                perror("in func \"append_cstring\": malloc failed");
                return;
            }
            memcpy(word, append_str, 4 * sizeof(char));
            word[4] = '\0';
            append_str += 4;
        }
        else
        {
            perror("in func \"append_cstring\": unknown encoding type");
            return;
        }
        cstring -> data[cstring -> len ++] = create_cchar(word);
    }
    return;
}

char * raw_cstring(CString * cstring)
{
    int data_len = 1;
    for(int i = 0; i < cstring -> len; i++)
    {
        CChar *cchar = cstring -> data[i];
        data_len += cchar -> len;
    }
    char *raw_data = (char *)malloc(sizeof(char) * data_len);
    char *ptr = raw_data;
    for(int i = 0; i < cstring -> len; ++ i)
    {
        CChar *cchar = cstring -> data[i];
        memcpy(ptr, cchar -> data, cchar -> len * sizeof(char));
        ptr += cchar -> len;
    }
    raw_data[data_len] = '\0';
    return raw_data;
}

CString * substr_cstring(CString *origin, int from, int length)
{
    char *substr_data;
    int data_len = 1;
    for(int i = from; i < from + length; ++ i)
    {
        CChar *cchar = origin -> data[i];
        data_len += cchar -> len;
    }

    substr_data = (char *)malloc(sizeof(char) * data_len);
    char *ptr = substr_data;
    for(int i = from; i < from + length; ++ i)
    {
        CChar *cchar = origin -> data[i];
        memcpy(ptr, cchar -> data, cchar -> len * sizeof(char));
        ptr += cchar -> len;
    }
    substr_data[data_len] = '\0';
    CString * substr = create_cstring(substr_data);
    return substr;
}
