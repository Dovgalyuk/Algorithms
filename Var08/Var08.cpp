#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;

int main()
{
	Stack *stack = stack_create();
	Stack *sort = stack_create();
	ifstream file("file.txt");
	int i = 0;
	char s;

	if (!file)
	{
		cout << "Error!" << endl;
		return 0;
	}

	while (!file.eof()) {
		file.get(s);
		stack_push(stack, s);
		i++;
	}
	stack_pop(stack);

	while (stack_get(stack) != '*') {
		stack_push(sort, stack_get(stack));
		stack_pop(stack);
	}
	stack_pop(stack);

	while (!stack_empty(stack)) {
		if (stack_get(stack) == stack_get(sort)) {
			stack_pop(stack);
			stack_pop(sort);
		}
		else break;
	}

	if (stack_empty(stack) && stack_empty(sort))
		cout << "YES";
	else cout << "NO";

	stack_delete(stack);
	stack_delete(sort);
	return 0;
}