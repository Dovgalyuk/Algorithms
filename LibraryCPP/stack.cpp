#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector* vec;
};

Stack* stack_create()
{
    Stack *stack = new Stack;
    stack->vec = vector_create();
    return stack;
}

void stack_delete(Stack* stack)
{
    vector_delete(stack->vec);
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    vector_resize(stack->vec, vector_size(stack->vec) + 1);
    vector_set(stack->vec, vector_size(stack->vec) - 1, data);
}

Data stack_get(const Stack* stack)
{
    return vector_get(stack->vec, vector_size(stack->vec) - 1);
}

void stack_pop(Stack* stack)
{
    vector_resize(stack->vec, vector_size(stack->vec) - 1);
}

bool stack_empty(const Stack* stack)
{
    return vector_size(stack->vec) == 0;
}
