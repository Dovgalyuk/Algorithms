#include <stdlib.h>
#include "stack.h"
#include "vector.h"

struct Stack
{
	Vector* cont;
	size_t size;
};

Stack* stack_create()
{
	Stack* temp = new Stack;
	temp->cont = vector_create();
	temp->size = 0;
	return temp;
}

void stack_delete(Stack* stack)
{
	vector_delete(stack->cont);
	delete stack;
}

void stack_push(Stack* stack, Data data)
{
	vector_set(stack->cont, stack->size, data);
	stack->size++;
}

Data stack_get(const Stack* stack)
{
	return vector_get(stack->cont, stack->size - 1);
}

void stack_pop(Stack* stack)
{
	stack->size--;
}

bool stack_empty(const Stack* stack)
{
	return !stack->size;
}
