#include <stdlib.h>
#include "stack.h"
#include "vector.h"

struct Stack
{
	Vector* cont;
};

Stack *stack_create()
{
	Stack* temp = new Stack;
	temp->cont = vector_create();
	return temp;
}

void stack_delete(Stack *stack)
{
	vector_delete(stack->cont);
	delete stack;
}

void stack_push(Stack *stack, Data data)
{
	vector_set(stack->cont, vector_size(stack->cont), data);
}

Data stack_get(const Stack *stack)
{
	return vector_get(stack->cont, vector_size(stack->cont)-1);
}

void stack_pop(Stack *stack)
{
	vector_resize(stack->cont, vector_size(stack->cont)-1);
}

bool stack_empty(const Stack *stack)
{
	return !vector_size(stack->cont);
}
