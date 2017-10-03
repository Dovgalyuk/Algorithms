/*	�������
	��������� �������� ����������� ��������������� ��������� ��� ������,
	������������� ����������������,��������� � �������. ��������� ������ 
	��������� ��������� ���������� ��������� � ������� � ������������ ����.
	���������� � ��������� �������� ��������������� ����� �����.
*/

#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include "../Library/stack.h"




int main() {

	//std::string test = "1+2*3-1";

	Stack * testStack = stack_create();
	std::string kek;

	

	while (!stack_empty(testStack))
	{
		std::cout << "Get: " << stack_get(testStack) << "\n";
		stack_pop(testStack);
	}

	stack_delete(testStack);


}