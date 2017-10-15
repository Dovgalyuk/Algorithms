/*	«адание
	¬ычислить значение корректного арифметического выражени€ без скобок,
	использующего операциисложени€,вычитани€ и делени€. ѕрограмма должна 
	учитывать приоритет операторов умножени€ и делени€ и использовать стек.
	ќперандами в выражении €вл€ютс€ неотрицательные целые числа.
*/




#include <iostream>
#include <conio.h>
#include <string>
//#include <string.h>
#include "../Library/stack.h"

using namespace std;
// превер€ет букву на то - символ ли это
bool is_znak(string insertString, int key);
// возвращает код знака либо -1
int get_znak(string insertString, int& key);
// возвращает число из строки inserString начина€ с номера элемента key
int get_number(string insertString, int& key);

int main() {

	//std::string test = "1+2*3-1";

	Stack * mainStack = stack_create();
	
		
	string insertString; int buffer = 0,buffer1 = 0,buffer2 = 0;
	getline(cin, insertString);
	



	int i = 0;
	while (i < insertString.size()) 
	{
		/*if (is_znak(insertString, i)) 
		{
		buffer2 =	get_znak(insertString, i);
		i++;
		}*/

		switch (insertString[i])
		{
			case '+': 
					buffer = get_number(insertString, i);
					stack_push(mainStack, buffer);i++;
				break;
			case '-':	
					buffer = get_number(insertString, i);
					buffer = buffer * -1;
					stack_push(mainStack, buffer);i++;
				break;
			case '*': 
					buffer1 = stack_get(mainStack);
					stack_pop(mainStack);
					buffer = get_number(insertString, i);
					buffer = buffer * buffer1;
					stack_push(mainStack, buffer);i++;
				break;	
			case '/':
					buffer1 = stack_get(mainStack);
					stack_pop(mainStack);
					buffer = get_number(insertString, i);
					buffer = buffer / buffer1;
					stack_push(mainStack, buffer);i++;
				break;
			default: buffer = get_number(insertString, i);	stack_push(mainStack, buffer);i++; break;
		
		}
		
	
	
	
	}


	

	int  answer = 0;


	while (!stack_empty(mainStack))
	{
		answer = answer + stack_get(mainStack);
		stack_pop(mainStack);
	}

	cout << answer;

	stack_delete(mainStack);
	
	
}

    bool is_znak(string insertString, int key)
	{
		if (insertString[key] == '-' || insertString[key] == '+' || insertString[key] == '*' || insertString[key] == '/')
			return true;
		else
			return false;	
	}

	int get_number(string insertString, int & key) 
	{
		int buffer = 0;
		
		while (isdigit(insertString[key]))
		{
			buffer = ((buffer) * 10 + insertString[key]) - '0';
			key++;
		}
		return buffer;
	}

	int get_znak(string insertString, int &key) {
		switch (insertString[key]) {
		case '+': return 1;break;
		case '-': return 2;break;
		case '*': return 3;break;
		case '/': return 4;break;
		default: return -1; break;
		}
		}
	
	
	
	
	
	
	
	