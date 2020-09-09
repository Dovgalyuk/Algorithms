#include <stdlib.h>
#include "stack.h"
#include "list.h"
#include <iostream>

struct Stack
{
	List* list;
};

Stack *stack_create()
{
	Stack* stack = new Stack;
	stack->list = list_create();
	return stack;
}

void stack_delete(Stack *stack)
{
	if (list_first(stack->list) != NULL)
		list_delete(stack->list);
	delete stack;
}

void stack_push(Stack *stack, Data data)
{
	list_insert(stack->list, data);
}

Data stack_get(const Stack *stack)
{
	return list_item_data(list_first(stack->list));
}

void stack_pop(Stack *stack)
{
	if (list_first(stack->list) != NULL)
		list_erase(stack->list, list_first(stack->list));
}

bool stack_empty(const Stack *stack)
{
	if (list_first(stack->list) == NULL)
		return true;
	else
		return false;
}
