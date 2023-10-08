#include <iostream>
#include "stack.h"
#include <string>

using namespace std;

int pror(Data c) { //приоритет операций
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
	for (size_t i = 0; i < Refraction.size(); i++) { //проходим по всему выражению
		if (isalpha(Refraction[i])) {//если это буква, то сразу доваляем её в строчку
			otvet += Refraction[i];
		}
		else if (stack_empty(stack)) {//если список пустой, то добавляем в стек
			stack_push(stack, Refraction[i]);
		}
		else if (pror(Refraction[i]) > pror(stack_get(stack))) {//если приоритет больше, то добавляем в стек

			stack_push(stack, Refraction[i]);
		}
		else if (pror(Refraction[i]) <= pror(stack_get(stack))) {
			if (Refraction[i] == '(') {// если приоритет меньше, но это '(' добавляем в стек
				stack_push(stack, Refraction[i]);
			}
			else if (Refraction[i] == ')') {// если это ')', то добавляем в строку элементы, то закрывающейся скобки и в конце её удаляем из стека
				while (stack_get(stack) != '(') {
					otvet += stack_get(stack);
					stack_pop(stack);
				}
				stack_pop(stack);
			}
			else {
				while ((pror(Refraction[i]) <= pror(stack_get(stack)))) {// если приоритет меньше, то добаляем в срочку элементы то того момента, пока он не станет больше и добвляем данный элемент в стек
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
	while (!stack_empty(stack)) { // если ещё есть элементы в стеке добавляем их в строку 
		otvet += stack_get(stack);
		stack_pop(stack);
	}
	cout << "Reverse Polish notation:" << endl << otvet;
}

string proverka() { //проверка на правльеый ввод выражения
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