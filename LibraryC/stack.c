#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

typedef struct Stack
{
    Vector *vector;
} Stack;

Stack *stack_create()
{
    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Ошибка выделения памяти для стека\n");
        return NULL;
    }
    stack->vector = vector_create(4, NULL);
    if (stack->vector == NULL) {
        free(stack);
        printf("Ошибка выделения памяти для вектора в стеке\n");
        return NULL;
    }
    return stack;
}

Vector *stack_get_vector(Stack *stack) {
    return stack->vector;
}

void stack_delete(Stack *stack)
{
    if (stack == NULL) {
        return;
    }
    vector_delete(stack->vector);
    free(stack);
}

void stack_push(Stack *stack, Data data)
{
    push_back(stack->vector, data);
}

Data stack_get(const Stack *stack, size_t index)
{
    return vector_get(stack->vector, index);
}

Data stack_pop(Stack *stack)
{
    return pop_back(stack->vector);
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->vector) == 0;
}
