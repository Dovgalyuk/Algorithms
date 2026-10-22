#include "stack.h"

struct Stack {
    Vector* vector;
};

Stack *stack_create() {
    Stack *s = new Stack();
    s->vector = vector_create();
    return s;
}

void stack_delete(Stack *stack) {
    if (stack) {
        vector_delete(stack->vector);
        delete stack;
    }
}

void stack_push(Stack *stack, Data data) {
    if (!stack) return;
    size_t sz = vector_size(stack->vector);
    vector_resize(stack->vector, sz + 1);
    vector_set(stack->vector, sz, data);
}

Data stack_get(const Stack *stack) {
    if (!stack || vector_size(stack->vector) == 0) return (Data)0;
    return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void stack_pop(Stack *stack) {
    if (!stack) return;
    size_t sz = vector_size(stack->vector);
    if (sz > 0) vector_resize(stack->vector, sz - 1);
}

bool stack_empty(const Stack *stack) {
    return (!stack || vector_size(stack->vector) == 0);
}