#include <iostream>
#include "stack.h"
#include <fstream>

using namespace std;

int main() {
	ifstream fin("filte.txt", ios::in);
	Stack* temp = stack_create();
	Stack* begin = stack_create();
	Stack* end = stack_create();
	bool zvezdochka = false;
	char ch;
	while ((ch = fin.get()) != EOF) {
		if (ch == '*') {
			zvezdochka = true;
		} else {
			if (zvezdochka) {
				stack_push(end, ch);
			} else {
				stack_push(begin, ch);
			}
		}
	}
	fin.close();
	while (!stack_empty(begin)) {
		stack_push(temp, stack_get(begin));
		stack_pop(begin);
	}

	bool marker = true;

	while (!stack_empty(temp) && !stack_empty(end)) {
		if (stack_get(temp) != stack_get(end)) {
			marker = false;
			break;
		} else {
			stack_pop(temp);
			stack_pop(end);
		}
	}

	if (!stack_empty(temp) || !stack_empty(end)) {
		marker = false;
	}

	stack_delete(begin);
	stack_delete(end);
	stack_delete(temp);

	if(marker){
		cout << "YES";
	} else {
		cout << "NO";
	}

	return 0;
}
