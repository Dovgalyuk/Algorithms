#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct Stack
{
	List* list;
};

Stack *stack_create()
{
	Stack* temp = new Stack;
	temp->list = list_create();
	return temp;
}

void stack_delete(Stack *stack)
{
	list_delete(stack->list);
	delete stack;
}

void stack_push(Stack *stack, Data data)
{
	List* temp = stack->list;
	list_insert(temp, data);
}

Data stack_get(const Stack *stack)
{
	if (list_first(stack->list) == NULL) return "";
	else return list_item_data(list_first(stack->list));
}

void stack_pop(Stack *stack)
{
	List* temp = stack->list;
	list_erase(temp, list_first(stack->list));
}

bool stack_empty(const Stack *stack)
{
	return list_first(stack->list) == NULL;
}
