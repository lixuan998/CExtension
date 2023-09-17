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

#define FALSE                   0
#define TRUE                    1

#define SUCCESS                 0
#define STACK_EMPTY_ERROR       -1
#define NULL_PTR_ERROR          -2
#define INSERT_LIST_ERROR       -3

typedef struct _Xnode{
    int begin_lt;
    int begin_gt;
    int end_lt;
    int end_gt;
    int label_closed;
    int is_header;
    int depth;
    CString *node_name;
    CString *content;
    List *attribute_keys;
    List *attribute_values;
    List *childs;
    struct _Xnode *parent;
} Xnode;

Xnode * create_xnode(int is_header, char *node_name, char *content, List *attribute_keys, List *attribute_values);

int add_child(Xnode *parent, Xnode *child);

int analyze_xml(Xnode **root_node, char *xml_file);

void phrase_to_xml(Xnode *root_node, CString *phrased_xml);

int analyze_xnode(Xnode *xnode, CString *xnode_info);

void print_xnode_recursive(Xnode *node);

void print_xml_tree(Xnode *root_node);
#endif  // __XML_H__