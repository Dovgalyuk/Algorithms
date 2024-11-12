#include "stack.h"




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
    vector_resize(stack->data, stack->data->size+1); 
    vector_set(stack->data, stack->data->size-1, data); 
}


Data stack_get(const Stack *stack)
{
    return vector_get(stack->data, stack->data->size-1); 
}


void stack_pop(Stack *stack)
{
    if (stack->data->size>0)
    {
        vector_resize(stack->data, stack->data->size-1);
    }
}


bool stack_empty(const Stack *stack)
{
    return stack->data->size ==0;
}
