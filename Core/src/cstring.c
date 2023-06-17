#include "cstring.h"

CString * CStringConstructor(char * __data)
{
    CString * _cstring = (CString *)malloc(sizeof(struct _CString));
    _cstring->_data = CVectorConstructor();
    _cstring->_len = 0;
    _cstring->raw_data = _CStringRawData;
    _cstring->at = _CStringAt;
    _cstring->append_cchar =_CStringAppendCChar;
    _cstring->append_c_char =_CStringAppendChar;
    _cstring->append_cstring =_CStringAppendCString;
    _cstring->append_c_string =_CStringAppendString;
    _cstring->substr =_CStringSubStr;
    _cstring->split = _CStringSplit;

    char *_tmp_ptr = __data;

    char *_word;
    CChar *_tmp_cchar;
    while(*_tmp_ptr != '\0')
    {
        if(((*_tmp_ptr) & CODEX_1_MASK) == CODEX_1_RESULT)
        {
            _word = (char *)malloc(sizeof(char) * 2);
            memset(_word, 0, sizeof(char) * 2);
            memcpy(_word, _tmp_ptr, 1);
            _tmp_ptr += 1;
            _tmp_cchar = CCharConstructor(_word, WITHOUT_COPY);
            _cstring->_data->push_back(_cstring->_data, _tmp_cchar, AUTO_FREE);
            _cstring->_len ++;
        }
        else if(((*_tmp_ptr) & CODEX_2_MASK) == CODEX_2_RESULT)
        {
            _word = (char *)malloc(sizeof(char) * 3);
            memset(_word, 0, sizeof(char) * 3);
            memcpy(_word, _tmp_ptr, 2);
            _tmp_ptr += 2;
            _tmp_cchar = CCharConstructor(_word, WITHOUT_COPY);
            _cstring->_data->push_back(_cstring->_data, _tmp_cchar, AUTO_FREE);
            _cstring->_len ++;
        }
        else if(((*_tmp_ptr) & CODEX_3_MASK) == CODEX_3_RESULT)
        {
            _word = (char *)malloc(sizeof(char) * 4);
            memset(_word, 0, sizeof(char) * 4);
            memcpy(_word, _tmp_ptr, 3);
            _tmp_ptr += 3;
            _tmp_cchar = CCharConstructor(_word, WITHOUT_COPY);
            _cstring->_data->push_back(_cstring->_data, _tmp_cchar, AUTO_FREE);
            _cstring->_len ++;
        }
        else if(((*_tmp_ptr) & CODEX_4_MASK) == CODEX_4_RESULT)
        {
            _word = (char *)malloc(sizeof(char) * 5);
            memset(_word, 0, sizeof(char) * 5);
            memcpy(_word, _tmp_ptr, 4);
            _tmp_ptr += 4;
            _tmp_cchar = CCharConstructor(_word, WITHOUT_COPY);
            _cstring->_data->push_back(_cstring->_data, _tmp_cchar, AUTO_FREE);
            _cstring->_len ++;
        }
        else
        {
            perror("cstring.c line 48 unrecognized format");
            return NULL;
        }
    }

    _word = (char *)malloc(sizeof(char) * 2);
    memset(_word, 0, sizeof(char) * 2);
    memcpy(_word, "\0", 1);
    _tmp_cchar = CCharConstructor(_word, WITHOUT_COPY);
    _cstring->_data->push_back(_cstring->_data, _tmp_cchar, AUTO_FREE);
    _cstring->_len ++;

    return _cstring;
}

void CStringDestructor(void ** _v_cstring)
{
    CString **_cstring = (CString **)_v_cstring;
    CVectorDestructor((void**)(&((*_cstring)->_data)), CCharDestructor);
    free(*_cstring);
    (*_cstring) = NULL;
}

char * _CStringRawData(CString * _cstring)
{
    char *_raw_data = (char *)malloc(_cstring->_len * sizeof(char) + 1);
    char *_raw_data_ptr = _raw_data;
    
    for(int i = 0; i < _cstring->_len; ++ i)
    {
        CChar *_tmp_cchar_ptr = (CChar *)(_cstring->_data->at(_cstring->_data, i));
        memcpy(_raw_data_ptr, _tmp_cchar_ptr->_data_ptr, _tmp_cchar_ptr->_len);
        _raw_data_ptr += _tmp_cchar_ptr->_len;
    }

    return _raw_data;
}

