#include "stack.h"
#include "vector.h"
#include "iostream"

struct Stack
{
    Vector* vector;
    Stack() {
        this->vector= vector_create(0);
    }
};

Stack* stack_copy(const Stack* stack)
{
    Stack* newStack = stack_create();
    size_t stackSize = vector_size(stack->vector);

    for (size_t i = 0; i < stackSize; i++)
    {
        Data data = vector_get(stack->vector, i);
        stack_push(newStack, data);
    }

    return newStack;
}

Stack* stack_create()
{
    Stack* stack = new Stack;
    return stack;
}

void stack_delete(Stack* stack)
{
    vector_delete(stack->vector);
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    size_t index = vector_size(stack->vector);
    vector_resize(stack->vector, index + 1);
    vector_set(stack->vector, index, data);
}

Data stack_get(const Stack* stack)
{
    return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void stack_pop(Stack* stack)
{
    vector_resize(stack->vector, vector_size(stack->vector) - 1);
}

bool stack_empty(const Stack* stack)
{   
    size_t size = vector_size(stack->vector);
    if (size == 0) {
        return true;
    }
    else {
        return false;
    }
}

