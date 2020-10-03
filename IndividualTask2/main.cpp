#include <iostream>
#include "stack.h"

using namespace std;

void calc_op(Stack* stack)
{
	List* temp_l_c = list_create();

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			temp_l_c->first->operation = stack_get_op(stack);
		else
		{
			char temp[256]= "";
			itoa(stack_get_dt(stack), temp, 10);
			list_insert_after(temp_l_c, temp_l_c->first, temp);
		}
		stack_pop(stack);
	}
	
	ListItem* temp_l_i = temp_l_c->first;
	Data temp_dt = 0;
	char temp_str[256] = "";
	
	if (temp_l_i->operation == '+')
	{
		temp_dt = temp_l_i->next->data + temp_l_i->next->next->data;
	}
	if (temp_l_i->operation == '-')
	{
		temp_dt = temp_l_i->next->data - temp_l_i->next->next->data;
	}
	if (temp_l_i->operation == '/')
	{
		temp_dt = temp_l_i->next->data / temp_l_i->next->next->data;
	}
	if (temp_l_i->operation == '*')
	{
		temp_dt = temp_l_i->next->data * temp_l_i->next->next->data;
	}

	itoa(temp_dt, temp_str, 10);
	list_delete(temp_l_c);
	stack_push(stack, temp_str);
}

void calc_proc(Stack* stack)
{
	int i, counter; //counter for data position check
	counter = i = 0;
	while (i < 5)
	{
		char str[256] = "";
		cout << "Enter number or operation: ";
		cin >> str;
		cout << endl;
		if (is_dt(str) == true)
		{
			stack_push(stack, str);
			counter += 1;
			i++;
		}
		else if (is_op(str) == true)
		{
			if (counter < 2)
			{
				cout << "Error, incorrect operation" << endl;
				cout << endl;
			}
			else
			{
				stack_push(stack, str);
				calc_op(stack);
				if (i == 4)
				{
					cout << "The result of operation: " << stack_get_dt(stack) << endl;
					cout << endl;
				}
				counter -= 1;
				i++;
			}
		}
		else
		{
			cout << "Error, please enter correct data" << endl;
			cout << endl;
		}
		cin.clear();
	}
}

int main()
{
	Stack* stack = stack_create();
	calc_proc(stack);
	stack_delete(stack);

	return 0;
}
