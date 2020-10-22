#include <stdlib.h>
#include "stack.h"
#include <iostream>
#include "stack.h"
#include "vector.h"
struct Stack
{
	Vector* vect;
};

Stack *stack_create()
{
	Stack* stack = new Stack;
	stack->vect = vector_create();
	return stack;
}

void stack_delete(Stack *stack)
{
	vector_delete(stack->vect);
	delete stack;
}

void stack_push(Stack *stack, Data data)
{
	vector_resize(stack->vect, vector_size(stack->vect) + 1);
	vector_set(stack->vect, vector_size(stack->vect) - 1, data);
}

Data stack_get(const Stack *stack)
{
	return vector_get(stack->vect, vector_size(stack->vect) - 1);
}

void stack_pop(Stack* stack)
{
	vector_resize(stack->vect, vector_size(stack->vect) - 1);
}

		bool stack_empty(const Stack * stack)
	{
		return vector_size(stack->vect) == 0 ;
	}
