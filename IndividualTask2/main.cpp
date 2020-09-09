#include <iostream>
#include "stack.h"

using namespace std;

void calc_op(Stack *stack) //given that each expression is correct and numbers matching symbols '+', '-', '/', '*' mean only those symbols in case Data is int
{
	ListItem* temp_calc = list_first(stack->list);
	if (stack_get(stack) == '+' || stack_get(stack) == '-' || stack_get(stack) == '/' || stack_get(stack) == '*')
	{
		Data temp = 0;
		if (stack_get(stack) == '+')
		{
			temp = list_item_data(list_item_next(temp_calc)) + list_item_data(list_item_next(list_item_next(temp_calc)));
		}
		if (stack_get(stack) == '-')
		{
			temp = list_item_data(list_item_next(list_item_next(temp_calc))) - list_item_data(list_item_next(temp_calc));
		}
		if (stack_get(stack) == '/')
		{
			temp = list_item_data(list_item_next(list_item_next(temp_calc))) / list_item_data(list_item_next(temp_calc));
		}
		if (stack_get(stack) == '*')
		{
			temp = list_item_data(list_item_next(temp_calc)) * list_item_data(list_item_next(list_item_next(temp_calc)));
		}
		temp_calc->next->next->data = temp;
		stack_pop(stack);
		stack_pop(stack);
	}
}

void print_op_list()
{
	cout << "The list of operations: " << endl;
	cout << endl;
	cout << "The number 42 is symbol '*';" << endl;
	cout << "The number 43 is symbol '+';" << endl;
	cout << "The number 45 is symbol '-';" << endl;
	cout << "The number 47 is symbol '/'." << endl;
	cout << endl;
}

void calc_proc(Stack *stack)
{
	print_op_list();
	Data temp_data;
	for (int i = 0; i < 5; i++)
	{
		cout << "Enter the number: ";
		cin >> temp_data;
		cout << endl;
		stack_push(stack, temp_data);
		calc_op(stack);
		if (stack_get(stack) != temp_data)
		{
			cout << "The result of operation: " << stack_get(stack) << endl;
			cout << endl;
		}
	}
}

int main()
{
	Stack* stack_1 = stack_create();
	calc_proc(stack_1);
	stack_delete(stack_1);
	return 0;
}