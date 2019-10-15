#include <stdlib.h>
#include "stack.h"
#include "array.h"

struct Stack
{
	Array* cont;
	size_t size;
};

Stack *stack_create()
{
	Stack* temp = new Stack;
	temp->cont = array_create(100);
	temp->size = 0;
	return temp;
}

void stack_delete(Stack *stack)
{
	array_delete(stack->cont);
	delete stack;
}

void stack_push(Stack *stack, Data data)
{
	if (stack->size >= array_size(stack->cont))
	{
		Array* temp = array_create(array_size(stack->cont) * 2);
		for (int i = 0; i < array_size(stack->cont); i++)
			array_set(temp, i, array_get(stack->cont, i));
		array_delete(stack->cont);
		stack->cont = temp;
	}
	array_set(stack->cont, stack->size, data);
	stack->size++;
}

Data stack_get(const Stack *stack)
{
    return array_get(stack->cont, stack->size - 1);
}

void stack_pop(Stack *stack)
{
	stack->size--;
}

bool stack_empty(const Stack *stack)
{
    return !stack->size;
}
