#include <iostream>
#include <map>
#include<fstream>
#include "stack.h"


using namespace std;

bool qwer(string& s, Stack* stack, map<char, int>& Arr , ifstream& file) {

	int value;

	if (s == "push") {
		file >> value;
		stack_push(stack, value);
	}
	else if (s == "pop") {
		char c;
		file >> c;

		if (stack_empty(stack)) {
			cout << "BAD POP";
			return false;
		}

		Arr[c] = stack_get(stack);
		stack_pop(stack);
	}
	else if (s == "add"){
		if (stack_empty(stack)) {
			cout << "BAD ADD";
			return false;
		}

		int a = stack_get(stack);
		stack_pop(stack);

		if(stack_empty(stack)) {
			cout << "BAD ADD";
			return false;
		}

		int b = stack_get(stack);
		stack_pop(stack);

		stack_push(stack, a + b);
	}
	else if (s == "sub") {
		if (stack_empty(stack)) {
			cout << "BAD SUB";
			return false;
		}

		int a = stack_get(stack);
		stack_pop(stack);

		if (stack_empty(stack)) {
			cout << "BAD SUB";
			return false;
		}

		int b = stack_get(stack);
		stack_pop(stack);

		stack_push(stack, a - b);
	}
	else if (s == "mul") {
		if (stack_empty(stack)) {
			cout << "BAD MUL";
			return false;
		}

		int a = stack_get(stack);
		stack_pop(stack);

		if (stack_empty(stack)) {
			cout << "BAD MUL";
			return false;
		}

		int b = stack_get(stack);
		stack_pop(stack);

		stack_push(stack, a * b);
	}
	else if (s == "call"){
		stack_push(stack , 9999);
	}
	else if (s == "ret") {
		if (stack_empty(stack)) {
			cout << "BAD RET";
			return false;
		}

		int qwer = stack_get(stack);

		if (qwer != 9999) {
			cout << "BAD RET";
			return false;
		}
		stack_pop(stack);
	}

	return true;
}



int main(int argc, char** argv) {

	ifstream file(argv[1]);

	if (!file.is_open()) {
		return 1;
	}

	Stack* stack = stack_create();
	map<char, int> Arr = {
		{'A',0},{'B',0},{'C',0},{'D',0}
	};
	string s;

	while (file >> s) {
		if (!qwer(s, stack, Arr, file)) {
			stack_delete(stack);
			file.close();
			return 0;
		}
	}

	cout << "A = " << Arr['A']
		<< " B = " << Arr['B']
		<< " C = " << Arr['C']
		<< " D = " << Arr['D'] << endl;

	stack_delete(stack);
	file.close();

	return 0;
}
