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
    vector_resize(stack->vec, 1);
    return stack;
}

void stack_delete(Stack *stack)
{
    vector_delete(stack->vec);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    //vector_set(stack->vec, stack->index++, data);
    if (vector_size(stack->vec) <= stack->index)
    {
        vector_resize(stack->vec, stack->index * 2);
    }
    vector_set(stack->vec, stack->index, data);
    stack->index++;
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
