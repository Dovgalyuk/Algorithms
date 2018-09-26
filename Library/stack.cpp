#include <stdlib.h>
#include "stack.h"
#include <vector.h>

#define VECTOR stack->top 

struct Stack
{
	Vector *top;
};

Stack *stack_create()
{
	Stack *stack = new Stack;
	stack->top = vector_create();
    return stack;
}

void stack_delete(Stack *stack)
{
	vector_delete(stack->top);
	delete stack;
}

void stack_push(Stack *stack, int Data)
{
	vector_set(VECTOR, vector_size(VECTOR), Data);
}

int stack_get(Stack *stack)
{
	if (!stack_empty(stack)) {
		return vector_get(VECTOR, vector_size(VECTOR) - 1);
	}
	else {
		std::cout << "Stack is empty" << std::endl;
		exit(0);
	}
}

void stack_pop(Stack *stack)
{
	if (!stack_empty(stack))
		vector_resize(VECTOR, vector_size(VECTOR) - 1);
	else
		std::cout << "Stack is empty" << std::endl;
}

bool stack_empty(Stack *stack)
{
	if (vector_size(VECTOR) < 1)
		return true;
	else
		return false;
}
