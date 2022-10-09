#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector* vector;
    size_t last;

    Stack() {
        this->vector = vector_create();
        this->last = -1;
    }

    ~Stack() {
        vector_delete(this->vector);
    }
};

Stack *stack_create()
{
    return new Stack();
}

void stack_delete(Stack *stack)
{
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    size_t size = vector_size(stack->vector);
    if (++stack->last == size)
        vector_resize(stack->vector,size + 1);
    vector_set(stack->vector,stack->last, data);
}

Data stack_get(const Stack *stack)
{
    return vector_get(stack->vector,stack->last);
}

void stack_pop(Stack *stack)
{
    vector_resize(stack->vector,stack->last--);
}

bool stack_empty(const Stack *stack)
{
    return stack->last == -1;
}
