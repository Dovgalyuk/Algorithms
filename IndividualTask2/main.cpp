#include <iostream>
#include <string>
#include "stack.h"


void multiplication(Stack* number) {
	int num;
	num = stack_get(number);
	stack_pop(number);
	num *= stack_get(number);
	stack_pop(number);
	stack_push(number, num);
}

void division(Stack* number) {
	int num, num2;
	num2 = stack_get(number);
	stack_pop(number);
	num = stack_get(number) / num2;
	stack_pop(number);
	stack_push(number, num);
}

void addition(Stack* number) {
	int num;
	num = stack_get(number);
	stack_pop(number);
	num += stack_get(number);
	stack_pop(number);
	stack_push(number, num);
}

void difference(Stack* number) {
	int num, num2;
	num2 = stack_get(number);
	stack_pop(number);
	num = stack_get(number) - num2;
	stack_pop(number);
	stack_push(number, num);
}

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
						multiplication(number);
					}
					else
					{
						division(number);
					}

					stack_pop(mark);

					if (!stack_empty(mark)&&(name[i]=='+' || name[i] == '-'))
					{
						if (stack_get(mark) == '+')
						{
							addition(number);
						}
						else
						{
							difference(number);
						}
						stack_pop(mark);
						stack_push(mark, name[i]);
					}
					else
					{
						stack_push(mark, name[i]);
					}
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
							addition(number);
						}
						else
						{
							difference(number);
						}
						stack_pop(mark);
					}
				}
			}
		}
	}

	while (!stack_empty(mark)) {

		if (stack_get(mark) == '*')
		{
			multiplication(number);
		}
		else if (stack_get(mark)=='/')
		{
			division(number);
		}
		else if (stack_get(mark) == '+')
		{
			addition(number);
		}
		else
		{
			difference(number);
		}
		stack_pop(mark);
	}

	std::cout << stack_get(number) << std::endl;


	stack_delete(mark);
	stack_delete(number);
	system("pause");
}