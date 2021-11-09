#include "stack.h"
#include "vector.cpp"

struct Stack
{
    Vector* vector;
    Stack(){
    vector = vector_create();
    vector_resize(vector, 0);
    }
};

Stack *stack_create()
{
    return new Stack;
}

void stack_delete(Stack* stack)
{
    vector_delete(stack->vector);
}

void stack_push(Stack *stack, Data data)
{
    vector_resize(stack->vector,vector_size(stack->vector)+1);
    vector_set(stack->vector,vector_size(stack->vector)-1,data);
}

Data stack_get(const Stack *stack)
{
    return vector_get(stack->vector,vector_size(stack->vector)-1);
}

void stack_pop(Stack *stack)
{
    vector_resize(stack->vector,vector_size(stack->vector)-1);
}

bool stack_empty(const Stack *stack)
{
    if (vector_size(stack->vector)>0)
        return false;
    else return true;
}
