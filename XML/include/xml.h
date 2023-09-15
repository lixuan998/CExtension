/**
 * @author climatex
 * @date 2023-Sep-12
 * @version 1.0.1
 * @file xml.h
*/

#ifndef __XML_H__
#define __XML_H__

#include "../../ADT/include/list.h"
#include "../../ADT/include/stack.h"
#include "../../Basic/include/cstring.h"

#define FALSE           0
#define TRUE            1

#define SUCCESS              0
#define STACK_EMPTY_ERROR    -1

typedef struct _Xnode{
    int begin_lt;
    int begin_gt;
    int end_lt;
    int end_gt;
    int label_closed;
    CString *node_name;
    CString *content;
    List *attribute_keys;
    List *attribute_values;
    List *childs;
    struct _Xnode *parent;
} Xnode;

typedef struct _XHeader{
    int begin_lt;
    int begin_gt;
    int end_lt;
    int end_gt;
    int label_closed;
    CString *file_type;
    List *attribute_keys;
    List *attribute_values;
} XHeader;

Xnode * create_xnode();
XHeader * create_xheader();

int analyze_xml(char *xml_file);

int analyze_xnode(Xnode *xnode, CString *xnode_info);

void print_recursive(Xnode *node, int tab_cnt);

void test();
#endif  // __XML_H__