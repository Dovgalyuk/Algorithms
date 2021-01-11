#include <stdlib.h>
#include "vector.h"
#include "stack.h"

struct Stack
{
    Vector* vec;
    Data index = 0;
};

Stack *stack_create()
{
    Stack *stack = new Stack;
    stack->vec = vector_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    delete stack->vec;
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    vector_set(stack->vec, stack->index++, data);
}

Data stack_get(const Stack *stack)
{
    return vector_get(stack->vec, stack->index - 1);
}

void stack_pop(Stack *stack)
{
    stack->index--;
}

bool stack_empty(const Stack *stack)
{
    return stack->index == 0;
}
