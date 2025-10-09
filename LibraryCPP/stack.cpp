#include "stack.h"

struct Stack
{
};

Stack *stack_create()
{
    return new Stack;
}

void stack_delete(Stack *stack)
{
    // TODO: free stack elements
    (void)stack;
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    (void)stack;
    (void)data;
}

Data stack_get(const Stack *stack)
{
    (void)stack;
    return (Data)0;
}

void stack_pop(Stack *stack)
{
    (void)stack;
}

bool stack_empty(const Stack *stack)
{
    (void)stack;
    return true;
}
