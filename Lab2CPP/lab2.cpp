#include <iostream>
#include <string>
#include <fstream>
#include "stack.h"

unsigned int priority(const char symbol)
{
	if (symbol == '*' || symbol == '/')
		return 3;
	if (symbol == '+' || symbol == '-')
		return 2;
	if (symbol == '(')
		return 1;

	return 0;
}

std::string RPN(std::string data)
{
	Stack* stack = stack_create();
	std::string res = "";
	for (size_t i = 0; i < data.size(); i++)
	{
		if (isdigit(data[i]))
		{
			res += data[i];
		}
		else
		{
			if (data[i] == '(')
			{
				stack_push(stack, data[i]);
			}
			else if (data[i] == ')')
			{
				while (!stack_empty(stack) && stack_get(stack) != '(')
				{
					res += stack_get(stack);
					stack_pop(stack);
				}
				if (!stack_empty(stack) && stack_get(stack) == '(')
				{
					stack_pop(stack);
				}
			}
			else
			{
				while (!stack_empty(stack) && priority(stack_get(stack)) >= priority(data[i]))
				{
					res += stack_get(stack);
					stack_pop(stack);
				}
				stack_push(stack, data[i]);
			}
		}
	}

	while (!stack_empty(stack))
	{
		res += stack_get(stack);
		stack_pop(stack);
	}

	stack_delete(stack);
	return res;
}

Data solve(std::string data)
{
	Stack* stack = stack_create();
	for (size_t i = 0; i < data.size(); i++)
	{
		if (isdigit(data[i]))
			stack_push(stack, data[i] - '0');
		else
		{
			Data val1 = stack_get(stack);
			stack_pop(stack);
			Data val2 = stack_get(stack);
			stack_pop(stack);
			Data res = 0;

			switch (data[i])
			{
			case '+': res = val1 + val2;
				break;
			case '-': res = val1 - val2;
				break;
			case '*': res = val1 * val2;
				break;
			case '/': res = val1 / val2;
				break;
			}

			stack_push(stack, res);
		}
	}

	Data res = stack_get(stack);
	stack_delete(stack);
	return res;
}

std::string calculate(std::string expr)
{
	expr = RPN(expr);
	expr = std::to_string(solve(expr));

	return expr;
}

int main()
{
	std::string input = "";
	std::cin >> input;
	std::cout << calculate(input);
	return 0;
}
