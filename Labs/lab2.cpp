#include <iostream>
#include "stack.h"
#include <string>

using namespace std;

void task1(string str) {
	Stack* stack = stack_create(); //выделение памяти под стэк
	size_t size = str.size();
	if (size % 2 == 0) {
		int pair = 0;
		for (size_t i = 0; i < size; i++) {
			if (str[i] == '[' || str[i] == '{' || str[i] == '(') {
				stack_push(stack, str[i]);
				int between = 0;
				int opened = 0;
				int closed = 0;
				for (size_t j = i + 1; j < size; j++) {
					if (closed==opened && between%2==0 
						&& ((stack_get(stack) == '[' && str[j] == ']') || 
						(stack_get(stack) == '{' && str[j] == '}') || 
						(stack_get(stack) == '(' && str[j] == ')'))) {
						pair++;
						break;
					}
					else if (str[j] == ']' || str[j] == '}' || str[j] == ')') {
						closed++;
					}
					else if (str[j] == '[' || str[j] == ' {' || str[j] == '(') {
						opened++;
					}
					between++;
				}
				stack_pop(stack);
			}
		}
		if (pair == size / 2) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
	else {
		cout << "NO\n";
	}
	stack_delete(stack);
}

int main()
{
	string str;
	cout << "Please enter a string consisting of [, ], (, ), { , }: ";
	getline(cin, str);
	task1(str);
}