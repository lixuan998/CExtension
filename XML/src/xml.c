/**
 * @author climatex
 * @date 2023-Sep-12
 * @version 1.0.1
 * @file xml.c
*/
#include "xml.h"

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
static char newline[] = "\n";
static char return_mark[] = "\r";

Xnode * create_xnode(int is_header, char *node_name, char *content, List *attribute_keys, List *attribute_values)
{
    Xnode *xnode = (Xnode *)malloc(sizeof(Xnode));
    if(attribute_keys == NULL)
    {
        xnode -> attribute_keys = create_list();    
    }
    else
    {
        xnode -> attribute_keys = attribute_keys;
    }
    if(attribute_values == NULL)
    {
        xnode -> attribute_values = create_list();
    }
    else
    {
        xnode -> attribute_values = attribute_values;
    }
    xnode -> childs = create_list();
    xnode -> parent = NULL;
    xnode -> node_name = NULL;
    xnode -> content = NULL;
    xnode -> begin_lt = -1;
    xnode -> begin_gt = -1;
    xnode -> end_lt = -1;
    xnode -> end_gt = -1;
    xnode -> depth = 0;
    xnode -> label_closed = FALSE;
    xnode -> is_header = is_header;

    if(node_name != NULL)
    {
        xnode -> node_name = create_cstring(node_name);
        xnode -> label_closed = TRUE;  
    }
    if(content != NULL)
    {
        xnode -> content = create_cstring(content);
    }

    return xnode;
}

Xnode * create_xheader()
{
    Xnode *xheader = (Xnode *)malloc(sizeof(Xnode));
    xheader -> begin_lt = -1;
    xheader -> begin_gt = -1;
    xheader -> end_lt = -1;
    xheader -> end_gt = -1;
    xheader -> attribute_keys = create_list();
    xheader -> attribute_values = create_list();
    xheader -> node_name = NULL;
    xheader -> label_closed = FALSE;
    return xheader;
}

int add_child(Xnode *parent, Xnode *child)
{
    if(parent == NULL)
    {
        perror ("in func \"add_child\": parent pointer is null\r\n");
        return NULL_PTR_ERROR;
    }
    if(child == NULL)
    {
        perror ("in func \"add_child\": child pointer is null\r\n");
        return NULL_PTR_ERROR;
    }
    if(parent -> is_header)
    {
        child -> depth = parent -> depth;
    }
    else
    {
        child -> depth = parent -> depth + 1;
    }
    int ret = insert_list(parent -> childs, (void *)child, APPEND);
    if(ret != 0)
    {
        perror ("in func \"add_child\": fail to insert child node into parent node\r\n");
        return INSERT_LIST_ERROR;
    }
    child -> parent = parent;
    return SUCCESS;
}

