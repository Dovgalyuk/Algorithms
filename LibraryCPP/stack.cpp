#include <stdlib.h>
#include "stack.h"

Stack* stack_create()
{
	Stack* stack_temp = new Stack;
	stack_temp->list = nullptr;
	return stack_temp;
};

Data stack_get(const Stack *stack)
{
    return list_item_data(stack->list->first);
}

bool stack_empty(const Stack *stack)
{
	if (stack->list == nullptr)
		return true;
	else return false;
}

void stack_pop(Stack* stack)
{
	if (stack_empty(stack) == 1)
		return;
	else
		list_erase(stack->list, list_first(stack->list));
}

void stack_push(Stack *stack, Data data)
{
	if (stack_empty(stack) == 1)
	{
		List* temp_list = list_create();
		stack->list = temp_list;
		ListItem* temp = new ListItem;
		stack->list->first = temp;
		temp->data = data;
		temp->next = nullptr;
	}
	else
	{
		list_insert(stack->list, data);
	}
}

void stack_delete(Stack* stack)
{
	if (stack_empty == 0)
		list_delete(stack->list);
	delete stack;
}