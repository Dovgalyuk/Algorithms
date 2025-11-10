#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector* vector;
};

Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->vector = vector_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    if (stack) {
        vector_delete(stack->vector);
        delete stack;
    }
}

void stack_push(Stack *stack, Data data)
{
    if (stack) {
        size_t current_size = vector_size(stack->vector);
        vector_resize(stack->vector, current_size + 1);
        vector_set(stack->vector, current_size, data);
    }
}

Data stack_get(const Stack *stack)
{
    if (stack && !stack_empty(stack)) {
        size_t size = vector_size(stack->vector);
        return vector_get(stack->vector, size - 1);
    }
    return 0;
}

void stack_pop(Stack *stack)
{
    if (stack && !stack_empty(stack)) {
        size_t size = vector_size(stack->vector);
        vector_resize(stack->vector, size - 1);
    }
}

bool stack_empty(const Stack *stack)
{
    return !stack || vector_size(stack->vector) == 0;
}