int analyze_xml(Xnode **root_node, char *xml_file)
{
    *root_node = create_xnode(FALSE, NULL, NULL, NULL, NULL);
    Xnode *xml_root_node = *root_node;
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
                    free_stack(stack);
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
                    Xnode *new_xml_node = create_xnode(FALSE, NULL, NULL, NULL, NULL);
                    new_xml_node -> begin_lt = lt_pos;
                    new_xml_node -> begin_gt = gt_pos;
                    new_xml_node -> end_lt = lt_pos;
                    new_xml_node -> end_gt = gt_pos;
                    new_xml_node -> label_closed = TRUE;
                    analyze_xnode(new_xml_node, substr_cstring(xml_cstring, lt_pos + 1, gt_pos - lt_pos - 2));
                    Xnode *parent_node = (Xnode *)top_stack(stack);
                    new_xml_node -> parent = parent_node;
                    if(parent_node -> is_header)
                    {
                        new_xml_node -> depth = parent_node -> depth;
                    }
                    else
                    {
                        new_xml_node -> depth = parent_node -> depth + 1;
                    }
                    int ret = add_child(parent_node, new_xml_node);
                    if(ret != 0)
                    {
                        perror ("in func \"analyze_xml\": fail to add child node\r\n");
                        return INSERT_LIST_ERROR;
                    }
                }
            }
            else if(strcmp(xml_cstring -> data[lt_pos + 1] -> data, q_mark) == 0&&
                    strcmp(xml_cstring -> data[gt_pos - 1] -> data, q_mark) == 0)
            {
                if(stack -> top < 0)
                {
                    xml_root_node -> begin_lt = lt_pos;
                    xml_root_node -> begin_gt = gt_pos;
                    xml_root_node -> end_lt = lt_pos;
                    xml_root_node -> end_gt = gt_pos;
                    xml_root_node -> label_closed = TRUE;
                    xml_root_node -> is_header = TRUE;  
                    analyze_xnode(xml_root_node, substr_cstring(xml_cstring, lt_pos + 2, gt_pos - lt_pos - 3));
                    push_stack(stack, xml_root_node);
                }
                else
                {
                    Xnode *new_xml_node = create_xnode(FALSE, NULL, NULL, NULL, NULL);
                    new_xml_node -> begin_lt = lt_pos;
                    new_xml_node -> begin_gt = gt_pos;
                    new_xml_node -> end_lt = lt_pos;
                    new_xml_node -> end_gt = gt_pos;
                    new_xml_node -> label_closed = TRUE;
                    new_xml_node -> is_header = TRUE; 
                    analyze_xnode(new_xml_node, substr_cstring(xml_cstring, lt_pos + 2, gt_pos - lt_pos - 3));
                    Xnode *parent_node = (Xnode *)top_stack(stack);
                    new_xml_node -> parent = parent_node;
                    new_xml_node -> depth = parent_node -> depth;
                    int ret = add_child(parent_node, new_xml_node);
                    if(ret != 0)
                    {
                        perror ("in func \"analyze_xml\": fail to add child node\r\n");
                        return INSERT_LIST_ERROR;
                    }
                }
                
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
                    Xnode *new_xml_node = create_xnode(FALSE, NULL, NULL, NULL, NULL);
                    new_xml_node -> begin_lt = lt_pos;
                    new_xml_node -> begin_gt = gt_pos;
                    analyze_xnode(new_xml_node, substr_cstring(xml_cstring, lt_pos + 1, gt_pos - lt_pos - 1));
                    Xnode *parent_node = (Xnode *)top_stack(stack);
                    new_xml_node -> parent = parent_node;
                    printf("parent: %s depth: %d is header: %d\n", raw_cstring(parent_node -> node_name), parent_node -> depth, parent_node -> is_header);
                    
                    if(parent_node -> is_header)
                    {
                        new_xml_node -> depth = parent_node -> depth;
                    }
                    else
                    {
                        new_xml_node -> depth = parent_node -> depth + 1;
                    }
                    int ret = add_child(parent_node, new_xml_node);
                    if(ret != 0)
                    {
                        perror ("in func \"analyze_xml\": fail to add child node\r\n");
                        return INSERT_LIST_ERROR;
                    }
                    push_stack(stack, (void *)new_xml_node);
                }
            }
            
            find_lt = find_gt = FALSE;
        }
    }
    free_stack(stack);
    return SUCCESS;
}

