#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct Stack {
	List* list;
};

// �������� ������� �����
Stack *stack_create() {
	Stack* stack = new Stack;
	stack->list = list_create();
	return stack;
}

// �������� �����
void stack_delete(Stack *stack) {
	if (stack != NULL) {
		list_delete(stack->list);
		delete stack;
	}
}

// ��������� �������� � ����
void stack_push(Stack *stack, int Data) {
	if (stack != NULL) {
		list_insert(stack->list, Data);
	}

}

// ��������� ���������� �������� �����
int stack_get(Stack *stack) {
	if (stack != NULL) {
		ListItem* item = list_first(stack->list);
		int a = list_item_data(item);
		return a;
	}

	return 0;
}

// ������������ �������� �� �����
void stack_pop(Stack *stack) {
	if (stack != NULL) {
			ListItem* item = list_first(stack->list);
			list_erase(stack->list, item);
		}
}

// �������� ����� �� ������� ���������
bool stack_empty(Stack *stack) {
	return list_first(stack->list) == NULL;
}
