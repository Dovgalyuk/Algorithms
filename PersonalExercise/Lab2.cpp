#include <iostream>
#include "stack.h"
using namespace std;

const string open = "([{<";
const string close = ")]}>";

int main()
{
	string check;
	cin >> check;

	Stack<char>* stack = new Stack<char>();

	bool good = true;
	for (int i = 0; i < check.size(); i++)
	{
		size_t index = open.find(check[i]);
		if (index != string::npos)
		{
			stack->push(check[i]);
		}
		else
		{
			if (!stack->empty())
			{
				size_t index = close.find(check[i]);
				if (stack->get() != open[index])
				{
					good = false;
					break;
				}
				else
				{
					stack->pop();
				}
			}
			else
			{
				good = false;
				break;
			}
		}
	}

	if (good && stack->empty()) cout << "YES";
	else cout << "NO";

	delete stack;
}