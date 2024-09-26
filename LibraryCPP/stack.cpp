#include "stack.h"
#include "vector.h"

// Structure to represent the stack
struct Stack {
    Vector* vector; // Internal vector for storing stack elements
};

// Creates a new stack
Stack* stack_create() {
    Stack* stack = new Stack;
    stack->vector = vector_create();
    return stack;
}

// Deletes the stack, freeing the memory
void stack_delete(Stack* stack) {
    vector_delete(stack->vector);
    delete stack;
}

// Pushes data onto the top of the stack
void stack_push(Stack* stack, Data data) {
    size_t size = vector_size(stack->vector);
    vector_resize(stack->vector, size + 1);
    vector_set(stack->vector, size, data);
}

// Retrieves the last element from the stack
Data stack_get(const Stack* stack) {
    size_t size = vector_size(stack->vector);
    if (size > 0) {
        return vector_get(stack->vector, size - 1);
    }
    return 0;
}

// Removes the last element from the stack
void stack_pop(Stack* stack) {
    size_t size = vector_size(stack->vector);
    if (size > 0) {
        vector_resize(stack->vector, size - 1);
    }
}

// Returns true if the stack is empty
bool stack_empty(const Stack* stack) {
    return vector_size(stack->vector) == 0;
}