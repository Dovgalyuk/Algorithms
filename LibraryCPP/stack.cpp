#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector *vec;
};

Stack *stack_create()
{
    Stack *stack = new Stack;
    stack->vec = vector_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    if (stack != nullptr)
    {
        vector_delete(stack->vec);
        delete stack;
    }
}

void stack_push(Stack *stack, Data data)
{
    size_t current_size = vector_size(stack->vec);
    vector_resize(stack->vec, current_size + 1);
    vector_set(stack->vec, current_size, data);
}

Data stack_get(const Stack *stack)
{
    size_t current_size = vector_size(stack->vec);
    return vector_get(stack->vec, current_size - 1);
}

void stack_pop(Stack *stack)
{
    size_t current_size = vector_size(stack->vec);
    vector_resize(stack->vec, current_size - 1);
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->vec) == 0;
}
