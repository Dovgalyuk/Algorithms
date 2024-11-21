#include <stdlib.h>
#include "stack.h"
#include "vector.h"

typedef struct Stack {
    Vector *data_vector;
} Stack;

Stack *stack_create(FFree free_func, Data init_filler) {
    Stack *new_stack = malloc(sizeof(Stack));
    new_stack -> data_vector = vector_create(free_func, init_filler);
    return new_stack;
}

void stack_delete(Stack *stack) {
    vector_delete(stack -> data_vector);
    free(stack);
}

void stack_push(Stack *stack, Data new_data) {
    vector_set(stack -> data_vector, vector_size(stack -> data_vector), new_data);
}

Data stack_get(const Stack *stack) {
    return vector_get(stack -> data_vector, vector_size(stack -> data_vector) - 1);
}

void stack_pop(Stack *stack) {
    vector_resize(stack -> data_vector, vector_size(stack -> data_vector) - 1);
}

bool stack_empty(const Stack *stack) {
    if (vector_size(stack -> data_vector) == 0) {
        return true;
    } else {
        return false;
    }
}
