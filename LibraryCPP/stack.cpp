#include "stack.h"
#include "vector.h"

struct Stack {
    Vector *vec;
};

Stack *stack_create() {
    Stack *s = new Stack;
    s->vec = vector_create();
    return s;
}

void stack_delete(Stack *stack) {
    if (stack) {
        vector_delete(stack->vec);
        delete stack;
    }
}

void stack_push(Stack *stack, Data data) {
    size_t sz = vector_size(stack->vec);
    vector_resize(stack->vec, sz + 1);
    vector_set(stack->vec, sz, data);
}

Data stack_get(const Stack *stack) {
    size_t sz = vector_size(stack->vec);
    if (sz > 0) {
        return vector_get(stack->vec, sz - 1);
    }
    return (Data)0;
}

void stack_pop(Stack *stack) {
    size_t sz = vector_size(stack->vec);
    if (sz > 0) {
        vector_resize(stack->vec, sz - 1);
    }
}

bool stack_empty(const Stack *stack) {
    return vector_size(stack->vec) == 0;
}