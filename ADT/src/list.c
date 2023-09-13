/**
 * @author climatex
 * @date 2023-Sep-11
 * @version 1.0.1
 * @file list.c
*/

#include "list.h"

List * create_list()
{
    List * list;
    list = (List *)malloc(sizeof(List));
    if(list == NULL)
    {
        perror ("in func \"create_list\": list allocation failed\r\n");
        return NULL;
    }
    list -> len = 0;
    list -> next = NULL;
    list -> prev = NULL;
    list -> data = NULL;
    return list;
}

List * find_list(List * list, int idx)
{
    List * slider = list;
    int cur_idx = 0;
    while(slider != NULL && cur_idx < idx)
    {
        slider = slider -> next;
        ++ cur_idx;
    }
    if(slider == NULL)
    {
        perror ("in func \"find_list\": node doesn't exist\r\n");
    }
    return slider;
}

int insert_list(List * list, void * new_data, int pos)
{
    List * new_node = (List *)malloc(sizeof(List));
    if(new_node == NULL)
    {
        perror ("in func \"insert_list\": new node allocation failed\r\n");
        return MEM_ALLOCATE_ERROR;
    }
    new_node -> data = new_data;
    if(pos == APPEND)
    {
        List * last_node = find_list(list, list -> len);
        if(last_node == NULL)
        {
            perror ("in func \"insert_list\": find last node error\r\n");
            free(new_node);
            return NOT_EXSIST;
        }
        new_node -> next = last_node -> next;
        new_node -> prev = last_node;
        last_node -> next = new_node;

        list -> len += 1;
        return SUCCESS;
    }

    List * old_node = find_list(list, pos);
    if(old_node == NULL)
    {
        perror ("in func \"insert_list\": pos overrange\r\n");
        free(new_node);
        return OVERRANGE;
    }

    new_node -> next = old_node;
    new_node -> prev = old_node -> prev;

    if(old_node -> prev != NULL)
    {
        old_node -> prev -> next = new_node;
    }
    if(old_node -> next != NULL)
    {
        old_node -> next -> prev = new_node;
    }

    list->len += 1;

    return SUCCESS;
}

int remove_list(List * list, int idx)
{
    List * rm_node = find_list(list, idx);
    if(rm_node == NULL)
    {
        perror ("in func \"remove_list\": removed node not found\r\n");
        return NOT_EXSIST;
    }
    if(rm_node -> prev != NULL)
    {
        rm_node -> prev -> next = rm_node -> next;
    }
    if(rm_node -> next != NULL)
    {
        rm_node -> next -> prev = rm_node -> prev;
    }

    free(rm_node);

    return SUCCESS;
}