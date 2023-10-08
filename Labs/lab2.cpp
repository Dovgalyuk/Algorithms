#include <iostream>
#include "stack.h"
#include <string>

using namespace std;

int pror(Data c) { //��������� ��������
	switch (c)
	{
	case '(':
		return 0;
	case ')':
		return 1;
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	default:
		break;
	}
	return -1;
}

void opz(string Refraction) {
	string otvet;
	Stack* stack = stack_create();
	for (size_t i = 0; i < Refraction.size(); i++) { //�������� �� ����� ���������
		if (isalpha(Refraction[i])) {//���� ��� �����, �� ����� �������� � � �������
			otvet += Refraction[i];
		}
		else if (stack_empty(stack)) {//���� ������ ������, �� ��������� � ����
			stack_push(stack, Refraction[i]);
		}
		else if (pror(Refraction[i]) > pror(stack_get(stack))) {//���� ��������� ������, �� ��������� � ����

			stack_push(stack, Refraction[i]);
		}
		else if (pror(Refraction[i]) <= pror(stack_get(stack))) {
			if (Refraction[i] == '(') {// ���� ��������� ������, �� ��� '(' ��������� � ����
				stack_push(stack, Refraction[i]);
			}
			else if (Refraction[i] == ')') {// ���� ��� ')', �� ��������� � ������ ��������, �� ������������� ������ � � ����� � ������� �� �����
				while (stack_get(stack) != '(') {
					otvet += stack_get(stack);
					stack_pop(stack);
				}
				stack_pop(stack);
			}
			else {
				while ((pror(Refraction[i]) <= pror(stack_get(stack)))) {// ���� ��������� ������, �� �������� � ������ �������� �� ���� �������, ���� �� �� ������ ������ � �������� ������ ������� � ����
					otvet += stack_get(stack);
					stack_pop(stack);
					if (stack_empty(stack)) {
						break;
					}
				}
				stack_push(stack, Refraction[i]);
			}
		}
	}
	while (!stack_empty(stack)) { // ���� ��� ���� �������� � ����� ��������� �� � ������ 
		otvet += stack_get(stack);
		stack_pop(stack);
	}
	cout << "Reverse Polish notation:" << endl << otvet;
}

string proverka() { //�������� �� ��������� ���� ���������
	cout << "Enter an arithmetic expression (The operands in the expression are single-letter variables):";
	while (true) {
		string Refraction;
		getline(cin, Refraction);
		int leng = Refraction.size();
		int k = 0;
		for (int i = 0; i < leng; i++) {
			if (isalpha(Refraction[i]) || Refraction[i] == '*' || Refraction[i] == '-' || Refraction[i] == '+' || Refraction[i] == '/' || Refraction[i] == '(' || Refraction[i] == ')') {
				k++;
			}
		}
		if (k == leng) {
			return Refraction;
		}
		else {
			cout << "Error.Enter an arithmetic expression (The operands in the expression are single-letter variables):";
		}
	}
}

int main()
{
	string Refraction = proverka();
	opz(Refraction);
}