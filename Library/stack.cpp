#include <stdlib.h>
#include "array.h"
#include "stack.h"

const size_t INITIAL_SIZE = 100;
const size_t MULTIPLIER = 2;

struct Stack
{
	Array* array;
	size_t top;
};

Stack *stack_create()
{
	Stack* newStack = new Stack();
	newStack->array = array_create(INITIAL_SIZE);
	newStack->top = 0;
    return newStack;
}

void stack_delete(Stack *stack)
{
	array_delete(stack->array);
	delete stack;
}

void stack_push(Stack *stack, Data data)
{

	size_t arrSize = array_size(stack->array);
	if (stack->top >= arrSize) {
		Array* newArr = array_create(arrSize * MULTIPLIER);
		for (size_t i = 0; i < arrSize; i++) {
			array_set(newArr, i, array_get(stack->array, i));
		}
		array_delete(stack->array);
		stack->array = newArr;
	}

	array_set(stack->array, stack->top, data);
	stack->top++;
}

Data stack_get(const Stack *stack)
{
    return array_get(stack->array, stack->top - 1);
}

void stack_pop(Stack* stack)
{
	stack->top--;
}

bool stack_empty(const Stack *stack)
{
    return (stack->top == 0);
}
