#include "stack.h"

Stack* stack_create()
{
	Stack* new_stack = new Stack;
	new_stack->list = nullptr;
	return new_stack;
};

void stack_delete(Stack* stack)
{
	if (stack_empty(stack) != true)
		list_delete(stack->list);
	delete stack;
	stack = nullptr;
}

void stack_push(Stack* stack, Data data)
{
	if (stack_empty(stack))
	{
		stack->list = list_create();
	}
	list_insert(stack->list, data);
}

Data stack_get(const Stack* stack)
{
	return list_get(stack->list->first);
}

void stack_pop(Stack* stack)
{
	if (stack_empty(stack))
		return;
	else
	{
		list_erase_first(stack->list);
		if (stack_empty(stack))
			stack_delete(stack);
	}
}

bool stack_empty(const Stack* stack)
{
	if (stack->list == nullptr || stack == nullptr)
		return true;
	else return false;
}
