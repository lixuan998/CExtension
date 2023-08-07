#include "cvector.h"

CVector * CVectorConstructor()
{
    CVector *_cvector = (CVector*)malloc(sizeof(struct _CVector));
    _cvector->_data_ptr = (void**)malloc(100 * sizeof(void *));
    _cvector->_type_ptr = (DATA_TYPE *)malloc(100 * sizeof(int));
    _cvector->_len = 100;
    _cvector->_rear = 0;
    _cvector->PushBack = _CVectorPushBack;
    _cvector->PopBack = _CVectorPopBack;
    _cvector->Back = _CVectorBack;
    _cvector->PopFront = _CVectorPopFront;
    _cvector->Front = _CVectorFront;
    _cvector->At = _CVectorAt;

    _cvector->Destructor = CVectorDestructor;
    return _cvector;
}

void CVectorDestructor(void **_v_cvector)
{
    CVector **_cvector = (CVector **)_v_cvector;
    while(((*_cvector)->Back(*_cvector)) != NULL)
        (*_cvector)->PopBack(*_cvector);
    free((*_cvector)->_data_ptr);
    (*_cvector)->_data_ptr = NULL;
    free(*_cvector);
    *_cvector = NULL;
}

void _CVectorPushBack(CVector *_cvector,
                      void *_data,
                      DATA_TYPE _data_type)
{
    void *_new_data_ptr;
    int _rest_space = _cvector->_len - _cvector->_rear;
    if(_rest_space <= 0)
    {
        void *_tmp_data_ptr = realloc(*_cvector->_data_ptr, _cvector->_len + 100);
        void *_tmp_type_ptr = realloc(_cvector->_type_ptr, _cvector->_len + 100);
        if(_tmp_data_ptr == NULL || _tmp_type_ptr == NULL)
        {
            perror("cvector.c line 44 fail to realloc memory");
            return;
        }
        else
        {
            _cvector->_len += 100;
            *(_cvector->_data_ptr) = _tmp_data_ptr;
            _cvector->_type_ptr = _tmp_type_ptr; 
        }
    }
    _new_data_ptr = malloc(sizeof(*_data));
    memcpy(_new_data_ptr, _data, sizeof(*_data));
    _cvector->_type_ptr[_cvector->_rear] = _data_type;
    _cvector->_data_ptr[_cvector->_rear ++] = _new_data_ptr; 
    
}

void _CVectorPopBack(CVector *_cvector)
{
    if(_cvector->_rear == 0)
    {
        return;
    }
    _cvector->_rear -= 1;

    if(_cvector->_data_ptr[_cvector->_rear] == NULL)
    {
        return;
    }
    else
    {
        DATA_TYPE _data_type = _cvector->_type_ptr[_cvector->_rear];
        if(_cvector->_type_ptr[-- _cvector->_rear] == DATA_TYPE_BASIC)
        {
            free(_cvector->_data_ptr[_cvector->_rear]);
        }
        else
        {
            switch(_data_type)
            {
                case DATA_TYPE_CCHAR :
                {
                    CChar *_tmp_cchar
                }
            }
            (CUR_DATA_TYPE(_data_type(_cvector->_data_ptr[_cvector->_rear]))->Destructor(&(_cvector->_data_ptr + _cvector->_rear));
        }
        _cvector->_data_ptr[_cvector->_rear] = NULL;
    }
}

void * _CVectorBack(CVector *_cvector)
{
    if(_cvector->_rear == 0) return NULL;
    else
    {
        return _cvector->_data_ptr[_cvector->_rear - 1];
    }
}

void _CVectorPopFront(CVector *_cvector, void (*destructor)(void **))
{
    // if(_cvector->_rear == 0) return;
    // else
    // {
    //     if(_cvector->_free_flag_ptr[0] == AUTO_FREE && _cvector->_data_ptr[0] != NULL)
    //     {
    //         if(destructor != NULL) destructor(&_cvector->_data_ptr[0]);
    //         else free(_cvector->_data_ptr[0]);
    //     }
    //     for(int i = 1; i < _cvector->_rear; ++ i)
    //     {
    //         _cvector->_data_ptr[i - 1] = _cvector->_data_ptr[i];
    //         _cvector->_free_flag_ptr[i - 1] = _cvector->_free_flag_ptr[i];

    //     }

    //     _cvector->_data_ptr[-- _cvector->_rear] = NULL;
    // }
}

void * _CVectorFront(CVector *_cvector)
{
    if(_cvector->_rear == 0) return NULL;
    else return _cvector->_data_ptr[0];
}

void * _CVectorAt(CVector *_cvector, int _index)
{
    if(_index >= _cvector->_rear) return NULL;
    else
    {
        return _cvector->_data_ptr[_index];
    }
}
