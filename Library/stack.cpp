#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct Stack
{
	List *st;
};

Stack *stack_create()
{
	Stack *R = new Stack;
	R->st = list_create();
    return R;
}

void stack_delete(Stack *stack)
{
	list_delete(stack->st);
	delete stack;
}

void stack_push(Stack *stack, Data data)
{
	list_insert(stack->st, data);
}

Data stack_get(const Stack *stack)
{
	Data d = list_item_data (list_first(stack->st));
    return d;
}

void stack_pop(Stack *stack)
{
	list_erase(stack->st, list_first(stack->st));
}

bool stack_empty(const Stack *stack)
{

	if (list_first(stack->st) == NULL) {
		return true;
	}
	return false;
}
