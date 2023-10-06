#include <iostream>
#include "stack.h"
#include <string>

using namespace std;

string input() { //првоерка на ввод скобок
	cout << "Please enter a string consisting of [, ], (, ), { , }: ";
	while (true) {
		string str;
		getline(cin, str);
		size_t size = str.size();
		size_t count = 0;
		for (size_t i = 0; i < size; i++) {
			if (str[i] == '[' || str[i] == '(' || str[i] == '{' || str[i] == ']' || str[i] == ')' || str[i] == '}') {
				count++;
			}
		}
		if (count == size) {
			return str;
		}
		else {
			cout << "Incorrect input! Try again\n";
		}
	}
}

void task1(string str) {
	Stack* stack = stack_create(); //выделение памяти под стэк
	size_t size = str.size(); //узнаем длину
	for (size_t i = 0; i < size; i++) {
		if (str[i] == '[' || str[i] == '{' || str[i] == '(') {
			stack_push(stack, str[i]); // добавляем элемент в stack
		}
		else {
			if (!stack_empty(stack) && ((stack_get(stack) == '[' && str[i] == ']') || //проверяем если стэк не пуст и последний элемент составляет пару
				(stack_get(stack) == '{' && str[i] == '}') ||
				(stack_get(stack) == '(' && str[i] == ')'))) {
				stack_pop(stack);
			}
			else {
				break;
			}
		}
	}
	if (stack_empty(stack)) { //если стэк пуст, то все верно
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
	stack_delete(stack);//освобождаем память
}

int main()
{
	string str = input();
	task1(str);
}