void phrase_to_xml(Xnode *root_node, CString *phrased_xml)
{
    if(root_node -> parent != NULL)
    {
        if(root_node -> parent -> is_header == FALSE)
        {
            root_node -> depth = root_node -> parent -> depth + 1;
        }
        else
        {
            root_node -> depth = root_node -> parent -> depth;
        }
    }
    for(int i = 0; i < root_node -> depth; ++ i)
    {
        append_cstring(phrased_xml, "    ");
    }

    if(root_node -> is_header)
    {
        append_cstring(phrased_xml, "<?");
    }
    else
    {
        append_cstring(phrased_xml, "<");
    }
    
    append_cstring(phrased_xml, raw_cstring(root_node -> node_name));
    
    for(int i = 0; i < root_node -> attribute_keys -> len; ++ i)
    {
        CString *attribute = (CString *)(find_list(root_node -> attribute_keys, i + 1) -> data);
        CString *value = (CString *)(find_list(root_node -> attribute_values, i + 1) -> data);

        if(attribute == NULL || value == NULL)
        {
            break;
        }
        append_cstring(phrased_xml, " ");
        append_cstring(phrased_xml, raw_cstring(attribute));
        append_cstring(phrased_xml, "=\"");
        append_cstring(phrased_xml, raw_cstring(value));
        append_cstring(phrased_xml, "\"");
    }
    if(root_node -> is_header)
    {
        append_cstring(phrased_xml, "?>\r\n");
    }
    else
    {
        append_cstring(phrased_xml, ">");
    }
    
    if(root_node -> content != NULL)
    {
        append_cstring(phrased_xml, raw_cstring(root_node -> content)); 
    }
    else
    {
        append_cstring(phrased_xml, "\r\n");
    }
    for(int i = 0; i < root_node -> childs -> len; ++ i)
    {
        Xnode *child = (Xnode *)(find_list(root_node -> childs, i + 1) -> data);
        phrase_to_xml(child, phrased_xml);
    }

    if(root_node -> is_header == FALSE)
    {
        for(int i = 0; i < root_node -> depth && root_node -> content == NULL; ++ i)
        {
            append_cstring(phrased_xml, "    ");
        }
        append_cstring(phrased_xml, "</");
        append_cstring(phrased_xml, raw_cstring(root_node -> node_name));
        append_cstring(phrased_xml, ">\r\n");
    }
    
}

int analyze_xnode(Xnode *xnode, CString *xnode_info)
{
    xnode -> node_name = create_cstring(NULL);
    int idx = 0;
    for(; idx < xnode_info -> len; ++ idx)
    {
        char *cur_cchar_data = xnode_info -> data[idx] -> data;
        if(strcmp(cur_cchar_data, space) == 0||
           strcmp(cur_cchar_data, newline) == 0||
           strcmp(cur_cchar_data, return_mark) == 0)
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
            
            if(strcmp(cur_cchar_data, space) != 0&&
               strcmp(cur_cchar_data, newline) != 0&&
               strcmp(cur_cchar_data, return_mark) != 0)
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
    return SUCCESS;
}

void print_xnode_recursive(Xnode *node)
{
    for(int i = 0; i < 1 && node -> depth > 0; ++ i)
    {
        for(int j = 0; j < node -> depth - 1; ++ j)
            printf("    ");
        printf("\n");
    }
    if(node -> depth == 0) printf("\n");
    printf("|");
    for(int i = 0; i < node -> depth - 1; i++) printf("    |");
    for(int i = 0; i < 4 && node -> depth > 0; i++)
    printf("-");
    printf("%s ", raw_cstring(node -> node_name));
    if(node -> content != NULL)
    {
        printf("%s ", raw_cstring(node -> content));
    }
    List *attributes = node -> attribute_keys;
    List *values = node -> attribute_values;

    for(int i = 0; i < attributes -> len; ++ i)
    {
        CString *attribute = (CString *)(find_list(attributes, i + 1) -> data);
        CString *value = (CString *)(find_list(values, i + 1) -> data); 
        if(attribute == NULL || value == NULL)
        {
            continue;
        }
        printf("%s=\"%s\" ", raw_cstring(attribute), raw_cstring(value));
    }
    for(int i = 0; i < node -> childs -> len; ++ i)
    {
        Xnode *next = (Xnode *)(find_list(node -> childs, i + 1) -> data);
        print_xnode_recursive(next);
    }
}

void print_xml_tree(Xnode *root_node)
{
    print_xnode_recursive(root_node);
    printf("\r\n");
}