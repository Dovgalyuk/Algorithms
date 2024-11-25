#include "stack.h"
#include "vector.h"

//structure of the stack with module of vector 
struct Stack
{
    Vector* vector;
};

//creating new stack
Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->vector = vector_create();
    return stack;
}

//deleting fully stack and also freeing up memory
void stack_delete(Stack* stack)
{
    vector_delete(stack->vector);
    delete stack;
}

//adding(pushing) elements on the top of the stack
void stack_push(Stack* stack, Data data)
{
    size_t size = vector_size(stack->vector);
    vector_resize(stack->vector, size+1);
    vector_set(stack->vector, size, data);
}   

//receiving the last element from stack 
Data stack_get(const Stack* stack)
{
    size_t size = vector_size(stack->vector);

    if(size>0){
        return vector_get(stack->vector, size-1);
    }

    return 0;
}

//removing the last element from stack 
void stack_pop(Stack *stack)
{
    size_t size = vector_size(stack->vector);
    
    if(size>0){
        vector_resize(stack->vector, size-1);
    }
}

//returning true if stack is empty
bool stack_empty(const Stack *stack)
{
    return vector_size(stack->vector) == 0;
}
