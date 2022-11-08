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
	int x = 0;

	cout << "Введите размерность стека: ";
	cin >> n;

	while (x != 27) {
		cout << "Введите команду: ";
		cin >> command >> n_1;
		if (command == "push" and n != 0) {
			stack_push(stack, n_1);
			n--;
		}
		else if (command == "push" and n <= 0) {
			cout << "BAD PUSH" << endl;
		}
		else if (command == "pop" and !stack_empty(stack)) {
			stack_pop(stack);
			n++;
		}
		else if (command == "pop" and stack_empty(stack)) {
			cout << "BAD POP" << endl;
		}
		if (x == 27) {
			system("cls");
			cout << "STACK" << endl;
			while (n != 0) {
				cout << stack_get(stack) << endl;
				n--;
			}
		}
	}
}
