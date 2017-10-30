#include <stdlib.h>
#include "stack.h"
#include "list.h"
#include <string.h>


struct Stack
{
	List *list;
};

// 
Stack *stack_create()
{
	Stack *item = new Stack;
	item->list = list_create();
	return item;
}

//
void stack_delete(Stack *stack)
{
	list_delete(stack->list);
}

// 
void stack_push(Stack *stack, int Data)
{
	List *list = stack->list;
	list_insert(list, Data);
}

// 
int stack_get(Stack *stack)
{
	return list_item_data(list_first(stack->list));
}

// 
void stack_pop(Stack *stack)
{
	List *list = stack->list;
	list_erase(list, list_first(stack->list)); //удалить заданный элемент списка
}

// 
bool stack_empty(Stack *stack)
{
	if (list_first(stack->list) == NULL)
	{
		return true;
	}
	else
		return false;
}
