#include <iostream>
#include "stack.h"

int main()
{
	const std::string open_brackets = "([{";
	const std::string close_brackets = ")]}";
	Data index;
	std::string str;
	bool result = true;

	Stack* stack = stack_create();

	std::cin >> str;

	for (size_t i = 0; i < str.size(); i++)
	{
		index = open_brackets.find(str[i]);
		if (index != std::string::npos)
		{
			stack_push(stack, str[i]);
		}
		else
		{
			if (!stack_empty(stack))
			{
				index = close_brackets.find(str[i]);
				if (stack_get(stack) != open_brackets[index])
				{
					result = false;
					break;
				}
				else
				{
					stack_pop(stack);
				}
			}
			else
			{
				result = false;
				break;
			}
		}
	}

	std::cout << ((result && stack_empty(stack)) ? "YES" : "NO");
	stack_delete(stack);
}