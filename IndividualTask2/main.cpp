#include <iostream>
#include <stdio.h>
#include <string>
#include "stack.h"

using namespace std;

void calc_op(Stack* stack, char operation)
{
	Data a = stack_get(stack);
	stack_pop(stack);
	Data b = stack_get(stack);
	stack_pop(stack);
	if (operation == '+')
	{
		stack_push(stack, b + a);
	}
	if (operation == '-')
	{
		stack_push(stack, b - a);
	}
	if (operation == '/')
	{
		stack_push(stack, b / a);
	}
	if (operation == '*')
	{
		stack_push(stack, b * a);
	}
}

void calc_proc(Stack* stack)
{
	string str;
	cout << "Please, enter correct string (characters and numbers must be separated by spaces): ";
	getline(cin, str);
	cout << endl;
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		if (isdigit(str[i]))
		{
			stack_push(stack, atoi(str.c_str() + i));
			if (isdigit(str[i + 1]))
				i++;
		}
		else if (str[i] != ' ')
				calc_op(stack, str[i]);
	}
	cout << "The result of operation: " << stack_get(stack) << endl;
}

int main()
{
	Stack* stack = stack_create();
	calc_proc(stack);
	stack_delete(stack);

	return 0;
}