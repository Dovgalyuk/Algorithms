#include "stack.h"
#include "vector.h"

struct Stack
{
public:
    Vector* vector_base;

    Stack()
    {
        vector_base = vector_create();

    }
    ~Stack()
    {
        vector_delete(vector_base);
    }
};

Stack* stack_create()
{
    return new Stack;
}

void stack_delete(Stack* stack)
{
    // TODO: free stack elements
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    vector_set(stack->vector_base, vector_size(stack->vector_base), data);
}

Data stack_get(const Stack* stack)
{
    if (stack_empty(stack))
    {
        return (Data)0;
    }
    else
    {
        return vector_get(stack->vector_base, vector_size(stack->vector_base) - 1);

    }

}

void stack_pop(Stack* stack)
{

    vector_resize(stack->vector_base, 1);

}

bool stack_empty(const Stack* stack)
{
    return vector_size(stack->vector_base) == 0;
}
