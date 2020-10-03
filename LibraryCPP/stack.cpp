#include "stack.h"

Stack* stack_create()
{
	Stack* new_stack = new Stack;
	new_stack->list = nullptr;
	return new_stack;
};

void stack_delete(Stack* stack)
{
	if (stack_empty(stack) == false)
	{
		list_delete(stack->list);
		delete stack;
	}
}

void stack_push(Stack* stack, const char* str)
{
	if (stack_empty(stack) == true)
	{
		stack->list = list_create();
		list_insert(stack->list, str);
		list_erase_next(stack->list, stack->list->first);
	}
	else list_insert(stack->list, str);
}

Data stack_get_dt(const Stack* stack)
{
	return list_item_dt(stack->list->first);
}

Operation stack_get_op(const Stack* stack)
{
	return list_item_op(stack->list->first);
}

void stack_pop(Stack* stack)
{
	if (stack_empty(stack) == true)
		return;
	else
	{
		ListItem* temp = stack->list->first->next;
		if (temp != nullptr)
		{
			delete stack->list->first;
			stack->list->first = temp;
		}
		else
		{
			delete stack->list;
			stack->list = nullptr;
		}
	}
}

bool stack_empty(const Stack* stack)
{
	if (stack->list == nullptr)
		return true;
	else return false;
}