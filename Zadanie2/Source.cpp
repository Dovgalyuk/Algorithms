/*	«адание
	¬ычислить значение корректного арифметического выражени€ без скобок,
	использующего операциисложени€,вычитани€ и делени€. ѕрограмма должна 
	учитывать приоритет операторов умножени€ и делени€ и использовать стек.
	ќперандами в выражении €вл€ютс€ неотрицательные целые числа.
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