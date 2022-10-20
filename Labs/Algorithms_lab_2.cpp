#include <iostream>
#include "stack.h"
#include "vector.h"
#include <string>
#include <conio.h>

using namespace std;

//0 - 9 - заносит число в стек
//+ -*/ % -арифметические операции.Извлекают два числа из стека, а потом заносят туда результат
//dup - дублирует число на вершине стека z 122
//drop - удаляет число с вершины стека x 120
//swap - меняет местами два числа на вершине стека c 99 
//over - берёт элемент под вершиной стека и добавляет его в стек v 118
//rot - перемещает "по кругу" верхние три элемента стека b 98 
//. - извлекает из стека верхний элемент и выводит на экран m 109

void show_menu() {
	cout << "Нажмите 0-9 для занесения числа в стек\n";
	cout << "Нажмите +-*/% чтобы извлечь 2 верхних числа стека и произвести соотв. операцию\n";
	cout << "Нажмите z(dup), чтобы продублировать вершину стека\n";
	cout << "Нажмите x(drop), чтобы удалить вершину стека\n";
	cout << "Нажмите c(swap), чтобы поменять местами 2 элемента вершины стека\n";
	cout << "Нажмите v(over), чтобы добавить элемент в стек, который находится под вершиной\n";
	cout << "Нажмите b(rot), чтобы переместить элементы 'по кругу' верхние три элемента стека\n";
	cout << "Нажмите m(.), чтобы извлечь и показать вершину стека\n";
	cout << "Нажмите s, чтобы показать меню и очистить консоль\n";
	cout << "Нажмите ESC, чтобы закончить выполнение программы\n\n";
}

//Сложить 2 числа в стеке
void stack_plus(Stack *stack) {
	try
	{
		int first_value = stack_get(stack);
		stack_pop(stack);

		int second_value = stack_get(stack);
		stack_pop(stack);

		stack_push(stack, first_value + second_value);
		cout << "Успешно!\n";
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}
}

//Вычесть 2 числа в стеке
void stack_minus(Stack *stack) {
	try
	{
		int first_value = stack_get(stack);
		stack_pop(stack);

		int second_value = stack_get(stack);
		stack_pop(stack);

		stack_push(stack, first_value - second_value);
		cout << "Успешно!\n";
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}
}

//Разделить 2 числа в стеке
void divide(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);
	if (second_value == 0) {
		throw exception("Divide by zero!\n");
	}
	else {
		stack_push(stack, first_value / second_value);
	}
}

//умножить 2 числа в стеке
void multiply(Stack* stack) {
	try
	{
		int first_value = stack_get(stack);
		stack_pop(stack);

		int second_value = stack_get(stack);
		stack_pop(stack);

		stack_push(stack, first_value * second_value);
		cout << "Успешно!\n";
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}
}

//Остаток от деления
void percent(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);
	if (second_value == 0) {
		throw exception("Divide by zero!\n");
	}
	else {
		stack_push(stack, first_value % second_value);
		cout << "Успешно!\n";
	}
}

//Дублировать вершину стека
void duplicate(Stack* stack) {
	try
	{
		int value = stack_get(stack);
		stack_push(stack, value);
		cout << "Успешно!\n";
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}
}

//Удалить вершину стека
void drop(Stack* stack) {
	try
	{
		stack_pop(stack);
		cout << "Успешно!\n";
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}
}

//Меняет местами два числа на вершине стека
void swap(Stack* stack) {
	try
	{
		int first_value = stack_get(stack);
		stack_pop(stack);

		int second_value = stack_get(stack);
		stack_pop(stack);

		stack_push(stack, first_value);
		stack_push(stack, second_value);
		cout << "Успешно!\n";
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}
}

//Добавить элемент в стек, который находится под вершиной
void over(Stack* stack) {
	try
	{
		int first_value = stack_get(stack);
		stack_pop(stack);

		int second_value = stack_get(stack);

		stack_push(stack, first_value);
		stack_push(stack, second_value);
		cout << "Успешно!\n";
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}

}



