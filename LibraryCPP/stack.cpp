#include "stack.h"
#include "vector.h"
#include <stdexcept>

struct Stack
{
    Vector *vec;
};

Stack *stack_create()
{
    Stack *s = new Stack;
    s->vec = vector_create();
    return s;
}

void stack_delete(Stack *stack)
{
    vector_delete(stack->vec);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    size_t n = vector_size(stack->vec);
    vector_resize(stack->vec, n + 1);
    vector_set(stack->vec, n, data);
}

Data stack_get(const Stack *stack)
{
    size_t n = vector_size(stack->vec);
    if (n == 0)
        throw std::runtime_error("stack_get: empty stack");
    return vector_get(stack->vec, n - 1);
}

void stack_pop(Stack *stack)
{
    size_t n = vector_size(stack->vec);
    if (n == 0)
        throw std::runtime_error("stack_pop: empty stack");
    vector_resize(stack->vec, n - 1);
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->vec) == 0;
}