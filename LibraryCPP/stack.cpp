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
    vector_resize(stack->vector, vector_size(stack->vector) + 1);
    vector_set(stack->vector, vector_size(stack->vector) - 1, data);
}

Data stack_get(const Stack *stack)
{
    size_t stackSize = vector_size(stack->vector);
    if (stackSize > 0)
    {
        return vector_get(stack->vector, stackSize - 1);
    }
    return (Data)0;
}

void stack_pop(Stack *stack)
{
    if (!stack_empty(stack))
    {
        vector_resize(stack->vector, vector_size(stack->vector) - 1);
    }
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->vector) == 0;
}
