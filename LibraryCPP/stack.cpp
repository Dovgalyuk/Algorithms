#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector* vector;
};

Stack* stack_create()
{
    Stack* stack = new Stack;
    stack->vector = vector_create();
    return stack;
}

void stack_delete(Stack* stack)
{
    vector_delete(stack->vector);
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    size_t index = vector_size(stack->vector);
    vector_resize(stack->vector, index + 1);
    vector_set(stack->vector, index, data);
}

Data stack_get(const Stack* stack)
{
    return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void stack_pop(Stack* stack)
{
    vector_resize(stack->vector, vector_size(stack->vector) - 1);
}

bool stack_empty(const Stack* stack)
{
    size_t size = vector_size(stack->vector);
    return size == 0;
}

