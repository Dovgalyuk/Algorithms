#include <iostream>
#include <string>
#include "vector.h"
#include "stack.h"

using namespace std;

int cheak(Stack* str,string st);


int main()
{
	Stack* str = stack_create();
	string cha;
	cout << "Give me string. Only ()[]{}''\"\"" << endl;
	cin >> cha;
	int i;
	stack_push(str, cha[0]);
	i = cheak(str, cha);
	if (stack_empty(str) && i == cha.size())
		cout << "YES";
	else
		cout << "NO";
	stack_delete(str);

}

int cheak(Stack* str, string st)
{
	bool c = 0;
	bool b = 0;
	int i = 1;
	for (i; i < st.size(); i++)
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
				return i;
		}

		else if (st[i] == ']')
		{
			if (stack_get(str) == '[')
				stack_pop(str);
			else
				return i;
		}

		else if (st[i] == '}')
		{
			if (stack_get(str) == '{')
				stack_pop(str);
			else
				return i;
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
	return i;
}
