#include <iostream>
#include "list.h"
#include "stack.h"
#include <string>


using namespace std;


//
//char instruction (string command) {
//	
//		if (command == "+" || command == "-" || command == "*" || command == "/" || command == "%")
//		{
//			return '+';
//		}
//		else if (command == ".") {
//			return command[0];
//		}
//		else if(command[0] >= '0' && command[0] <= '9') {
//			return 'A';
//		}
//		else {
//			return 'B';
//		}
//	
//}
//
void writeData(Stack* stack, char num) {//Запись данных в стек
	int value = num - '0';//Перевод значения в int
	stack_push(stack, value);//Записываем данные в стек
}

void setnum(Stack* stack) {
	int num;
	cout << "введите число с клавиатуры:";
	cin >> num;
	stack_push(stack, num);
}

void operations(Stack* stack, char operation) {//Арифметические операции
	int num = stack_get(stack);
	stack_pop(stack);
	int num2 = stack_get(stack);
	stack_pop(stack);

	switch (operation)
	{
	case '+':
		stack_push(stack, num + num2);
		break;
	case '-':
		stack_push(stack, num - num2);
		break;
	case '*':
		stack_push(stack, num * num2);
		break;
	case '/':
		if (num2 == 0)
		{
			cout<<"На 0 делить нельзя";
		}
		stack_push(stack, num / num2);
		break;
	case '%':
		if (num2 == 0)
		{
			cout << "На 0 делить нельзя";
		}
		stack_push(stack, num % num2);
		break;
	default:
		break;
	}
}


void correctNum(Stack *stack) 
{//Удаляем значение с вершины стека
	int num = stack_get(stack);
	stack_pop(stack);
	if (num == 0) {
		stack_push(stack, 1);//Записываем в стек 1, если значение равно 0
	}
	else stack_push(stack, 0);//Иначе заносим в стек 0
}

void compareNum(Stack* stack) {//Сравнение значений
	int num = stack_get(stack);
	stack_pop(stack);
	int num2 = stack_get(stack);
	stack_pop(stack);
	if (num > num2) {//Если первое больше второго,то записываем в стек 1
		stack_push(stack, 1);
	}
	else {//иначе 0
		stack_push(stack, 0);
	}
}

char checkingForNumber(char command) {
	if (command >= '0' && command <= '9')
	{
		return 'n';
	}
	else if(command == '+' || command == '-' || command == '*' || command == '/' || command == '%')
	{
		return '+';
	}
	else
	{
		return command;
	}
}


void programCommand(Stack* stack) {

	string command;
	getline(cin, command);
	if (command == "")
	{
		cout << "Error! Enter command list\n";
		programCommand(stack);
	}
	else
	{
		int i = 0;
		while (command[i] != '\0')
		{
			char thisCommand = ' ';
			thisCommand = checkingForNumber(command[i]);
			switch (thisCommand)
			{
			case 'n'://Занести числа в стек
				writeData(stack, command[i]);
				break;
			case '+'://Логические операции
				operations(stack, command[i]);
				break;
			case '!'://Логическое "не"
				correctNum(stack);
				break;
			case '`'://Логическое "больше"
				compareNum(stack);
				break;
			case ':'://Дублирует значение на вершине стека
				stack_push(stack, stack_get(stack));
				break;

			case '.'://извлекает значение из стека и выводит его.
				cout << stack_get(stack) << endl;
				stack_pop(stack);
				break;
			case '&'://Запрашивает число с клавиатуры и заносит его в стек.
				setnum(stack);
				break;
			default:
				break;
			}
			i++;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "ru");

	Stack* stack = stack_create();
	programCommand(stack);
	stack_delete(stack);

	return 0;
}
