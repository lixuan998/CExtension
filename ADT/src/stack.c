/**
 * @author climatex
 * @date 2023-Sep-12
 * @version 1.0.1
 * @file stack.c
*/

#include "stack.h"

Stack * create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack -> top = -1;
    stack -> data = (void **)malloc(sizeof(void *) * INIT_STACK_SIZE);
    return stack;
}

void * push_stack(Stack *stack, void * new_data)
{
    if(stack == NULL)
    {
        perror ("in func \"push_stack\": target stack is null\r\n");
        return NULL;
    }
    if(stack -> top + 1 % INIT_STACK_SIZE == 0)
    {
        stack -> data = (void **)realloc(stack -> data, sizeof(void *) * (stack -> top + 1 + INIT_STACK_SIZE));
        if(stack -> data == NULL)
        {
            perror ("in func \"push_stack\": realloc failed\r\n");
            return NULL;
        }
    }
    stack -> data[++ stack -> top] = new_data;
    return NULL;
}

void * top_stack(Stack *stack)
{
    if(stack-> top == -1)
    {
        return NULL;
    }
    return stack -> data[stack -> top];
}

void * pop_stack(Stack * stack)
{
    if(stack-> top == -1)
    {
        return NULL;
    }
    return stack -> data[stack -> top --];
}