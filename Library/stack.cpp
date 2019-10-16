#include <stdlib.h>
#include "stack.h"
#include "array.h"

struct Stack
{
	Array* arr;
	size_t top;
};

Stack* stack_create()
{
	Stack* stack;
	stack = new Stack;
	stack->top = 0;
	stack->arr = array_create(max_size);
	return stack;
}

void stack_delete(Stack* stack)
{
	array_delete(stack->arr);
}

void stack_push(Stack* stack, Data data)
{
	if (stack->top < max_size)
	{
		array_set(stack->arr, stack->top, data);
		stack->top++;
	}
}

Data stack_get(const Stack* stack)
{
	return array_get(stack->arr, stack->top - 1);
}

void stack_pop(Stack* stack)
{
	stack->top--;
}

bool stack_empty(const Stack* stack)
{
	return !stack->top;
}