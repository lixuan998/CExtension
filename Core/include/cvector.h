#ifndef __C_VECTOR__
#define __C_VECTOR__

typedef struct _CVector{
    void *data_ptr;
    void (*PushBack)(void *data);
} CVector;

void *(_PushBack)(void *data);

#endif