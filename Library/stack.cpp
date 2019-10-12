#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct Stack
{
	List* source;
};

Stack *stack_create()
{
	Stack* temp;
	temp = new Stack;
	temp->source = list_create();
    return temp;
}

void stack_delete(Stack *stack)
{
	list_delete(stack->source);
}

void stack_push(Stack *stack, Data data)
{
	list_insert(stack->source, data);
}

Data stack_get(const Stack *stack)
{
    return list_item_data(list_first(stack->source));
}

void stack_pop(Stack *stack)
{
	list_erase(stack->source, list_first(stack->source));
}

bool stack_empty(const Stack *stack)
{
    return !(list_first(stack->source));
}
