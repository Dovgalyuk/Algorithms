#include <stdlib.h>
#include "stack.h"
#include "vector.h"
struct Stack
{
	Vector* vector;
	int size_t;
};

Stack* stack_create()
{
	Stack* a = new Stack;
	a->vector = vector_create();
	a->size_t = 0;
	return a;
}

void stack_delete(Stack* stack)
{
	vector_delete(stack->vector);
	delete stack;
}

void stack_push(Stack* stack, Data data)
{
	vector_set(stack->vector, stack->size_t, data);
	stack->size_t += 1;
}

Data stack_get(const Stack* stack)
{
	return vector_get(stack->vector, stack->size_t - 1);
}

void stack_pop(Stack* stack)
{
	vector_resize(stack->vector, stack->size_t - 1);
	stack->size_t -= 1;
}

bool stack_empty(const Stack* stack)
{
	if (stack->size_t == 0)
		return true;
	else return false;
}