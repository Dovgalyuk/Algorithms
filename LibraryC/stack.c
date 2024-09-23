#include <stdlib.h>
#include "stack.h"
#include "vector.h"

typedef struct Stack
{
    Vector* vector;
} Stack;

Stack *stack_create(FFree f, Data filler)
{
    Stack* stack = malloc(sizeof(Stack));
    stack->vector = vector_create(f, filler);
    return stack;
}

void stack_delete(Stack *stack)
{
    vector_delete(stack->vector);
    free(stack);
}

void stack_push(Stack *stack, Data data)
{
    vector_set(stack->vector, vector_size(stack->vector), data);
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
    if (vector_size(stack->vector) == 0)
        return true;
    else
        return false;
}
