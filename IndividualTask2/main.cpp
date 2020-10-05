#include <iostream>
#include <stdio.h>
#include "stack.h"

using namespace std;

void calc_op(Stack* stack, char operation, int &i)
{
	Data a = stack_get(stack);
	stack_pop(stack);
	if (stack_empty(stack))
	{
		stack_push(stack, a);
		i--;
		cout << "Error, incorrect input, please try again" << endl;
		cout << endl;
		return;
	}
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

Data cast_dt(const char* str)
{
	return atoi(str);
}

char cast_op(const char* str)
{
	return str[0];
}

bool is_dt(const char* str)
{
	const char* temp_num = "0123456789";
	for (int i = 0; i < strlen(str); i++)
	{
		if (!strchr(temp_num, str[i]))
			return false;
	}
	return true;
}

bool is_op(const char* str)
{
	const char* temp_op = "+-/*";
	if (!strchr(temp_op, str[0]) || str[1] != NULL)
		return false;
	else return true;
}

void calc_proc(Stack* stack)
{
	for (int i = 0; i < 5; i++)
	{
		char str[256] = "";
		cout << "Enter number or operation: ";
		cin >> str;
		cout << endl;
		if (is_dt(str))
		{
			stack_push(stack, cast_dt(str));
		}
		else if (is_op(str) && stack_empty(stack) != true)
		{
			calc_op(stack, cast_op(str), i);
		}
		else
		{
			cout << "Error, incorrect input, please try again" << endl;
			cout << endl;
		}
		cin.clear();
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