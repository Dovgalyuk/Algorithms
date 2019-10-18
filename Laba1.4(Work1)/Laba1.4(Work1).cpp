#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
	int count;
	cin >> count;
	Stack* atoms;
	atoms = stack_create();
	int otr = 0;
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
			stack_push(atoms, temp);
		else
			otr=temp;
		if (!stack_empty(atoms) && otr >= stack_get(atoms))
		{
			cout << stack_get(atoms) << ' ' << otr << endl;
			otr = 0;
			stack_pop(atoms);
		}
	}
	stack_delete(atoms);
}