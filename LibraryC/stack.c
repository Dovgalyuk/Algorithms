#include <stdlib.h>
#include "vector.h"
#include "stack.h"
typedef struct Stack
{
    Vector* vector; 
} Stack;

Stack* stack_create(FFree f)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    
    stack->vector = vector_create(f);
        
   
    return stack;
}

void stack_delete(Stack* stack)
{
    if (stack) {
        vector_delete(stack->vector);
        free(stack);
    }
}

void stack_push(Stack* stack, Data value)
{
    
    size_t currentSize = vector_size(stack->vector);
    vector_resize(stack->vector, currentSize +1);
    vector_set(stack->vector, currentSize, value);
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
    
    return vector_size(stack->vector) == 0;
}
size_t stack_size(const Stack* stack)
{
    return vector_size(stack->vector);
}
