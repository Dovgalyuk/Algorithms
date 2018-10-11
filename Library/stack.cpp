#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct Stack
{
	List *list;
};

Stack *stack_create()
{
	Stack *tmp = new Stack;
	tmp->list = list_create();
	return tmp;
}

void stack_delete(Stack *stack)
{
	list_delete(stack->list);
	delete stack;
}

void stack_push(Stack *stack, data data)
{
	List *tmp = stack->list;
	list_insert(tmp, data);
}

data stack_get(const Stack *stack)
{
	return list_item_data(list_first(stack->list));
}

void stack_pop(Stack *stack)
{
	List *tmp = stack->list;
	list_erase(tmp, list_first(stack->list));
}

bool stack_empty(const Stack *stack)
{
	return list_first(stack->list) == NULL;
}
