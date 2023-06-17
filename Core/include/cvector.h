#ifndef __C_VECTOR__
#define __C_VECTOR__

#define AUTO_FREE 1
#define MANUAL_FREE 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _CVector{
    int _len;
    int _rear;
    void **_data_ptr;
    int *_free_flag_ptr;
    void (*push_back)(struct _CVector *, void *, int);
    void (*pop_back)(struct _CVector *, void (*)(void **));
    void * (*back)(struct _CVector *);
    void (*pop_front)(struct _CVector *, void (*)(void **));
    void * (*front)(struct _CVector *);
    void * (*at)(struct _CVector *, int);
} CVector;

CVector * CVectorConstructor();
void CVectorDestructor(void **_v_cvector, void (*destructor)(void **));
void _CVectorPushBack(CVector *_cvector, void *_data, int free_flag);
void _CVectorPopBack(CVector *_cvector, void (*destructor)(void **));
void * _CVectorBack(CVector *_cvector);
void _CVectorPopFront(CVector *_cvector, void (*destructor)(void **));
void * _CVectorFront(CVector *_cvector);
void * _CVectorAt(CVector *_cvector, int _index);

#endif