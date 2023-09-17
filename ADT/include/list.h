/**
 * @author climatex
 * @date 2023-Sep-11
 * @version 1.0.1
 * @file list.h
*/
#ifdef __cplusplus
extern "C" {
#endif
#ifndef _LIST_H_
#define _LIST_H_

#define SUCCESS                      0
#define OVERRANGE                   -1
#define NOT_EXSIST                  -2
#define MEM_ALLOCATE_ERROR          -3

#define APPEND                      -1

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct _List{
    int len;
    void * data;
    struct _List * next;
    struct _List * prev;
} List;

/**
 * @brief create a new list
 * @return a pointer to a initialized list
*/
List * create_list();
void free_list(List * list);

/**
 * @brief find the list node at the given index, note that the index starts from 1
 * @param list pointer to the target list
 * @param idx index of the expected node
 * @return the node at the given index if success, NULL otherwise
*/
List * find_list(List * list, int idx);

/**
 * @brief insert a new element into the list, note that the pos starts from 1
 * @param list pointer to the target list
 * @param new_data data of the new list element
 * @param pos the position of the new element
 * @return return 0 if the operation succeeded, negative value otherwise
*/
int insert_list(List * list, void * new_data, int pos);

/**
 * @brief remove an element from the list, note that the index starts from 1, always remember to free the data pointer manually if necessary
 * @param list pointer to the target list
 * @param idx index of the removed element
 * @return return 0 if the operation succeeded, negative value otherwise
*/
int remove_list(List * list, int idx);
#ifdef __cplusplus
}
#endif

#endif // _LIST_H_