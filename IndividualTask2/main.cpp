#include <iostream>
#include "stack.h"

void symbolsSequenceCheck(std::string& symbols)
{
	Stack* stack = stack_create();

	for (int i = 0; i < symbols.size(); i++)
	{
		if (symbols[i] == '(' || symbols[i] == '{' || symbols[i] == '[')
		{
			stack_push(stack, symbols[i]);
			continue;
		}
		else if (symbols[i] == '\"' || symbols[i] == '\'')
		{
			if (!stack_empty(stack) && stack_get(stack) == symbols[i])
			{
				stack_pop(stack);
			}
			else
			{
				stack_push(stack, symbols[i]);
			}
			continue;
		}

		if (!stack_empty(stack) && (stack_get(stack) == symbols[i] - 1 || stack_get(stack) == symbols[i] - 2))
		{
			stack_pop(stack);
		}
		else
		{
			if (symbols[i] == ')' || symbols[i] == ']' || symbols[i] == '}')
			{
				std::cout << "NO" << std::endl;
				return;
			}
			else
			{
				std::cout << "Incorrect input. Allowed characters: [ ] , { } , ( ) , \" or \' " << std::endl;
				return;
			}
		}
	}

	if (!stack_empty(stack))
	{
		std::cout << "NO" << std::endl;
	}
	else
	{
		std::cout << "YES" << std::endl;
	}
}

int main()
{
	std::string symbols;
	std::cin >> symbols;

	symbolsSequenceCheck(symbols);

	system("pause");

	return 0;
}