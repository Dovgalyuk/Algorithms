#include <stdlib.h>
#include "stack.h"

typedef struct Stack
{
} Stack;

Stack *stack_create(FFree f)
{
    return malloc(sizeof(Stack));
}

void stack_delete(Stack *stack)
{
    // TODO: free stack elements
    free(stack);
}

void stack_push(Stack *stack, Data data)
{
}

Data stack_get(const Stack *stack)
{
    return (Data)0;
}

void stack_pop(Stack *stack)
{
}

bool stack_empty(const Stack *stack)
{
    return true;
}
