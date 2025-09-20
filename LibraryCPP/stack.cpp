/*#include "stack.h"

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
    delete stack;
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
*/


#include "stack.h"

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

struct Stack
{
};

Stack* stack_create()
{
    return new Stack;
}

void stack_delete(Stack* stack)
{
    // TODO: free stack elements
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    UNUSED(stack);
    UNUSED(data);
}

Data stack_get(const Stack* stack)
{
    UNUSED(stack);
    return (Data)0;
}

void stack_pop(Stack* stack)
{
    UNUSED(stack);
}

bool stack_empty(const Stack* stack)
{
    UNUSED(stack);
    return true;
}