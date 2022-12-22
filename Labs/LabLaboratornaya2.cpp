#include<iostream>
#include<string>
#include"stack.h"

using namespace std;

bool StringValidation(Stack* stack, string str) {
	int count34 = 0;
	int count39 = 0;
	for (char c : str) {
		switch (c) {
		case '(': stack_push(stack, '('); break;
		case ')':
			if (stack_empty(stack))
				return false;
			stack_pop(stack);
			break;
		case '\'': count34++; break;
		case '"': count39++; break;
		default: break;
		}
	}
	if (stack_empty(stack) && count34 % 2 == 0 && count39 % 2 == 0) return true;
	else return false;
}

int main() {
	string inputString;
	getline(cin, inputString);
	Stack* stack = stack_create();
	if (StringValidation(stack, inputString))
		cout << "Yes" << endl;
	else cout << "NO" << endl;
	stack_delete(stack);
}