CChar * _CStringAt(CString * _cstring, int _index)
{
    if(_index >= _cstring->_len) return NULL;
    else
    {
        return _cstring->_data->at(_cstring->_data, _index);
    }
}

void _CStringAppendCChar(CString * _cstring, CChar * _cchar)
{
    if(_cchar == NULL) return;
    CChar *_tmp_end = CCharConstructor("\0", WITH_COPY);
    CChar *_cstring_back = _cstring->_data->back(_cstring->_data);

    if(_cstring_back->equal(_cstring_back, _tmp_end))
    {
        _cstring->_data->pop_back(_cstring->_data, CCharDestructor);
        _cstring->_len --;
    }

    _cstring->_data->push_back(_cstring->_data, _cchar, AUTO_FREE);
    _cstring->_len ++;

    if(!_cchar->equal(_cchar, _tmp_end))
    {
        _cstring->_data->push_back(_cstring->_data, _tmp_end, AUTO_FREE);
        _cstring->_len ++;
    }
    else
    {
        CCharDestructor((void **)(&_tmp_end));
    }
}

void _CStringAppendChar(CString *_cstring, char *_c_string, int _copy_flag)
{
    if(_c_string == NULL || (_copy_flag != 0 && _copy_flag != 1)) return;
    CChar *_tmp_cchar = CCharConstructor(_c_string, _copy_flag);
    _cstring->append_cchar(_cstring, _tmp_cchar);
}

void _CStringAppendCString(CString *_cstring, CString *_append_cstring)
{
    if(_append_cstring->_len <= 0) return;
    for(int i = 0; i < _append_cstring->_len; ++ i)
    {
        _cstring->append_cchar(_cstring, _append_cstring->at(_append_cstring, i));
    }
}

void _CStringAppendString(CString *_cstring, char *_append_c_string)
{
    CString *_tmp_cstring = CStringConstructor(_append_c_string);
    _cstring->append_cstring(_cstring, _tmp_cstring);
}

CString * _CStringSubStr(CString * _cstring, int _begin, int _end)
{
    if(_begin < 0 || _begin >= _cstring->_len || _end < 0 || _end > _cstring->_len || _begin > _end)
    {
        return NULL;
    }
    CString *_result_cstr = CStringConstructor("");
    for(int i = _begin; i < _end; ++ i)
    {
        CChar * _tmp_cchar = _cstring->at(_cstring, i);
        _result_cstr->append_cchar(_result_cstr, _tmp_cchar);
    }
    CChar *_tmp_end = CCharConstructor("\0", WITH_COPY);
    CChar *_tmp_back = _result_cstr->_data->back(_result_cstr->_data);

    if(_tmp_back->equal(_tmp_back, _tmp_end))
        CCharDestructor((void **)(&_tmp_end));
    else 
        _result_cstr->append_cchar(_result_cstr, _tmp_end);
    return _result_cstr;
}

CVector * _CStringSplit(CString * _cstring, CChar * _cchar)
{
    CVector *_result_vector = CVectorConstructor();
    CString *_tmp_cstring;

    int _begin = 0;
    for(int i = 0; i < _cstring->_len; i++)
    {
        if(_cstring->at(_cstring, i)->equal(_cstring->at(_cstring, i), _cchar))
        {
            if(_begin < i)
            {
                _tmp_cstring = _cstring->substr(_cstring, _begin, i);
                _result_vector->push_back(_result_vector, _tmp_cstring, AUTO_FREE);
            }

            _begin = i + 1;
        }
    }

    if(_begin < _cstring->_len - 1)
    {
        _tmp_cstring = _cstring->substr(_cstring, _begin, _cstring->_len);
        _result_vector->push_back(_result_vector, _tmp_cstring, AUTO_FREE);
    }
        
    
    if(_result_vector->_rear == 0)
        CVectorDestructor((void**)(&_result_vector), CStringDestructor);
    return _result_vector;
}