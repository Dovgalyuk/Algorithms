#include "stack.h"
#include "vector.h"

struct Stack {
    Vector *vector;

    Stack() {
        this->vector = vector_create();
    }

    ~Stack() {
        vector_delete(this->vector);
    }
};

Stack *stack_create() {
    return new Stack();
}

void stack_delete(Stack *stack) {
    delete stack;
}

void stack_push(Stack *stack, Data data) {
    size_t size = vector_size(stack->vector);
    vector_resize(stack->vector, size + 1);
    vector_set(stack->vector, size, data);
}

Data stack_get(const Stack *stack) {
    if (stack_empty(stack))
        throw "ERROR: Stack empty";
    else
        return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void stack_pop(Stack *stack) {
    if (stack_empty(stack))
        throw "ERROR: Stack empty";
    else
        vector_resize(stack->vector, vector_size(stack->vector) - 1);
}

bool stack_empty(const Stack *stack) {
    return vector_size(stack->vector) == 0;
}
