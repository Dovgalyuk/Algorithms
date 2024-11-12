#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

struct Stack
{
    Vector *vector;
};

Stack *stack_create()
{
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) {
        fprintf(stderr, "Ошибка выделения памяти для стека\n");
        return NULL;
    }
    stack->vector = vector_create(4, NULL);
    if (!stack->vector) {
        free(stack);
        fprintf(stderr, "Ошибка выделения памяти для вектора в стеке\n");
        return NULL;
    }
    return stack;
}

void stack_delete(Stack *stack)
{
    if (!stack) {
        return;
    }
    vector_delete(stack->vector);
    free(stack);
}

void stack_push(Stack *stack, void *data)
{
    if (!stack) {
        fprintf(stderr, "Ошибка: стек не инициализирован\n");
        return;
    }
    push_back(stack->vector, data);
}

void *stack_get(const Stack *stack)
{
    if (stack_empty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        return NULL;
    }
    return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void *stack_pop(Stack *stack)
{
    if (stack_empty(stack)) {
        fprintf(stderr, "Stack underflow!\n");
        return NULL;
    }
    return pop_back(stack->vector);
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->vector) == 0;
}
