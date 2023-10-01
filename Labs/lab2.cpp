#include <iostream>
#include "vector.h"
#include "stack.h"
#include <string>

using namespace std;

int get_len(Stack* stack, Data symbolic, int& opened, int& closed) {
	size_t len = 0;
	Data exam = 'a';
	if (symbolic == ']') {
		while (true) {
			exam = stack_get(stack);
			if (exam == '{' || exam == '(') {
				opened++;
			}
			else if (exam == ']' || exam == '}' || exam == ')') {
				closed++;
			}
			if (exam == '[') {
				break;
			}
			stack_pop(stack);
			len += 1;
		}
	}
	else if (symbolic == '}') {
		while (true) {
			exam = stack_get(stack);
			if (exam == '[' || exam == '(') {
				opened++;
			}
			else if (exam == ']' || exam == '}' || exam == ')') {
				closed++;
			}
			if (exam == '{') {
				break;
			}
			stack_pop(stack);
			len += 1;
		}
	}
	else if (symbolic == ')') {
		while (true) {
			exam = stack_get(stack);
			if (exam == '[' || exam == '{') {
				opened++;
			}
			else if (exam == ']' || exam == '}' || exam == ')') {
				closed++;
			}
			if (exam == '(') {
				break;
			}
			stack_pop(stack);
			len += 1;
		}
	}
	else {
		return 1;
	}
	return len;
}

int size_and_print(Stack* stack) {
	int size = 0;
	while (!(stack_empty(stack))) {
		cout << stack_get(stack) << " ";
		stack_pop(stack);
		size++;
	}
	cout << endl;
	return size;
}

void task1(Stack* stack) {
	Stack* exam = stack_copy(stack);
	int size = size_and_print(exam);
	if (size % 2 == 0) {
		int pair = 0;
		while (!(stack_empty(stack))) {
			stack_delete(exam);
			int opened = 0, closed = 0;
			Data symbolic = stack_get(stack);
			stack_pop(stack);
			exam = stack_copy(stack);
			int len = get_len(exam, symbolic, opened, closed);
			if (len % 2 == 0 && opened == closed) {
				pair++;
			}
		}
		if (pair == size / 2) {
			cout << "YES";
		}
		else {
			cout << "NO";
		}
	}
	else {
		cout << "NO";
	}
}

int main()
{
	Stack* stack = stack_create();
	string str = "";
	getline(cin, str);
	char* c = const_cast<char*>(str.c_str());
	for (size_t i = 0; i < str.size(); i++) {
		stack_push(stack, c[i]);
	}
	task1(stack);
}