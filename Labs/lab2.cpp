#include <iostream>
#include "stack.h"
#include <string>

using namespace std;

string input() { //�������� �� ���� ������
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
	Stack* stack = stack_create(); //��������� ������ ��� ����
	size_t size = str.size(); //������ ����� (��������, ��� ����� )
	if (size % 2 == 0) {
		for (size_t i = 0; i < size; i++) {//��������� ������ ������� ����� ��� for
			if (str[i] == '[' || str[i] == '{' || str[i] == '(') {
				stack_push(stack, str[i]); // ��������� ������� � stack
				int between = 0; //���-�� ��������� ����� ���� ������
				int opened = 0; //���-�� ����������� ������
				int closed = 0; //���-�� ����������� ������
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
		if (stack_empty(stack)) { //���� ���� ����, �� ��� �����
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
	else {
		cout << "NO\n";
	}
	stack_delete(stack);//����������� ������
}

int main()
{
	string str = input();
	task1(str);
}