#include "stack.h"
#include <stdexcept>

struct Stack {
    Vector* vector;  
};

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
    vector_resize(stack->vector, vector_size(stack->vector) + 1);  // ����������� ������ �������
    vector_set(stack->vector, vector_size(stack->vector) - 1, data);  // ��������� �������
}

Data stack_get(const Stack* stack) {
    if (stack_empty(stack)) {
        throw std::underflow_error("Stack is empty");
    }
    return vector_get(stack->vector, vector_size(stack->vector) - 1);  // ���������� ��������� �������
}

void stack_pop(Stack* stack) {
    if (stack_empty(stack)) {
        throw std::underflow_error("Stack is empty");
    }
    vector_resize(stack->vector, vector_size(stack->vector) - 1);  // ��������� ������ �������
}

bool stack_empty(const Stack* stack) {
    return vector_size(stack->vector) == 0;
}