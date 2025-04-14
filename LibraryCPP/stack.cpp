#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector *vector;
};

Stack *stack_create()
{
    Stack *stack = new Stack;
    stack->vector = vector_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    vector_delete(stack->vector);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    vector_set(stack->vector, vector_size(stack->vector), data);
}

Data stack_get(const Stack *stack)
{
    return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void stack_pop(Stack *stack)
{
    if (vector_size(stack->vector) > 0) {
        size_t new_size = vector_size(stack->vector) - 1;
        vector_resize(stack->vector, new_size);
    }
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->vector) == 0;
}
