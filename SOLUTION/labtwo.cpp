#include <iostream>
#include <string>
#include "stack.h"
#include "list.h"

void stack_write(int i, Stack* stack, std::string str)
{
	if (str[i] == '+') stack_push(stack, 1);
	if (str[i] == '-') stack_push(stack, 2);
	if (str[i] == '*') stack_push(stack, 3);
	if (str[i] == '/') stack_push(stack, 4);
}

void transform(Stack* stack)
{
	if (stack_get(stack) == 1) std::cout << '+';
	if (stack_get(stack) == 2) std::cout << '-';
	if (stack_get(stack) == 3) std::cout << '*';
	if (stack_get(stack) == 4) std::cout << '/';
	stack_pop(stack);
}

int main()
{
	Stack* stack = stack_create();
	std::cout << "enter correct arithmetic expression: \n";
	std::string str;
	std::getline(std::cin, str);
	std::cout << "reverse polish notation: \n";
	for (int i = 0; i < str.size(); i++) //E.W. Dijkstra Algorithm
	{
		if (isalpha(str[i]))
			std::cout << str[i];

		if (stack_empty(stack))
			stack_write(i, stack, str);
		else
		{
			if (str[i] == '+' || str[i] == '-')
			{
				while (!stack_empty(stack))
					transform(stack);
				stack_write(i, stack, str);
			}

			if ((str[i] == '*' || str[i] == '/') &&
				(stack_get(stack) == 1 || stack_get(stack) == 2))
				stack_write(i, stack, str);

			else if ((str[i] == '*' || str[i] == '/') &&
				(stack_get(stack) == 3 || stack_get(stack) == 4))
			{
				while (!stack_empty(stack))
					transform(stack);
				stack_write(i, stack, str);
			}
		}
	}
	while (!stack_empty(stack))
	{
		transform(stack);
	}
}
