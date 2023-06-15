#ifndef __C_VECTOR__
#define __C_VECTOR__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _CVector{
    int _len;
    int _rear;
    void **data_ptr;
} CVector;

CVector * CVectorConstructor();
void PushBack(CVector *_cvector, void *_data);
void PopBack(CVector *_cvector);
void * Back(CVector *_cvector);
void PopFront(CVector *_cvector);
void * Front(CVector *_cvector);
void * At(CVector *_cvector, int _index);

#endif