#ifndef __C_VECTOR__
#define __C_VECTOR__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_types.h"

typedef struct _CVector{
    int _len;
    int _rear;
    void **_data_ptr;
    int *_type_ptr;

    void    (*Destructor)   (struct _CVector **);

    void    (*PushBack)    (struct _CVector *,
                             UNIVERSAL *,
                             int);

    void    (*PopBack)     (struct _CVector *);

    void *  (*Back)         (struct _CVector *);

    void    (*PopFront)    (struct _CVector *,
                             void (*)(void **));

    void *  (*Front)        (struct _CVector *);

    void *  (*At)           (struct _CVector *,
                             int);
} CVector;

CVector * CVectorConstructor();
void CVectorDestructor(void **_v_cvector);

void _CVectorPushBack(CVector *_cvector,
                      void *_data,
                      DATA_TYPE _data_type);

void _CVectorPopBack(CVector *_cvector);
void * _CVectorBack(CVector *_cvector);
void _CVectorPopFront(CVector *_cvector, void (*destructor)(void **));
void * _CVectorFront(CVector *_cvector);
void * _CVectorAt(CVector *_cvector, int _index);

#endif