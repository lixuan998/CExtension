/**
 * @author climatex
 * @date 2023-Sep-12
 * @version 1.0.1
 * @file xml.c
*/
#include "xml.h"

static Xnode *xml_root_node;
static XHeader *xml_header;

static char lt[] = "<";
static int lt_pos = 0;
static char rt[] = ">";
static int gt_pos = 0;
static char slash[] = "/";
static char space[] = " ";
static char equal_mark[] = "=";
static char q_mark[] = "?";
static char exclamation[] = "!";
static char dash[] = "-";
static char quates[] = "\"";

Xnode * create_xnode()
{
    Xnode *xnode = (Xnode *)malloc(sizeof(Xnode));
    xnode -> attribute_keys = create_list();
    xnode -> attribute_values = create_list();
    xnode -> childs = create_list();
    xnode -> parent = NULL;
    xnode -> node_name = NULL;
    xnode -> content = NULL;
    xnode -> begin_lt = -1;
    xnode -> begin_gt = -1;
    xnode -> end_lt = -1;
    xnode -> end_gt = -1;
    xnode -> label_closed = FALSE;
    return xnode;
}

XHeader * create_xheader()
{
    XHeader *xheader = (XHeader *)malloc(sizeof(XHeader));
    xheader -> begin_lt = -1;
    xheader -> begin_gt = -1;
    xheader -> end_lt = -1;
    xheader -> end_gt = -1;
    xheader -> attribute_keys = create_list();
    xheader -> attribute_values = create_list();
    xheader -> file_type = NULL;
    xheader -> label_closed = FALSE;
}

int analyze_xml(char *xml_file)
{
    xml_root_node = create_xnode();
    xml_header = create_xheader();
    Stack *stack = create_stack();
    CString *xml_cstring = create_cstring(xml_file);
    int find_lt, find_gt;
    int is_comment = FALSE;
    find_lt = find_gt = 0;
    for(int i = 0; i < xml_cstring -> len; ++ i)
    {
        char *cur_cchar_data = xml_cstring -> data[i] -> data;
        if(strcmp(cur_cchar_data, lt) == 0)
        {
            lt_pos = i;
            find_lt = TRUE;
        }
        if(strcmp(cur_cchar_data, rt) == 0)
        {
            gt_pos = i;
            find_gt = TRUE; 
        }
        if(find_lt == TRUE && find_gt == TRUE)
        {
            if(strcmp(xml_cstring -> data[lt_pos + 1] -> data, slash) == 0)
            {
                if(stack -> top < 0)
                {
                    perror ("in func \"analyze_xml\": empty stack\r\n");
                    return STACK_EMPTY_ERROR;
                } 
                Xnode *close_xnode = (Xnode *)pop_stack(stack);
                close_xnode -> end_lt = lt_pos;
                close_xnode -> end_gt = gt_pos;
                close_xnode -> label_closed = TRUE;
                if(close_xnode -> childs -> len == 0)
                {
                    int content_len = close_xnode -> end_lt - close_xnode -> begin_gt - 1;
                    int content_pos = close_xnode -> begin_gt + 1;
                    close_xnode -> content = substr_cstring(xml_cstring, content_pos, content_len);
                }
            }
            else if(strcmp(xml_cstring -> data[gt_pos - 1] -> data, slash) == 0)
            {
                if(stack -> top < 0)
                {
                    xml_root_node -> begin_lt = lt_pos;
                    xml_root_node -> begin_gt = gt_pos;
                    xml_root_node -> end_lt = lt_pos;
                    xml_root_node -> end_gt = gt_pos;
                    xml_root_node -> label_closed = TRUE;
                    analyze_xnode(xml_root_node, substr_cstring(xml_cstring, lt_pos + 1, gt_pos - lt_pos - 2));
                }
                else
                {
                    Xnode *new_xml_node = create_xnode();
                    new_xml_node -> begin_lt = lt_pos;
                    new_xml_node -> begin_gt = gt_pos;
                    new_xml_node -> end_lt = lt_pos;
                    new_xml_node -> end_gt = gt_pos;
                    new_xml_node -> label_closed = TRUE;
                    analyze_xnode(new_xml_node, substr_cstring(xml_cstring, lt_pos + 1, gt_pos - lt_pos - 2));
                    Xnode *parent_node = (Xnode *)top_stack(stack);
                    new_xml_node -> parent = parent_node;
                    insert_list(parent_node -> childs, (void *)new_xml_node, APPEND);
                }
            }
            else if(strcmp(xml_cstring -> data[lt_pos + 1] -> data, q_mark) == 0&&
                    strcmp(xml_cstring -> data[gt_pos - 1] -> data, slash) == 0)
            {
                
            }
            else if(strcmp(xml_cstring -> data[lt_pos + 1] -> data, exclamation) == 0)
            {
                find_lt = find_gt = FALSE;
                continue;
            }
            else
            {
                if(stack -> top < 0)
                {
                    xml_root_node -> begin_lt = lt_pos;
                    xml_root_node -> begin_gt = gt_pos;
                    analyze_xnode(xml_root_node, substr_cstring(xml_cstring, lt_pos + 1, gt_pos - lt_pos - 1));
                    push_stack(stack, (void *)xml_root_node);
                }
                else
                {
                    Xnode *new_xml_node = create_xnode();
                    new_xml_node -> begin_lt = lt_pos;
                    new_xml_node -> begin_gt = gt_pos;
                    analyze_xnode(new_xml_node, substr_cstring(xml_cstring, lt_pos + 1, gt_pos - lt_pos - 1));
                    Xnode *parent_node = (Xnode *)top_stack(stack);
                    new_xml_node -> parent = parent_node;
                    insert_list(parent_node -> childs, (void *)new_xml_node, APPEND);
                    push_stack(stack, (void *)new_xml_node);
                }
            }
            
            find_lt = find_gt = FALSE;
        }
    }
    
    return SUCCESS;
}

