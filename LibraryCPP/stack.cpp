#include "stack.h"
#include "vector.h"
#include <stdexcept>
using namespace std;

Stack* stack_create() {
    Stack* stack = new Stack;
    stack->vector = vector_create();
    return stack;
}

void stack_delete(Stack* stack) {
    vector_delete(stack->vector);
    delete stack;
}

void stack_push(Stack* stack, Data data) {
    vector_resize(stack->vector, vector_size(stack->vector) + 1);
    stack->vector->data[stack->vector->size - 1] = data;
}

Data stack_get(const Stack* stack) {
    if (stack_empty(stack)) {
        throw std::out_of_range("Stack is empty");
    }
    return stack->vector->data[stack->vector->size - 1];
}

void stack_pop(Stack* stack) {
    if (stack_empty(stack)) {
        throw std::out_of_range("Stack is empty");
    }
    stack->vector->size--;
}

bool stack_empty(const Stack* stack) {
    return vector_size(stack->vector) == 0;

}
