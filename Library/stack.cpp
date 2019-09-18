#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct Stack
{
	List* list;
	size_t counter;
};

Stack *stack_create()
{
	Stack* temp = new Stack;
	temp->list = list_create();
	temp->counter = 0;
	return temp;
}

void stack_delete(Stack *stack)
{
	list_delete(stack->list);
	delete stack;
}

void stack_push(Stack *stack, sData data)
{
	List* temp = stack->list;
	list_insert(temp, data);
	stack->counter++;
}

sData stack_get(const Stack *stack)
{
	if (list_first(stack->list) == NULL) return "";
	else return list_item_data(list_first(stack->list));
}

void stack_pop(Stack *stack)
{
	List* temp = stack->list;
	list_erase(temp, list_first(stack->list));
	stack->counter--;
}

bool stack_empty(const Stack *stack)
{
	return stack->counter == 0;
}
