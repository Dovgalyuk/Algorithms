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
	for (size_t i = 0; ; i++)
	{
		if (str[i] == ' ' || str[i] == '\0')
		{
			string temp;
			temp.insert(0, str, 0, i);
			if (temp.length() == 1 && !isdigit(temp[0])) //giving string is correct and doesn't contain other characters
				calc_op(stack, temp[0]);
			else
				stack_push(stack, atoi(temp.c_str()));
			if (str[i] == ' ')
			{
				str.erase(0, i+1);
				i = 0;
			}
			else break;
		}
	}
	cout << "The result of operation: " << stack_get(stack) << endl;;
}

int main()
{
	Stack* stack = stack_create();
	calc_proc(stack);
	stack_delete(stack);

	return 0;
}


