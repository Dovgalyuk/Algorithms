#include <iostream>
#include "stack.h"
#include "vector.h"
#include <string>

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
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value + second_value);
	cout << "Успешно!\n";
}

//Вычесть 2 числа в стеке
void stack_minus(Stack *stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value - second_value);
	cout << "Успешно!\n";
	
}

//Разделить 2 числа в стеке
void divide(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);
	if (second_value == 0) {
		throw "Divide by zero!";
	}
	else {
		stack_push(stack, first_value / second_value);
		cout << "Успешно!\n";
	}
}

//умножить 2 числа в стеке
void multiply(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value * second_value);
	cout << "Успешно!\n";
}

//Остаток от деления
void percent(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);
	if (second_value == 0) {
		throw "Divide by zero!";
	}
	else {
		stack_push(stack, first_value % second_value);
		cout << "Успешно!\n";
	}
}

//Дублировать вершину стека
void duplicate(Stack* stack) {
	int value = stack_get(stack);
	stack_push(stack, value);
	cout << "Успешно!\n";
}

//Удалить вершину стека
void drop(Stack* stack) {
	stack_pop(stack);
	cout << "Успешно!\n";
}

//Меняет местами два числа на вершине стека
void swap(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value);
	stack_push(stack, second_value);
	cout << "Успешно!\n";
}

//Добавить элемент в стек, который находится под вершиной
void over(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);

	stack_push(stack, first_value);
	stack_push(stack, second_value);
	cout << "Успешно!\n";
}



//первый становится вторым (последний(вершина) элемент стека становится вторым)
//второй становится третьим (второй становится первым элементом в стеке)
//третий становится первым (первый элемент стека становится последним (вершина))
void rot(Stack *stack) {
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

//Показать и извлечь из стека
void show_and_pop(Stack* stack) {
	cout << stack_get(stack) << "\n";
	stack_pop(stack);
}

void program_execution(Stack* stack, bool& is_run) {

	string choise;
	cout << "choise: ";
	cin >> choise;

	for (char _choise : choise) {
		if (_choise >= '0' && _choise <= '9') {
			stack_push(stack, _choise - 48);
			continue;
		}
		switch (_choise) {
			//Сложить верхние 2 элемента стека +
		case '+':
			stack_plus(stack);
			break;

			//Вычесть верхние 2 элемента стека -
		case '-':
			stack_minus(stack);
			break;

			//Умножить верхние 2 элемента стека *
		case '*':
			multiply(stack);
			break;

			//Разделить верхние 2 элемента стека /
		case '/':
			divide(stack);
			break;
		case '%':
			percent(stack);
			break;
			//Дублирует верхний элемент стека z 
		case 'z':
			duplicate(stack);
			break;

			//Удаляет верхний элемент стека x
		case 'x':
			drop(stack);
			break;

			//меняет местами два числа на вершине стека c
		case 'c':
			swap(stack);
			break;

			//берёт элемент под вершиной стека и добавляет его в стек v
		case 'v':
			over(stack);
			break;

			//перемещает "по кругу" верхние три элемента стека b 
		case 'b':
			rot(stack);
			break;

			//извлекает из стека верхний элемент и выводит на экран m 
		case 'm':
			show_and_pop(stack);
			break;

			//Показать меню
		case 's':
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
	}
}


int main()
{
	setlocale(LC_ALL, "rus");

	Stack *stack = stack_create();
	bool is_run = true;

	show_menu();
	
	do
	{
		try
		{
			program_execution(stack, is_run);
		}
		catch (const char* a)
		{
			cout << a << "\n";
		}
	} while (is_run);
}
