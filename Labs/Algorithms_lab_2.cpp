#include <iostream>
#include "stack.h"
#include "vector.h"
#include <string>

using namespace std;

//0 - 9 - ������� ����� � ����
//+ -*/ % -�������������� ��������.��������� ��� ����� �� �����, � ����� ������� ���� ���������
//dup - ��������� ����� �� ������� ����� z 122
//drop - ������� ����� � ������� ����� x 120
//swap - ������ ������� ��� ����� �� ������� ����� c 99 
//over - ���� ������� ��� �������� ����� � ��������� ��� � ���� v 118
//rot - ���������� "�� �����" ������� ��� �������� ����� b 98 
//. - ��������� �� ����� ������� ������� � ������� �� ����� m 109

void show_menu() {
	cout << "������� 0-9 ��� ��������� ����� � ����\n";
	cout << "������� +-*/% ����� ������� 2 ������� ����� ����� � ���������� �����. ��������\n";
	cout << "������� z(dup), ����� �������������� ������� �����\n";
	cout << "������� x(drop), ����� ������� ������� �����\n";
	cout << "������� c(swap), ����� �������� ������� 2 �������� ������� �����\n";
	cout << "������� v(over), ����� �������� ������� � ����, ������� ��������� ��� ��������\n";
	cout << "������� b(rot), ����� ����������� �������� '�� �����' ������� ��� �������� �����\n";
	cout << "������� m(.), ����� ������� � �������� ������� �����\n";
	cout << "������� s, ����� �������� ���� � �������� �������\n";
	cout << "������� ESC, ����� ��������� ���������� ���������\n\n";
}

//������� 2 ����� � �����
void stack_plus(Stack *stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value + second_value);
	cout << "�������!\n";
}

//������� 2 ����� � �����
void stack_minus(Stack *stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value - second_value);
	cout << "�������!\n";
	
}

//��������� 2 ����� � �����
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
		cout << "�������!\n";
	}
}

//�������� 2 ����� � �����
void multiply(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value * second_value);
	cout << "�������!\n";
}

//������� �� �������
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
		cout << "�������!\n";
	}
}

//����������� ������� �����
void duplicate(Stack* stack) {
	int value = stack_get(stack);
	stack_push(stack, value);
	cout << "�������!\n";
}

//������� ������� �����
void drop(Stack* stack) {
	stack_pop(stack);
	cout << "�������!\n";
}

//������ ������� ��� ����� �� ������� �����
void swap(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);
	stack_pop(stack);

	stack_push(stack, first_value);
	stack_push(stack, second_value);
	cout << "�������!\n";
}

//�������� ������� � ����, ������� ��������� ��� ��������
void over(Stack* stack) {
	int first_value = stack_get(stack);
	stack_pop(stack);

	int second_value = stack_get(stack);

	stack_push(stack, first_value);
	stack_push(stack, second_value);
	cout << "�������!\n";
}



//������ ���������� ������ (���������(�������) ������� ����� ���������� ������)
//������ ���������� ������� (������ ���������� ������ ��������� � �����)
//������ ���������� ������ (������ ������� ����� ���������� ��������� (�������))
void rot(Stack *stack) {
	int first_value = stack_get(stack); //������ ������� (���������(�������) � �����) 3
	stack_pop(stack);

	int second_value = stack_get(stack); //������ �������  2
	stack_pop(stack);

	int third_value = stack_get(stack); //������ ������� (������ � �����) 1
	stack_pop(stack);

	stack_push(stack, second_value); //������ ���� ������ ��������� ����� 1
	stack_push(stack, first_value); //������� ����� ����� ������ ��������� 3
	stack_push(stack, third_value); //������ ������� ����� ���� ��������(���������) 2
	cout << "�������!\n";
}

//�������� � ������� �� �����
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
			//������� ������� 2 �������� ����� +
		case '+':
			stack_plus(stack);
			break;

			//������� ������� 2 �������� ����� -
		case '-':
			stack_minus(stack);
			break;

			//�������� ������� 2 �������� ����� *
		case '*':
			multiply(stack);
			break;

			//��������� ������� 2 �������� ����� /
		case '/':
			divide(stack);
			break;
		case '%':
			percent(stack);
			break;
			//��������� ������� ������� ����� z 
		case 'z':
			duplicate(stack);
			break;

			//������� ������� ������� ����� x
		case 'x':
			drop(stack);
			break;

			//������ ������� ��� ����� �� ������� ����� c
		case 'c':
			swap(stack);
			break;

			//���� ������� ��� �������� ����� � ��������� ��� � ���� v
		case 'v':
			over(stack);
			break;

			//���������� "�� �����" ������� ��� �������� ����� b 
		case 'b':
			rot(stack);
			break;

			//��������� �� ����� ������� ������� � ������� �� ����� m 
		case 'm':
			show_and_pop(stack);
			break;

			//�������� ����
		case 's':
			cout << "\n";
			system("cls");
			show_menu();
			break;
			//��������� ���������� ���������
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
