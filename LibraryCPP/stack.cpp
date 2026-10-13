#include "stack.h"
#include "vector.h"
#include <stdexcept>

struct Stack
{
    Vector *data;
};

Stack *stack_create()
{
    Stack *stack = new Stack;
    stack->data = vector_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    vector_delete(stack->data);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    vector_push_back(stack->data, data);
}

Data stack_get(const Stack *stack)
{
    if (vector_size(stack->data) == 0)
    {
        throw std::runtime_error("Stack is empty");
    }
    return vector_get(stack->data, vector_size(stack->data) - 1);
}

void stack_pop(Stack *stack)
{
    if (vector_size(stack->data) == 0)
    {
        throw std::runtime_error("Stack is empty");
    }
    vector_pop_back(stack->data);
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->data) == 0;
}