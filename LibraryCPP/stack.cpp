#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector* data;
};

Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->data = vector_create();
    return stack;
   // return new Stack;
}

void stack_delete(Stack *stack)
{
    // TODO: free stack elements
    vector_delete(stack->data);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    Vector* vec = stack->data;
    vector_resize(vec, vector_size(vec)+1);
    vector_set(vec, vector_size(vec) - 1, data);
}

Data stack_get(const Stack *stack)
{
    Vector* vec = stack->data;
    return vector_get(vec, vector_size(vec) - 1);
   // return (Data)0;
}

void stack_pop(Stack *stack)
{
    Vector* vec = stack->data;
    if (!stack_empty(stack))
    {
        vector_resize(vec, vector_size(vec) - 1);
    }
}

bool stack_empty(const Stack *stack)
{
    return (vector_size(stack->data) == 0);
    //return true;
}
