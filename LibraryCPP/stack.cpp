#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector *data;
};

Stack *stack_create()
{
    Stack* stack = new Stack;
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
    vector_set(stack->data, vector_size(stack->data), data);
}

Data stack_get(const Stack *stack)
{
    return stack_empty(stack)? (Data)-1 : vector_get(stack->data, (vector_size(stack->data) - 1) );
}

void stack_pop(Stack *stack)
{
    vector_resize(stack->data, (vector_size(stack->data) - 1) );
}

bool stack_empty(const Stack *stack)
{    
    return (vector_size(stack->data) == 0)? true : false;
}
