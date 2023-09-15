/**
 * @author climatex
 * @date 2023-Sep-12
 * @version 1.0.1
 * @file stack.h
*/

#ifndef __STACK_H__
#define __STACK_H__

#define INIT_STACK_SIZE 100

#include <stdlib.h>
#include <stdio.h>

typedef struct _Stack{
    int top;
    void **data;
} Stack;

Stack * create_stack();
void free_stack(Stack *stack);

void * push_stack(Stack *stack, void * new_data);
void * top_stack(Stack *stack);
void * pop_stack(Stack * stack);
#endif //   __STACK_H__