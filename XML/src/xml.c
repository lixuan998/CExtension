/**
 * @author climatex
 * @date 2023-Sep-12
 * @version 1.0.1
 * @file xml.c
*/
#include "xml.h"

static Xnode *xml_root_node;
static XHeader *xml_header;

Xnode * create_xnode()
{
    Xnode *xnode = (Xnode *)malloc(sizeof(Xnode));
    xnode -> attribute_keys = create_list();
    xnode -> attribute_values = create_list();
    xnode -> childs = create_list();
    xnode -> parent = NULL;
    xnode -> node_name = NULL;
    xnode -> content = NULL;
    return xnode;
}

XHeader * create_xheader()
{
    XHeader *xheader = (XHeader *)malloc(sizeof(XHeader));
    xheader -> attribute_keys = create_list();
    xheader -> attribute_values = create_list();
    xheader -> file_type = NULL;
}

void analyze_xml(char *xml_file)
{
    xml_root_node = create_xnode();
}