//первый становится вторым (последний(вершина) элемент стека становится вторым)
//второй становится третьим (второй становится первым элементом в стеке)
//третий становится первым (первый элемент стека становится последним (вершина))
void rot(Stack *stack) {
	try
	{
		int first_value = stack_get(stack); //Первый элемент (Последний(вершина) в стеке) 3
		stack_pop(stack);

		int second_value = stack_get(stack); //Второй элемент  2
		stack_pop(stack);

		int third_value = stack_get(stack); //Третий элемент (первый в стеке) 1
		stack_pop(stack);

		stack_push(stack, second_value); //второй стал первым элементом стека 1
		stack_push(stack, first_value); //вершина стека стала вторым элементом 3
		stack_push(stack, third_value); //первый элемент стека стал вершиной(последним) 2
		cout << "Успешно!\n";
	}
	catch (const std::exception& e)
	{
		cout << e.what() << "\n";
	}
}

//Показать и извлечь из стека
void show_and_pop(Stack* stack) {
	try {
		cout << stack_get(stack) << "\n";
		stack_pop(stack);
	}
	catch (const exception& e) {
		cout << e.what() << "\n";
	}
}

void program_execution(Stack* stack) {

	bool is_run = true;

	do
	{

		char choise = _getch();

		switch (choise) {

			//Добавить на вершину стэка 0 
		case 48:
			stack_push(stack, 0);
			cout << "Число добавлено в стек\n";
			break;
			
			//Добавить на вершину стэка 1
		case 49:
			stack_push(stack, 1);
			cout << "Число добавлено в стек\n";
			break;

			//Добавить на вершину стэка 2
		case 50:
			stack_push(stack, 2);
			cout << "Число добавлено в стек\n";
			break;

			//Добавить на вершину стэка 3
		case 51:
			stack_push(stack, 3);
			cout << "Число добавлено в стек\n";
			break;

			//Добавить на вершину стэка 4
		case 52:
			stack_push(stack, 4);
			cout << "Число добавлено в стек\n";
			break;

			//Добавить на вершину стэка 5
		case 53:
			stack_push(stack, 5);
			cout << "Число добавлено в стек\n";
			break;

			//Добавить на вершину стэка 6
		case 54:
			stack_push(stack, 6);
			cout << "Число добавлено в стек\n";
			break;

			//Добавить на вершину стэка 7
		case 55:
			stack_push(stack, 7);
			cout << "Число добавлено в стек\n";
			break;

			//Добавить на вершину стэка 8
		case 56:
			stack_push(stack, 8);
			cout << "Число добавлено в стек\n";
			break;

			//Добавить на вершину стэка 9
		case 57:
			stack_push(stack, 9);
			cout << "Число добавлено в стек\n";
			break;

			//Сложить верхние 2 элемента стека +
		case 43:
			stack_plus(stack);
			break;

			//Вычесть верхние 2 элемента стека -
		case 45:
			stack_minus(stack);
			break;

			//Умножить верхние 2 элемента стека *
		case 42:
			multiply(stack);
			break;

			//Разделить верхние 2 элемента стека /
		case 47:
			try{
				divide(stack);
			}
			catch (const std::exception& e) {
				cout << e.what();
			}
			break;
		case 37:
			percent(stack);
			break;
			//Дублирует верхний элемент стека z 
		case 122:
			duplicate(stack);
			break;

			//Удаляет верхний элемент стека x
		case 120:
			drop(stack);
			break;

			//меняет местами два числа на вершине стека c
		case 99:
			swap(stack);
			break;

			//берёт элемент под вершиной стека и добавляет его в стек v
		case 118:
			over(stack);
			break;

			//перемещает "по кругу" верхние три элемента стека b 
		case 98:
			rot(stack);
			break;

			//извлекает из стека верхний элемент и выводит на экран m 
		case 109:
			show_and_pop(stack);
			break;

			//Показать меню
		case 115:
			cout << "\n";
			system("cls");
			show_menu();
			break;
			//Завершить выполнение программы
		case 27:
			is_run = false;
			break;
		default:
			break;
		}
	} while (is_run);
}


int main()
{
	setlocale(LC_ALL, "rus");

	Stack *stack = stack_create();

	show_menu();
	program_execution(stack);
	
}
