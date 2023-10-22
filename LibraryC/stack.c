#include <stdlib.h>
#include <assert.h>
#include "vector.h"

typedef struct Stack
{
    Vector* vector; // Вектор для хранения данных в стеке
} Stack;

Stack* stack_create()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack) {
        stack->vector = vector_create(NULL);
        if (!stack->vector) {
            free(stack);
            return NULL;
        }
    }
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
    
    size_t currentSize = vector_size(stack->vector);
    if (currentSize > 0) {
        vector_resize(stack->vector, currentSize - 1);
    } 
}


int stack_empty(const Stack* stack)
{
    
    return vector_size(stack->vector) == 0;
}
size_t stack_size(const Stack* stack)
{
    return vector_size(stack->vector);
}
