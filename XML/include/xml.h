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

typedef struct _XNode{
    CString *node_name;
    List *attribute_keys;
    List *attribute_values;
    List *childs;
    Xnode *parent;
} Xnode;

typedef struct _XHeader{
    CString *file_type;
    List *attribute_keys;
    List *attribute_values;
} XHeader;

Xnode * create_xnode();
XHeader * create_xheader();

void analyze_xml(char *xml_file);
#endif  // __XML_H__