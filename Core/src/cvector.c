#include "cvector.h"

CVector * CVectorConstructor()
{
    CVector *_cvector = (CVector*)malloc(sizeof(struct _CVector));
    _cvector->data_ptr = (void**)malloc(100 * sizeof(void *));
    _cvector->_len = 100;
    _cvector->_rear = 0;

    return _cvector;
}

void PushBack(CVector *_cvector, void *_data)
{
    int _rest_space = _cvector->_len - _cvector->_rear;
    if(_rest_space <= 0)
    {
        void *_tmp_ptr = realloc(*_cvector->data_ptr, _cvector->_len + 100);
        if(_tmp_ptr == NULL)
        {
            perror("cvector.c line 19 fail to realloc memory");
            return;
        }
        else
        {
            _cvector->_len += 100;
            *_cvector->data_ptr = _tmp_ptr;
            _cvector->data_ptr[_cvector->_rear ++] = _data; 
        }
    }
    else
    {
        _cvector->data_ptr[_cvector->_rear ++] = _data; 
    }
    
}

void PopBack(CVector *_cvector)
{
    if(_cvector->_rear == 0) return;
    else
    {
        free(_cvector->data_ptr[--_cvector->_rear]);
        _cvector->data_ptr[_cvector->_rear] = NULL;
    }
}

void * Back(CVector *_cvector)
{
    if(_cvector->_rear == 0) return NULL;
    else
    {
        return _cvector->data_ptr[_cvector->_rear - 1];
    }
}

void PopFront(CVector *_cvector)
{
    if(_cvector->_rear == 0) return;
    else
    {
        void *_tmp_ptr = _cvector->data_ptr[0];
        for(int i = 1; i < _cvector->_rear; ++ i)
        {
            _cvector->data_ptr[i - 1] = _cvector->data_ptr[i];
        }
        free(_tmp_ptr);
        _cvector->data_ptr[-- _cvector->_rear] = NULL;
    }
}

void * Front(CVector *_cvector)
{
    if(_cvector->_rear == 0) return NULL;
    else return _cvector->data_ptr[0];
}

void * At(CVector *_cvector, int _index)
{
    if(_index >= _cvector->_rear) return NULL;
    else
    {
        return _cvector->data_ptr[_index];
    }
}
