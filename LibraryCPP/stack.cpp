#include "stack.h"
#include "vector.h"
using namespace std;

struct Stack
{
    Vector* vector;
};

Stack* stack_create()
{
    Stack* stack = new Stack;
    stack->vector = vector_create();
    return stack;
}

void stack_delete(Stack* stack)
{
    vector_delete(stack->vector);
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    vector_push_back(stack->vector, data);
}

Data stack_get(const Stack* stack)
{
    if (vector_size(stack->vector) == 0)
        return 0;
    return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void stack_pop(Stack* stack)
{
    if (vector_size(stack->vector) > 0)
        vector_pop_back(stack->vector);
}

bool stack_empty(const Stack* stack)
{
    return vector_size(stack->vector) == 0;
}