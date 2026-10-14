#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector* v;
};

Stack *stack_create()
{
    Stack* s = new Stack;
    s->v = vector_create();
    return s;
}

void stack_delete(Stack *stack)
{
    vector_delete(stack->v);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    size_t n = vector_size(stack->v);
    vector_resize(stack->v, n + 1);
    vector_set(stack->v, n, data);
}

Data stack_get(const Stack *stack)
{
    size_t n = vector_size(stack->v);
    if (n == 0) 
        return 0;

    return vector_get(stack->v, n - 1);
}

void stack_pop(Stack *stack)
{
    size_t n = vector_size(stack->v);
    if (n > 0) 
        vector_resize(stack->v, n - 1);
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->v) == 0;
}
