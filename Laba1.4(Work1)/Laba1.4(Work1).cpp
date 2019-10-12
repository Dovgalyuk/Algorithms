#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
	int count;
	cin >> count;
	Stack* pol, * otr;
	pol = stack_create();
	otr = stack_create();
	while (!cin.eof())
	{
		int temp;
		char temp1 = ' ';
		cin >> temp;
		while (temp1 != '+' && temp1 != '-' && !cin.eof())
			cin >> temp1;
		if (cin.eof())
			break;
		if (temp1 == '+')
			stack_push(pol, temp);
		else
			stack_push(otr, temp);
	}
	while (!(stack_empty(pol) || stack_empty(otr)))
	{
		if (stack_get(otr) >= stack_get(pol))
		{
			cout << stack_get(pol) << ' ' << stack_get(otr) << endl;
			stack_pop(pol);
			stack_pop(otr);
		}
		else
			stack_pop(pol);
	}
	stack_delete(pol);
	stack_delete(otr);
}