#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "list.h"
#include "stack.h"
using namespace std;

void to_lower_register(string& str) {
	for (char& c : str) {
		if (c >= 'A' && c <= 'Z') {
			c += 32;
		}
	}
}

bool tag_sequence_correctness(ifstream& input, Stack* stack) {
	string line;
	bool flag = true;
	while (getline(input, line)) {
		if (line.substr(0, 2) == "</") {
			string closed_tag = line.substr(2, line.length() - 2);
			string open_tag = stack_get(stack).substr(1, stack_get(stack).length() - 1);
			to_lower_register(closed_tag);
			to_lower_register(open_tag);
			if (closed_tag == open_tag) {
				stack_pop(stack);
			}
			else {
				flag = false;
				return flag;
			}
		}
		else {
			stack_push(stack, line);
		}
	}
	return flag;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		return 1;
	}
	setlocale(LC_ALL, "RUS");
	ifstream input(argv[1]);
	if (!(input.is_open())) {
		cout << "Не удалось открыть файл.";
		return 1;
	}
	Stack* stack = stack_create();
	ofstream output("output.txt");
	if (tag_sequence_correctness(input, stack)) {
		output << "YES";
	}
	else {
		output << "NO";
	}
	stack_delete(stack);
	input.close();
	output.close();
	return 0;
}