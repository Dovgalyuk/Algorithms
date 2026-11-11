#include "stack.h"
#include "vector.h"

struct Stack {
    Vector *vector = nullptr;

    Stack() {
        vector = vector_create();
    }

    ~Stack() {
        if (vector) {
            vector_delete(vector);
        }
    }
};

Stack *stack_create()
{
    return new Stack;
}

void stack_delete(Stack *stack)
{
    // TODO: free stack elements
    delete stack;
}

void stack_push(Stack *stack, Data data) {
    if (!stack || !stack->vector) return;

    vector_set(stack->vector, vector_size(stack->vector), data);
}

Data stack_get(const Stack *stack)
{
    if (stack_empty(stack)) return Data();

    return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void stack_pop(Stack *stack)
{
    if (stack_empty(stack)) return;

    vector_resize(stack->vector, vector_size(stack->vector) - 1);
}

bool stack_empty(const Stack *stack)
{
    if (!stack || !stack->vector || vector_size(stack->vector) == 0) return true;

    return false;
}
