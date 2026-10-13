#include "stack.h"
#include "vector.h"
#include <iostream>

using namespace std;

struct Stack
{
    Vector* vec;
};

Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->vec = vector_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    if (stack) {
        vector_delete(stack->vec);
        delete stack;
    }
}

void stack_push(Stack *stack, Data data)
{
    size_t n = vector_size(stack->vec);
    vector_resize(stack->vec, n + 1);
    vector_set(stack->vec, n, data);
}

Data stack_get(const Stack *stack)
{
    size_t n = vector_size(stack->vec);
    if (n == 0) {
        return 0;
    }
    return vector_get(stack->vec, n - 1);
}

void stack_pop(Stack *stack)
{
    size_t n = vector_size(stack->vec);
    if (n > 0) {
        vector_resize(stack->vec, n - 1);
    }
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->vec) == 0;
}

void printStack(Stack* stack) {
    if (stack_empty(stack)) {
        cout << endl;
        cout << "Пусто";
    }
    size_t size = vector_size(stack->vec);
    for (size_t i = 0; i < size; i++) {
        cout << vector_get(stack->vec, i);
        if (i != size - 1) {
            cout << " ";
        }
    }
    cout << endl;
}