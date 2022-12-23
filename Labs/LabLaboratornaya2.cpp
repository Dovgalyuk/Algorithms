#include<iostream>
#include<string>
#include"stack.h"

using namespace std;

bool StringValidation(Stack* stack, string str) {
	int count = 0;
	for (char c : str) {
		switch (c) {
		case '(': stack_push(stack, '('); count++; break;
		case ')': 
			if (stack_get(stack) == '('); count--; stack_pop(stack);
			break;
		case '\'': 
			if (stack_get(stack) == '\'') stack_pop(stack);
			else stack_push(stack, '\'');
			break;
		case '"':
			if (stack_get(stack) == '"') stack_pop(stack);
			else stack_push(stack, '"');
			break;
		default: break;
		}
	}
	if (stack_empty(stack) && count == 0) return true;
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
