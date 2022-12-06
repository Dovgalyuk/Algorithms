#include "stack.h"
#include "vector.h"
struct Stack
{
    Vector* vector;

    Stack() {
        this->vector = vector_create();
    }

    ~Stack() {
        vector_delete(this->vector);
    }
};

Stack* stack_create()
{
    return new Stack();
}

void stack_delete(Stack* stack)
{
    // TODO: free stack elements
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    vector_resize(stack->vector, vector_size(stack->vector) + 1);
    vector_set(stack->vector, vector_size(stack->vector) - 1, data );
}

Data stack_get(const Stack* stack)
{
    if (stack_empty(stack)) { throw "Empty stack error"; }
    else { return vector_get(stack->vector, vector_size(stack->vector) - 1); }
    return(Data) 0;
}

void stack_pop(Stack* stack)
{
    stack_empty(stack) ? throw "Empty stack error" :
        vector_resize(stack->vector, vector_size(stack->vector) - 1);
}

bool stack_empty(const Stack* stack)
{
    return vector_size(stack->vector) == 0;
}
