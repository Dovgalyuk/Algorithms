#include <iostream>
#include "vector.h"
#include "stack.h"
#include <string>

using namespace std;

int get_len(Stack* stack, Data symbolic, int& opened, int& closed) { //функция узнавания длинны и кол-ва открывающихся и закрывающихся скобок внутри пары скобок
	size_t len = 0;
	Data exam = 'a';
	if (symbolic == ']') {
		while (true) {
			exam = stack_get(stack);
			if (exam == '{' || exam == '(') {
				opened++;
			}
			else if (exam == ']' || exam == '}' || exam == ')') {
				closed++;
			}
			if (exam == '[') {
				break;
			}
			stack_pop(stack);
			len += 1;
		}
	}
	else if (symbolic == '}') {
		while (true) {
			exam = stack_get(stack);
			if (exam == '[' || exam == '(') {
				opened++;
			}
			else if (exam == ']' || exam == '}' || exam == ')') {
				closed++;
			}
			if (exam == '{') {
				break;
			}
			stack_pop(stack);
			len += 1;
		}
	}
	else if (symbolic == ')') {
		while (true) {
			exam = stack_get(stack);
			if (exam == '[' || exam == '{') {
				opened++;
			}
			else if (exam == ']' || exam == '}' || exam == ')') {
				closed++;
			}
			if (exam == '(') {
				break;
			}
			stack_pop(stack);
			len += 1;
		}
	}
	else { //мы проходим с конца в начало, значит если попадается открывающаяся скобка, то мы либо уже нашли ей пару, либо к ней пары нет
		return 1;
	}
	return len;
}

int size_and_print(Stack* stack) { //печать стэка и узнаем его длинну (можно сделать в 2 функциях, но будет одиннаковый смысл у них)
	int size = 0;
	cout << "Data on the stack: ";
	while (!(stack_empty(stack))) {
		cout << stack_get(stack) << " ";
		stack_pop(stack);
		size++;
	}
	cout << endl;
	return size;
}

void task1(Stack*  stack)	 {
	Stack* exam = stack_copy(stack); //делаем копию стэка
	int size = size_and_print(exam); //узнаем длмнну стэка и печатаем его в консоль
	if (size % 2 == 0) { //если длинна строки нечет, то задание провалено, потому что элементы идут парами
		int pair = 0; //счетчик пар
		while (!(stack_empty(stack))) { //циклом находим каждому элементу пару
			stack_delete(exam);
			int opened = 0, closed = 0; //количество открывающихся и закрывающихся скобок внутри пары
			Data symbolic = stack_get(stack);
			stack_pop(stack);
			exam = stack_copy(stack);
			int len = get_len(exam,symbolic,opened,closed);
			if (len % 2 == 0 && opened == closed) { //если длинна нечет и количество скобок не совпадает, то такой пары нет
				pair++;
			}
		}
		if (pair == size/2) {
			cout << "YES";
		}
		else {
			cout << "NO";
		}
	}
	else {
		cout << "NO";
	}
}

int main()
{
	Stack* stack = stack_create(); //выделение памяти под стэк
	string str="";
	cout << "Please enter a string consisting of [, ], (, ), { , }: ";
	while (true) { //проверка ввода
		getline(cin, str); //считывание ввода строки пользователя
		size_t correct_count = 0; //счетчик правильности символа
		for (size_t i = 0; i < str.size(); i++) { //циклом проверяем все символы
			if (str[i] != '[' && str[i] != ']' && str[i] != '(' && str[i] != ')' && str[i] != '[' && str[i] != ']') {
				cout << "Incorrect input (please use just [,],(,),{,})\n";
				break;
			}
			else {
				correct_count++;
			}
		}
		if (correct_count == str.size()) {
			break;
		}
	}
	char* c = const_cast<char*>(str.c_str()); //делаем из string char*, чтобы передавать в Data
	for (size_t i = 0; i < str.size(); i++) { //передаем по очереди в стэк
		stack_push(stack, c[i]);
	}
	task1(stack);
}