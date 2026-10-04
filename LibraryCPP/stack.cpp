#include "stack.h"
#include "vector.h"

using namespace std;

struct Stack
{
    Vector *values;
};

Stack *stack_create()
{
    return new Stack{vector_create()};
}

void stack_delete(Stack *stack)
{
    if (stack == nullptr)
        return;

    vector_delete(stack->values);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    if (stack == nullptr)
        return;

    size_t size = vector_size(stack->values);
    vector_resize(stack->values, size + 1);
    vector_set(stack->values, size, data);
}

Data stack_get(const Stack *stack)
{
    if (stack_empty(stack))
        return 0;

    return vector_get(stack->values, vector_size(stack->values) - 1);
}

void stack_pop(Stack *stack)
{
    if (!stack_empty(stack))
        vector_resize(stack->values, vector_size(stack->values) - 1);
}

bool stack_empty(const Stack *stack)
{
    return stack == nullptr || vector_size(stack->values) == 0;
}
