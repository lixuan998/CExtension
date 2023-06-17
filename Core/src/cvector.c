#include "cvector.h"

CVector * CVectorConstructor()
{
    CVector *_cvector = (CVector*)malloc(sizeof(struct _CVector));
    _cvector->_data_ptr = (void**)malloc(100 * sizeof(void *));
    _cvector->_free_flag_ptr = (int *)malloc(100 * sizeof(int));
    _cvector->_len = 100;
    _cvector->_rear = 0;
    _cvector->push_back = _CVectorPushBack;
    _cvector->pop_back = _CVectorPopBack;
    _cvector->back = _CVectorBack;
    _cvector->pop_front = _CVectorPopFront;
    _cvector->front = _CVectorFront;
    _cvector->at = _CVectorAt;
    return _cvector;
}

void CVectorDestructor(void **_v_cvector, void (*destructor)(void **))
{
    CVector **_cvector = (CVector **)_v_cvector;
    while(((*_cvector)->back(*_cvector)) != NULL) (*_cvector)->pop_back(*_cvector, destructor);
    free((*_cvector)->_data_ptr);
    (*_cvector)->_data_ptr = NULL;
    free(*_cvector);
    *_cvector = NULL;
}

void _CVectorPushBack(CVector *_cvector, void *_data, int free_flag)
{
    int _rest_space = _cvector->_len - _cvector->_rear;
    if(_rest_space <= 0)
    {
        void *_tmp_ptr = realloc(*_cvector->_data_ptr, _cvector->_len + 100);
        void *_tmp_free_ptr = realloc(_cvector->_free_flag_ptr, _cvector->_len + 100);
        if(_tmp_ptr == NULL || _tmp_free_ptr == NULL)
        {
            perror("cvector.c line 19 fail to realloc memory");
            return;
        }
        else
        {
            _cvector->_len += 100;
            *(_cvector->_data_ptr) = _tmp_ptr;
            _cvector->_free_flag_ptr = _tmp_free_ptr;
            _cvector->_free_flag_ptr[_cvector->_rear] = free_flag;
            _cvector->_data_ptr[_cvector->_rear ++] = _data; 
        }
    }
    else
    {
        _cvector->_free_flag_ptr[_cvector->_rear] = free_flag;
        _cvector->_data_ptr[_cvector->_rear ++] = _data; 
    }
    
}

void _CVectorPopBack(CVector *_cvector, void (*destructor)(void **))
{
    if(_cvector->_rear == 0) return;
    else
    {
        if(_cvector->_free_flag_ptr[-- _cvector->_rear] == AUTO_FREE && _cvector->_data_ptr[_cvector->_rear] != NULL)
        {
            if(destructor != NULL) destructor(&(_cvector->_data_ptr[_cvector->_rear]));
            else free(_cvector->_data_ptr[_cvector->_rear]);
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
    if(_cvector->_rear == 0) return;
    else
    {
        if(_cvector->_free_flag_ptr[0] == AUTO_FREE && _cvector->_data_ptr[0] != NULL)
        {
            if(destructor != NULL) destructor(&_cvector->_data_ptr[0]);
            else free(_cvector->_data_ptr[0]);
        }
        for(int i = 1; i < _cvector->_rear; ++ i)
        {
            _cvector->_data_ptr[i - 1] = _cvector->_data_ptr[i];
            _cvector->_free_flag_ptr[i - 1] = _cvector->_free_flag_ptr[i];

        }

        _cvector->_data_ptr[-- _cvector->_rear] = NULL;
    }
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
