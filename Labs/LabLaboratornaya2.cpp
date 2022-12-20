#include<iostream>
#include<string>
#include"stack.h";

using namespace std;

bool StringValidation(Stack* stack, string str) {
	int count34 = 0;
	int count39 = 0;
	int count40 = 0;
	int count41 = 0;
	int counter = 0;
	for (char c : str) {
		switch (c) {
		case '(': stack_push(stack, '('); break;
		case ')': stack_push(stack, ')'); break;
		case '\'': stack_push(stack, '\''); break;
		case '"': stack_push(stack, '"'); break;
		default: break;
		}
	}

	while (!stack_empty(stack)) {
		switch (stack_get(stack)) {
		case '"': count34++; stack_pop(stack); break;
		case '\'': count39++; stack_pop(stack); break;
		case '(': count40++; stack_pop(stack); break;
		case ')': count41++; stack_pop(stack); break;
		default:
			break;
		}
	}
	if (count34 % 2 == 0 && count39 % 2 == 0 && count41 == count40) return true;
	else return false;
}

void main() {
	string inputString;
	getline(cin, inputString);
	Stack* stack = stack_create();
	if (StringValidation(stack, inputString))
		cout << "Yes" << endl;
	else cout << "NO" << endl;
	stack_delete(stack);
}
