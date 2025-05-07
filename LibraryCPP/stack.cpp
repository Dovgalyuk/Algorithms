#include "stack.h"
#include "vector.h"
#include <stdexcept>

struct Stack
{
    Vector* vector;
};

Stack* stack_create()
{
    Stack* stack = new Stack();
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
    size_t size = vector_size(stack->vector);
    vector_resize(stack->vector, size + 1);
    vector_set(stack->vector, size, data);
}

Data stack_get(const Stack* stack)
{
    if (vector_size(stack->vector) == 0)
        throw std::runtime_error("Stack underflow");
    return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void stack_pop(Stack* stack)
{
    if (vector_size(stack->vector) == 0)
        throw std::runtime_error("Stack underflow");
    vector_resize(stack->vector, vector_size(stack->vector) - 1);
}

bool stack_empty(const Stack* stack)
{
    return vector_size(stack->vector) == 0;
}

size_t stack_size(const Stack* stack) {
    return vector_size(stack->vector);
}