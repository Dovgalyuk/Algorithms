#include "stack.h"
#include "vector.h"

#include <stdexcept>

struct Stack
{
    Vector* elements;
};

Stack* stack_create()
{
    return new Stack{vector_create()};
}

void stack_delete(Stack* stack)
{
    if (stack == nullptr)
        return;

    vector_delete(stack->elements);
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    if (stack == nullptr)
        throw std::invalid_argument("a?");

    size_t size = vector_size(stack->elements);

    vector_resize(stack->elements, size + 1);
    vector_set(stack->elements, size, data);
}

Data stack_get(const Stack* stack)
{
    if (stack_empty(stack))
        throw std::out_of_range("Stack is empty");

    size_t size = vector_size(stack->elements);

    return vector_get(stack->elements, size - 1);
}

void stack_pop(Stack* stack)
{
    if (stack_empty(stack))
        throw std::out_of_range("Stack is empty");

    size_t size = vector_size(stack->elements);

    vector_resize(stack->elements, size - 1);
}

bool stack_empty(const Stack* stack)
{
    return stack == nullptr || vector_size(stack->elements) == 0;
}