#include <stdlib.h>
#include "stack.h"
#include "vector.h"

typedef struct Stack
{
	Vector* vector;
} Stack;

Stack* stack_create(FFree f)
{
	Stack* newstack = (Stack*)malloc(sizeof(Stack));
	newstack->vector = vector_create(f);
	return newstack;
}

void stack_delete(Stack* stack)
{
	vector_delete(stack->vector);
	free(stack);
}

void stack_push(Stack* stack, Data data)
{
	size_t i = vector_size(stack->vector);
	vector_resize(stack->vector, i + 1);
	vector_set(stack->vector, i, data);
}

Data stack_get(const Stack* stack)
{
	return vector_get(stack->vector, vector_size(stack->vector) - 1);
}

void stack_pop(Stack* stack)
{
	vector_resize(stack->vector, vector_size(stack->vector) - 1);
}

bool stack_empty(const Stack* stack)
{
	if (vector_size(stack->vector) == 0)
		return true;
	return false;
}
