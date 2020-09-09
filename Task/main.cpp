#include <iostream>
#include "stack.h"

void buildBackPolishExpression(const std::string& text)
{
	Stack* stack = stack_create();
	
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] != '*' && text[i] != '/' && text[i] != '+' && text[i] != '-')
		{
			std::cout << text[i];
		}
		else
		{
			if (stack_empty(stack))
			{
				stack_push(stack, text[i]);
			}
			else
			{
				if (stack_get(stack) == '*' || stack_get(stack) == '/')
				{
					std::cout << stack_get(stack);
					stack_pop(stack);
					if (!stack_empty(stack) && (text[i] == '+' || text[i] == '-'))
					{
						std::cout << stack_get(stack);
						stack_pop(stack);
						stack_push(stack, text[i]);
					}
					else
					{
						stack_push(stack, text[i]);
					}
				}
				else
				{
					if (text[i] == '*' || text[i] == '/')
					{
						stack_push(stack, text[i]);
					}
					else
					{
						std::cout << stack_get(stack);
						stack_pop(stack);
						stack_push(stack, text[i]);
					}
				}
			}
		}	
	}

	while (!stack_empty(stack))
	{
		std::cout << stack_get(stack);
		stack_pop(stack);
	}
	
	stack_delete(stack);
}

int main()
{
	std::string text;

	std::cout << "Enter an expression: ";
	std::cin >> text;
	
	buildBackPolishExpression(text);
	
	return 0;
}
