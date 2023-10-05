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
	size_t size = str.size(); //узнаем длину (возможно, что ответ )
	if (size % 2 == 0) {
		for (size_t i = 0; i < size; i++) {//проверяем каждый элемент через два for
			if (str[i] == '[' || str[i] == '{' || str[i] == '(') {
				stack_push(stack, str[i]); // добавляем элемент в stack
				int between = 0; //кол-во элементов между двух скобок
				int opened = 0; //кол-во октрывающих скобок
				int closed = 0; //кол-во закрывающих скобок
				for (size_t j = i + 1; j < size; j++) {
					if (closed == opened && between % 2 == 0
						&& ((stack_get(stack) == (Data)'[' && str[j] == (Data)']') ||
							(stack_get(stack) == (Data)'{' && str[j] == (Data)'}') ||
							(stack_get(stack) == (Data)'(' && str[j] == (Data)')'))) {
						stack_pop(stack);
						break;
					}
					else if (str[j] == ']' || str[j] == '}' || str[j] == ')') {
						closed++;
					}
					else if (str[j] == '[' || str[j] == ' {' || str[j] == '(') {
						opened++;
					}
					between++;
				}
			}
		}
		if (stack_empty(stack)) { //если стэк пуст, то все верно
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
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