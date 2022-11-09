#include <iostream>
#include <string>
#include "list.h"
#include "stack.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	Stack* stack = stack_create();
	string command;
	int n = 0;
	Data n_1 = 0;

	cout << "Введите размерность стека: ";
	cin >> n;

	while (command != "exit") {
		cout << "Введите команду: ";
		cin >> command >> n_1;
		if (command == "push") {
			if (n > 0) {
				stack_push(stack, n_1);
				n--;
			}
			if (n <= 0) {
				cout << "BAD PUSH" << endl;
			}
		}
		if (command == "pop") {
			if (!stack_empty(stack)) {
				stack_pop(stack);
				n++;
			}
			if (stack_empty(stack)) {
				cout << "BAD POP" << endl;
			}
		}
		if (command == "exit") {
			system("cls");
			cout << "STACK" << endl;
			while (n != 0) {
				cout << stack_get(stack) << endl;
				n--;
			}
		}
	}
}
