#include <iostream>
#include <map>
#include<fstream>
#include "stack.h"
 

using namespace std;

typedef map<char, int> MAP;

string perevod(string text) {
	for (char& c : text) {
		c = (char)tolower(c);
	}
	return text;
}

bool qwer(string& s, Stack* stack, Stack* call_stack, MAP& Arr, ifstream& file) {
	int value;

	s = perevod(s);

	if (s == "push") {
		file >> value;
		stack_push(stack, value);
		stack_push(call_stack, 0);
	}
	else if (s == "pop") {
		char c;
		file >> c;

		if (stack_empty(stack) || stack_empty(call_stack) || stack_get(call_stack) == 1) {
			cout << "BAD POP";
			return false;
		}

		Arr[c] = stack_get(stack);
		stack_pop(stack);
		stack_pop(call_stack);
	}
	else if (s == "add" || s == "sub" || s == "mul") {

		if (stack_empty(stack) || stack_empty(call_stack) || stack_get(call_stack) == 1) {
			cout << "BAD " << (s == "add" ? "ADD" : s == "sub" ? "SUB" : "MUL");
			return false;
		}

		int a = stack_get(stack);
		stack_pop(stack);
		stack_pop(call_stack);

		if (stack_empty(stack) || stack_empty(call_stack) || stack_get(call_stack) == 1) {
			cout << "BAD " << (s == "add" ? "ADD" : s == "sub" ? "SUB" : "MUL");
			return false;
		}

		int b = stack_get(stack);
		stack_pop(stack);
		stack_pop(call_stack);

		int res;
		if (s == "add") {
			res = a + b;
		}
		else if (s == "sub") {
			res = a - b;
		}
		else {
			res = a * b;
		}

		stack_push(stack, res);
		stack_push(call_stack, 0);
	}
	else if (s == "call"){
		stack_push(stack, 9999);
		stack_push(call_stack, 1);
	}
	else if (s == "ret") {
		if (stack_empty(call_stack) || stack_empty(stack) || stack_get(call_stack) != 1){
			cout << "BAD RET";
			return false;
		}

		stack_pop(stack);
		stack_pop(call_stack);
	}
	return true;
}


int main(int argc, char** argv)
{
	(void)argc;
	ifstream file(argv[1]);

	if (!file.is_open()) {
		return 1;
	}

	Stack* stack = stack_create();
	Stack* call_stack = stack_create();
	MAP Arr = {
		{'A',0},{'B',0},{'C',0},{'D',0}
	};
	string s;

	while (file >> s) {
		if (!qwer(s, stack, call_stack, Arr, file)) {
			stack_delete(stack);
			stack_delete(call_stack);
			file.close();
			return 0;
		}
	}

	cout << "A = " << Arr['A']
		<< " B = " << Arr['B']
		<< " C = " << Arr['C']
		<< " D = " << Arr['D'] << endl;

	stack_delete(stack);
	stack_delete(call_stack);
	file.close();

	return 0;
}
