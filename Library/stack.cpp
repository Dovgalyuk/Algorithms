#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct Stack
{
	List *list;
};

Stack *stack_create()
{
	Stack *p = new Stack;
	p->list = list_create();
	return p;
}

void stack_delete(Stack *stack)
{
	list_delete(stack->list);
	delete stack;
}

void stack_push(Stack *stack, Data data)
{
	List *p = stack->list;
	list_insert(p, data);
}

Data stack_get(const Stack *stack)
{
	if (stack_empty(stack) == false)
		return list_item_data(list_first(stack->list));
	return NULL;
}

void stack_pop(Stack *stack)
{
	List* p = stack->list;
	list_erase(p, list_first(stack->list));
}

bool stack_empty(const Stack *stack)
{
	if (list_first(stack->list) == NULL) {
		return true;
	}
	else return false;
}