int analyze_xnode(Xnode *xnode, CString *xnode_info)
{
    xnode -> node_name = create_cstring(NULL);
    int idx = 0;
    for(; idx < xnode_info -> len; ++ idx)
    {
        char *cur_cchar_data = xnode_info -> data[idx] -> data;
        if(strcmp(cur_cchar_data, space) == 0)
        {
            idx ++;
            break;
        }
        append_cstring(xnode -> node_name, cur_cchar_data);
    }

    int match_status = 1;   //  0 represents none, 1 represents attributes, 2 represents values
    CString *attribute = NULL;
    CString *value = NULL;
    while(idx < xnode_info -> len)
    {
        for(; idx < xnode_info -> len; ++ idx)
        {
            char *cur_cchar_data = xnode_info -> data[idx] -> data;
            if(strcmp(cur_cchar_data, space) != 0)
            {
                if(match_status == 0)
                {
                    if(strcmp(cur_cchar_data, quates) == 0)
                    {
                        match_status = 2;
                    }
                }
                else if(match_status == 1)
                {
                    if(strcmp(cur_cchar_data, equal_mark) == 0)
                    {
                        int res = insert_list(xnode -> attribute_keys, (void *)attribute, APPEND);
                        attribute = NULL;
                        match_status = 0;
                        continue;
                    }
                    if(attribute == NULL)
                    {
                        attribute = create_cstring(NULL);
                    }
                    append_cstring(attribute, cur_cchar_data);
                }
                else if(match_status == 2)
                {
                    if(strcmp(cur_cchar_data, quates) == 0)
                    {
                        insert_list(xnode -> attribute_values, (void *)value, APPEND);
                        value = NULL;
                        match_status = 1;
                        continue;
                    }
                    if(value == NULL)
                    {
                        value = create_cstring(NULL);
                    }
                    append_cstring(value, cur_cchar_data);
                }
            }
            else
            {
                if(match_status == 1)
                {
                    if(attribute == NULL)
                    {
                        continue;
                    }
                    insert_list(xnode -> attribute_keys, (void *)attribute, APPEND);
                    printf("ATTRIBUTE: %s\n", raw_cstring(attribute));
                    attribute = NULL;
                    match_status = 0;
                }
                else if(match_status == 2)
                {
                    append_cstring(value, cur_cchar_data);
                }
            }
        }
    }

}

void print_recursive(Xnode *node, int tab_cnt)
{
    for(int i = 0; i < 1 && tab_cnt > 0; ++ i)
    {
        for(int j = 0; j < tab_cnt - 1; ++ j)
            printf("|    ");
        printf("|\n");
    }
    printf("|");
    for(int i = 0; i < tab_cnt - 1; i++) printf("    |");
    for(int i = 0; i < 4 && tab_cnt > 0; i++)
    printf("-");
    printf("%s ", raw_cstring(node->node_name));
    for(int i = 0; i < node -> attribute_keys -> len; ++ i)
    {
        CString *attr = (CString *)(find_list(node -> attribute_keys, i + 1) -> data);
        CString *val = (CString *)(find_list(node -> attribute_values, i + 1) -> data);
        if(attr == NULL || val == NULL) continue;
        printf("%s = \"%s\"\n", raw_cstring(attr), raw_cstring(val));
    }
    for(int i = 0; i < node -> childs -> len; ++ i)
    {
        Xnode *next = (Xnode *)(find_list(node -> childs, i + 1) -> data);
        print_recursive(next, tab_cnt + 1);
    }
}

void test()
{
    print_recursive(xml_root_node, 0);
}