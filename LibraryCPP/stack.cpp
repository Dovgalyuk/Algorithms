#include "stack.h"
#include "vector.h"
struct Stack
{
    Vector *vector;

    Stack() {
        vector = vector_create();
    }
    ~Stack() {
        delete vector;
    }

};

Stack *stack_create()
{
    return new Stack;
}

void stack_delete(Stack *stack)
{
    // TODO: free stack elements
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    vector_resize(stack->vector, vector_size(stack->vector) + 1);
    vector_set(stack->vector, vector_size(stack->vector) - 1, data);
}

Data stack_get(const Stack *stack)
{
    return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void stack_pop(Stack *stack)
{
    vector_resize(stack->vector, vector_size(stack->vector) - 1);
}

bool stack_empty(const Stack *stack)
{
    return !((bool)vector_size(stack->vector));
}

size_t stack_size(const Stack *stack)
{
    return vector_size(stack->vector);
}