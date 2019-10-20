#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;

int main()
{
	Stack *stack = stack_create();
	ifstream file("file.txt");
	char s;

	if (!file)
	{
		cout << "Error!" << endl;
		return 0;
	}

	while (!file.eof() ) {
		file.get(s);
		if (s == '*') break;
		stack_push(stack, s);
	}

	while (!stack_empty(stack)) {
		if (stack_get(stack) == file.get())
			stack_pop(stack);
		else break;
	}
	file.get();

	if (stack_empty(stack) && file.eof())
		cout << "YES";
	else cout << "NO";
	
	stack_delete(stack);
	return 0;
}