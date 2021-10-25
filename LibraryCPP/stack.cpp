#include "stack.h"
#include "vector.h"
#include <stdlib.h>

struct Stack
{
    Vector* man;
};

Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->man = vector_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    // TODO: free stack elements
    vector_delete(stack->man);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    vector_resize(stack->man, vector_size(stack->man) + 1);
    vector_set(stack->man, vector_size(stack->man) - 1, data);
}

Data stack_get(const Stack *stack)
{
    return vector_get(stack->man, vector_size(stack->man) - 1);
}

void stack_pop(Stack *stack)
{
    vector_resize(stack->man, vector_size(stack->man) - 1);
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->man);
}
