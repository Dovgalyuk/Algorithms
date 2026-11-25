#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector *data;
};

Stack *stack_create()
{
    return new Stack{vector_create()};
}

void stack_delete(Stack *stack)
{
    // TODO: free stack elements
    if (stack == nullptr) {
        return;
    }
    vector_delete(stack->data);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    if (stack == nullptr) {
        throw std::invalid_argument("Stack is null");
    }

    size_t size = vector_size(stack->data);
    vector_resize(stack->data, size + 1);
    vector_set(stack->data, size, data);
}

Data stack_get(const Stack *stack)
{
    if (stack_empty(stack)) {
        throw std::underflow_error("Stack is empty");
    }
    return vector_get(stack->data, vector_size(stack->data) - 1);
}

void stack_pop(Stack *stack)
{
    if (stack_empty(stack)) {
        throw std::underflow_error("Stack is empty");
    }
    vector_resize(stack->data, vector_size(stack->data) - 1);
}

bool stack_empty(const Stack *stack)
{
    return stack == nullptr || vector_size(stack->data) == 0;
}
