#include "stack.h"

#include "vector.h"
#include <cassert>

struct Stack
{
    Vector *data;
};

Stack *stack_create()
{
    Stack *stack = new Stack;
    stack->data = vector_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    if (stack == nullptr) return;
    vector_delete(stack->data);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    assert(stack != nullptr);
    vector_resize(stack->data, vector_size(stack->data) + 1);
    vector_set(stack->data, vector_size(stack->data) - 1, data);
}

Data stack_get(const Stack *stack)
{
    assert(stack != nullptr && !stack_empty(stack));
    return vector_get(stack->data, vector_size(stack->data) - 1);
}

void stack_pop(Stack *stack)
{
    assert(stack != nullptr && !stack_empty(stack));
    vector_resize(stack->data, vector_size(stack->data) - 1);
}

bool stack_empty(const Stack *stack)
{
    assert(stack != nullptr);
    return vector_size(stack->data) == 0;
}
