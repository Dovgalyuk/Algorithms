#include <stdlib.h>
#include "stack.h"
#include "vector.h"

struct Stack
{
	Vector* top;
};

Stack* stack_create()
{
	Stack* stack = new Stack;
	stack->top = vector_create();
	return stack;
}

void stack_delete(Stack* stack)
{
	vector_delete(stack->top);
	delete stack;
}

void stack_push(Stack* stack, Data data)
{
	vector_set(stack->top, vector_size(stack->top), data);
}

Data stack_get(const Stack* stack)
{
	return vector_get(stack->top, vector_size(stack->top) - 1);
}

void stack_pop(Stack* stack)
{
	vector_resize(stack->top, vector_size(stack->top) - 1);
}

bool stack_empty(const Stack* stack)
{
	return !vector_size(stack->top);
}
