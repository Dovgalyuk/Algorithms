#include <cstddef>
#include "stack.h"
#include "list.h"

struct Stack
{
	List* list;
};
Stack* stack_create() {
	Stack* stack = new Stack;
	stack->list = list_create();
	return stack;
}

void stack_delete(Stack* stack) {
	if (stack == NULL) {
		return;
	}
	list_delete(stack->list);
	delete stack;
}

void stack_push(Stack* stack, Data data) {
	if (stack == NULL) {
		return;
	}
	list_insert(stack->list, data);
}

Data stack_get(const Stack* stack) {
	if (stack == NULL || stack->list == NULL) {
		return (Data)0;
	}
	ListItem* first = list_first(stack->list);
	if (first == NULL) {
		return (Data)0;
	}

	return list_item_data(first);
}

void stack_pop(Stack* stack) {
	if (stack == NULL || stack->list == NULL) {
		return;
	}
	list_erase_first(stack->list);
}

bool stack_empty(const Stack* stack) {
	if (stack == NULL || stack->list == NULL) {
		return true;
	}
	return list_first(stack->list) == NULL;
}