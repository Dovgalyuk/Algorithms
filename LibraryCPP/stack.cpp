#include "stack.h"
#include "vector.h"

struct Stack
{
    Vector* vector;
};

Stack *stack_create()
{
    Stack* stack = new Stack;
    stack->vector = vector_create();
    return stack;
}

void stack_delete(Stack *stack)
{
    vector_delete(stack->vector);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
    vector_set(stack->vector, vector_size(stack->vector), data);
}

Data stack_get(const Stack *stack)
{
    Data ret = vector_get(stack->vector, vector_size(stack->vector) - 1);
    return ret;
}

/*
stack_take создан, чтобы забирать и удалять одновременно из стека число
*/
Data stack_take(Stack *stack)
{
    Data ret = vector_get(stack->vector, vector_size(stack->vector) - 1);
    stack_pop(stack);
    return ret;
}

void stack_pop(Stack *stack)
{
    vector_resize(stack->vector, vector_size(stack->vector) - 1);
}

bool stack_empty(const Stack *stack)
{
    return stack->vector->size == 0;
}

/*
stack_size создан для проверки колличества элементов, так как stack_empty может быть не удобным
*/
int stack_size(const Stack *stack){
    return stack->vector->size;
}
