#include "cchar.h"

CChar *CCharConstructor(char * __data, int _copy_flag)
{
    CChar * _cchar = (CChar *)malloc(sizeof(struct _CChar));
    if(_copy_flag == WITH_COPY)
    {
        _cchar->_data_ptr = (char *)malloc(sizeof(char) * 5);
        strcpy(_cchar->_data_ptr, __data);
    }
    else _cchar->_data_ptr = __data;
    _cchar->_len = 0;
    while(1)
    {
        if((*__data) == '\0') break;
        _cchar->_len ++;
        __data ++;
    }

    _cchar->raw_data = _CCharRawData;
    _cchar->equal = _CCharEqual;
    return _cchar;
}

void CCharDestructor(void ** _v_cchar)
{
    CChar ** _cchar = (CChar **)(_v_cchar);
    free((*_cchar)->_data_ptr);
    (*_cchar)->_data_ptr = NULL;
    (*_cchar) = NULL;
}

char * _CCharRawData(CChar * _cchar)
{
    char * __data = (char *)malloc(sizeof(char) * 5);
    memcpy(__data, _cchar->_data_ptr, _cchar->_len);
    __data[_cchar->_len] = '\0';
    return __data;
}

int _CCharEqual(CChar * _cchar_1, CChar * _cchar_2)
{
    int res = strcmp(_cchar_1->_data_ptr, _cchar_2->_data_ptr);
    if(res == 0) return 1;
    else return 0;
}