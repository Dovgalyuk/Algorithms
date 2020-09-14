#include <stdlib.h>
#include <iostream>
#include "stack.h"
#include "vector.h"

struct Stack
{
	Vector* vct;
};

Stack *stack_create()
{
	Stack* stack = new Stack;
	stack->vct = vector_create();
	return stack;
}

void stack_delete(Stack *stack)
{
    // TODO: free stack elements
	vector_delete(stack->vct);
    delete stack;
}

void stack_push(Stack *stack, Data data)
{
	vector_resize(stack->vct, vector_size(stack->vct) + 1);
	vector_set(stack->vct, vector_size(stack->vct) - 1, data);
}

Data stack_get(const Stack *stack)
{
	return vector_get(stack->vct, vector_size(stack->vct) - 1);
}

void stack_pop(Stack *stack)
{
	vector_resize(stack->vct, vector_size(stack->vct) - 1);
}

bool stack_empty(const Stack *stack)
{
    return vector_size(stack->vct) == 0 ? true : false;
}
