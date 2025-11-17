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
    vector_delete(stack->vector);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    size_t current_size = vector_size(stack->vector);
    vector_resize(stack->vector, current_size + 1);
    vector_set(stack->vector, current_size, data);
}

Data stack_get(const Stack *stack)
{
    if (stack_empty(stack)) {
        return (Data)0;
    }
    size_t last_index = vector_size(stack->vector) - 1;
    return vector_get(stack->vector, last_index); 
}

void stack_pop(Stack *stack)
{
    if (!stack_empty(stack)) {
        size_t current_size = vector_size(stack->vector);
        vector_resize(stack->vector, current_size - 1);
    }
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->vector) == 0;
}