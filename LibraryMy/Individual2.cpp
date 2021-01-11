#include <iostream>
#include "stack.h"
using namespace std;

int main()
{
	const string open = "([{";
	const string close = ")]}";
	Stack* stack = stack_create();
	
	string check;
	cin >> check;

	bool right = true;
	for (int i = 0; i < check.size(); i++)
	{
		size_t index = open.find(check[i]);
		if (index != string::npos)
		{
			stack_push(stack, check[i]);
		}
		else
		{
			if (!stack_empty(stack))
			{
				size_t index = close.find(check[i]);
				if (stack_get(stack) != open[index])
				{
					right = false;
					break;
				}
				else
				{
					stack_pop(stack);
				}
			}
			else
			{
				right = false;
				break;
			}
		}
	}
	
	if (right && stack_empty(stack)) cout << "YES";
	else cout << "NO";

	stack_delete(stack);
}
