#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct Stack
{
	List* cont;
};

Stack* stack_create()
{
	Stack* temp;
	temp = new Stack;
	temp->cont = list_create();
	return temp;
}

void stack_delete(Stack* stack)
{
	list_delete(stack->cont);
	delete stack;
}

void stack_push(Stack* stack, Data data)
{
	list_insert(stack->cont, data);
}

Data stack_get(const Stack* stack)
{
	return list_item_data(list_first(stack->cont));
}

void stack_pop(Stack* stack)
{
	list_erase(stack->cont, list_first(stack->cont));
}

bool stack_empty(const Stack* stack)
{
	return !(list_first(stack->cont));
}