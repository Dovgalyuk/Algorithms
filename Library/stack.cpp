#include <stdlib.h>
#include "stack.h"
#include "array.h"

const size_t MAX_SIZE = 20;

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
	stack->arr = array_create(MAX_SIZE);
	return stack;
}

void stack_delete(Stack* stack)
{
	array_delete(stack->arr);
}

void stack_push(Stack* stack, Data data)
{
	if (stack->top >= array_size(stack->arr))
	{
		Array* n_array = array_create(2 * array_size(stack->arr));
		for (int i = 0; i < array_size(stack->arr); ++i)
		{
			array_set(n_array, i, array_get(stack->arr, i));
		}
		stack->arr = n_array;
	}
	array_set(stack->arr, stack->top, data);
	stack->top++;
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