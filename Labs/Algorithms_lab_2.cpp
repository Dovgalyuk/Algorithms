#include <iostream>
#include "stack.h"
#include "vector.h"
#include <string>
#include <conio.h>

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
	try
	{
		int first_value = stack_get(stack);
		stack_pop(stack);

		int second_value = stack_get(stack);
		stack_pop(stack);

		stack_push(stack, first_value + second_value);
		cout << "�������!\n";
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}
}

//������� 2 ����� � �����
void stack_minus(Stack *stack) {
	try
	{
		int first_value = stack_get(stack);
		stack_pop(stack);

		int second_value = stack_get(stack);
		stack_pop(stack);

		stack_push(stack, first_value - second_value);
		cout << "�������!\n";
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}
}

//��������� 2 ����� � �����
void divide(Stack* stack) {
	try
	{
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
		cout << "�������!\n";
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}
}

//�������� 2 ����� � �����
void multiply(Stack* stack) {
	try
	{
		int first_value = stack_get(stack);
		stack_pop(stack);

		int second_value = stack_get(stack);
		stack_pop(stack);

		stack_push(stack, first_value * second_value);
		cout << "�������!\n";
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}
}

//������� �� �������
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
		cout << "�������!\n";
	}
}

//����������� ������� �����
void duplicate(Stack* stack) {
	try
	{
		int value = stack_get(stack);
		stack_push(stack, value);
		cout << "�������!\n";
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}
}

//������� ������� �����
void drop(Stack* stack) {
	try
	{
		stack_pop(stack);
		cout << "�������!\n";
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}
}

//������ ������� ��� ����� �� ������� �����
void swap(Stack* stack) {
	try
	{
		int first_value = stack_get(stack);
		stack_pop(stack);

		int second_value = stack_get(stack);
		stack_pop(stack);

		stack_push(stack, first_value);
		stack_push(stack, second_value);
		cout << "�������!\n";
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}
}

//�������� ������� � ����, ������� ��������� ��� ��������
void over(Stack* stack) {
	
	try
	{
		int first_value = stack_get(stack);
		stack_pop(stack);

		int second_value = stack_get(stack);

		stack_push(stack, first_value);
		stack_push(stack, second_value);
		cout << "�������!\n";
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}

}



//������ ���������� ������ (���������(�������) ������� ����� ���������� ������)
//������ ���������� ������� (������ ���������� ������ ��������� � �����)
//������ ���������� ������ (������ ������� ����� ���������� ��������� (�������))
void rot(Stack *stack) {
	try
	{
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
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}
}

//�������� � ������� �� �����
void show_and_pop(Stack* stack) {
	try {
		cout << stack_get(stack) << "\n";
		stack_pop(stack);	
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}
}

void program_execution(Stack* stack) {

	bool is_run = true;

	do
	{

		char choise = _getch();

		switch (choise) {

			//�������� �� ������� ����� 0 
		case 48:
			stack_push(stack, 0);
			cout << "����� ��������� � ����\n";
			break;
			
			//�������� �� ������� ����� 1
		case 49:
			stack_push(stack, 1);
			cout << "����� ��������� � ����\n";
			break;

			//�������� �� ������� ����� 2
		case 50:
			stack_push(stack, 2);
			cout << "����� ��������� � ����\n";
			break;

			//�������� �� ������� ����� 3
		case 51:
			stack_push(stack, 3);
			cout << "����� ��������� � ����\n";
			break;

			//�������� �� ������� ����� 4
		case 52:
			stack_push(stack, 4);
			cout << "����� ��������� � ����\n";
			break;

			//�������� �� ������� ����� 5
		case 53:
			stack_push(stack, 5);
			cout << "����� ��������� � ����\n";
			break;

			//�������� �� ������� ����� 6
		case 54:
			stack_push(stack, 6);
			cout << "����� ��������� � ����\n";
			break;

			//�������� �� ������� ����� 7
		case 55:
			stack_push(stack, 7);
			cout << "����� ��������� � ����\n";
			break;

			//�������� �� ������� ����� 8
		case 56:
			stack_push(stack, 8);
			cout << "����� ��������� � ����\n";
			break;

			//�������� �� ������� ����� 9
		case 57:
			stack_push(stack, 9);
			cout << "����� ��������� � ����\n";
			break;

			//������� ������� 2 �������� ����� +
		case 43:
			stack_plus(stack);
			break;

			//������� ������� 2 �������� ����� -
		case 45:
			stack_minus(stack);
			break;

			//�������� ������� 2 �������� ����� *
		case 42:
			multiply(stack);
			break;

			//��������� ������� 2 �������� ����� /
		case 47:
			try{
				divide(stack);
			}
			catch (const std::exception& e)
			{
				cout << e.what() << "\n";
			}
			break;
		case 37:
			try
			{
				percent(stack);
			}
			catch (const std::exception& e)
			{
				cout << e.what() << "\n";
			}
			break;
			//��������� ������� ������� ����� z 
		case 122:
			duplicate(stack);
			break;

			//������� ������� ������� ����� x
		case 120:
			drop(stack);
			break;

			//������ ������� ��� ����� �� ������� ����� c
		case 99:
			swap(stack);
			break;

			//���� ������� ��� �������� ����� � ��������� ��� � ���� v
		case 118:
			over(stack);
			break;

			//���������� "�� �����" ������� ��� �������� ����� b 
		case 98:
			rot(stack);
			break;

			//��������� �� ����� ������� ������� � ������� �� ����� m 
		case 109:
			show_and_pop(stack);
			break;

			//�������� ����
		case 115:
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
	} while (is_run);
}


int main()
{
	setlocale(LC_ALL, "rus");

	Stack *stack = stack_create();

	show_menu();
	program_execution(stack);
	
}
