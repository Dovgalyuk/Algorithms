#include <iostream>
#include "stack.h"
#include <fstream>

using namespace std;

int main() {
	ifstream fin("filte.txt", ios::in);
	Stack* begin = stack_create();
	bool zvezdochka = false;
	char ch;
	while ((ch = fin.get()) != EOF) {
		if (ch == '*') {
			zvezdochka = true;
		} else {
			if (zvezdochka) {
				if (!stack_empty(begin)) {
					if (stack_get(begin) != ch) {
						cout << "NO";
						stack_delete(begin);
						return 0;
					} else {
						stack_pop(begin);
					}
				} else {
					cout << "NO";
					stack_delete(begin);
					return 0;
				}
			} else {
				stack_push(begin, ch);
			}
		}
	}
	fin.close();
	if (stack_empty(begin)) {
		cout << "YES";
	} else {
		cout << "NO";
	}
	stack_delete(begin);
	return 0;
}
