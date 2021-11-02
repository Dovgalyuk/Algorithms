#include <iostream>
#include <string>
#include "vector.h"
#include "stack.h"

using namespace std;

void cheak(Stack* str,string st);


int main()
{
	Stack *str = stack_create();
	string cha;
	cout << "Give me string. Only ()[]{}''\"\"" << endl;
	cin >> cha;
	if (cha.size() < 2)
	{
		cout << "Invalid input" << endl;
	}
	else
	{
		stack_push(str, cha[0]);
		cheak(str, cha);
		if (stack_empty(str))
			cout << "YES";
		else
			cout << "NO";
		stack_delete(str);
	}
}

void cheak(Stack* str, string st)
{
	bool c = 0;
	bool b = 0;
	for (int i = 1; i < st.size(); i++)
	{
		if (st[i] == '(' || st[i] == '[' || st[i] == '{')
		{
			stack_push(str, st[i]);
		}

		else if(st[i]==')')
		{
			if (stack_get(str) == '(')
				stack_pop(str);
			else
				break;
		}

		else if (st[i] == ']')
		{
			if (stack_get(str) == '[')
				stack_pop(str);
			else
				break;
		}

		else if (st[i] == '}')
		{
			if (stack_get(str) == '{')
				stack_pop(str);
			else
				break;
		}

		else if (st[i] == '\'')
		{
			if (stack_get(str) == '\'')
			{
				stack_pop(str);
			}
			else
			{
				stack_push(str, st[i]);
			}
		}

		else if (st[i] == '\"')
		{
			if (stack_get(str) == '\"')
			{
				stack_pop(str);
			}
			else
			{
				stack_push(str, st[i]);
			}
		}
	}
}
