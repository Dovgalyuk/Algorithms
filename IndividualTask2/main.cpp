#include <iostream>
#include <string>
#include "stack.h"

int main()
{
	Stack* number = stack_create();
	Stack* mark = stack_create();

	std::string name;
	std::cin >> name;
	int num, num2;

	for (int i = 0; i < name.size(); i++)
	{
		if (isdigit(name[i]))
		{
			stack_push(number, name[i]-48);
		}
		else
		{
			if (stack_empty(mark))
			{
				stack_push(mark, name[i]);
			}
			else
			{
				if (stack_get(mark) == '*' || stack_get(mark) == '/')
				{
					if (stack_get(mark) == '*')
					{
						num = stack_get(number);
						stack_pop(number);
						num *= stack_get(number);
						stack_pop(number);
						stack_push(number, num);
					}
					else
					{
						num2 = stack_get(number);
						stack_pop(number);
						num = stack_get(number) / num2;
						stack_pop(number);
						stack_push(number, num);
					}
					stack_pop(mark);
					if (!stack_empty(mark)&&(name[i]=='+' || name[i] == '-'))
					{
						if (stack_get(mark) == '+')
						{
							num = stack_get(number);
							stack_pop(number);
							num += stack_get(number);
							stack_pop(number);
							stack_push(number, num);
						}
						else
						{
							num2 = stack_get(number);
							stack_pop(number);
							num = stack_get(number) - num2;
							stack_pop(number);
							stack_push(number, num);
						}
						stack_pop(mark);
						stack_push(mark, name[i]);
					}
					else
					{
						stack_push(mark, name[i]);
					}
					//std::cout << num << std::endl;
				}
				else 
				{
					if (name[i] == '*' || name[i] == '/')
					{
						stack_push(mark, name[i]);
					}
					else {
						if (stack_get(mark) == '+')
						{
							num = stack_get(number);
							stack_pop(number);
							num += stack_get(number);
							stack_pop(number);
							stack_push(number, num);
						}
						else
						{
							num2 = stack_get(number);
							stack_pop(number);
							num = stack_get(number) - num2;
							stack_pop(number);
							stack_push(number, num);
						}
						stack_pop(mark);
						//std::cout << num << std::endl;
					}
				}
			}
		}
	}

	while (!stack_empty(mark)) {

		if (stack_get(mark) == '*')
		{
			num = stack_get(number);
			stack_pop(number);
			num *= stack_get(number);
			stack_pop(number);
			stack_push(number, num);
		}
		else if (stack_get(mark)=='/')
		{
			num2 = stack_get(number);
			stack_pop(number);
			num = stack_get(number) / num2;
			stack_pop(number);
			stack_push(number, num);
		}
		else if (stack_get(mark) == '+')
		{
			num = stack_get(number);
			stack_pop(number);
			num += stack_get(number);
			stack_pop(number);
			stack_push(number, num);
		}
		else
		{
			num2 = stack_get(number);
			stack_pop(number);
			num = stack_get(number) - num2;
			stack_pop(number);
			stack_push(number, num);
		}
		stack_pop(mark);
	}

	std::cout << stack_get(number);

	system("pause");
}