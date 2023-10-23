#include<string>
#include<iostream>
#include<fstream>
#include<stack.h>
#include<vector>

using namespace std;


void check_input(Stack *stack, string input, const int stack_size, int &stack_fill_element)
{
	string comand = {}, num = {};

	for (basic_string<char>::size_type i = 0; i < input.length();i++)
	{
		if(isalpha(input[i])) comand += input[i];

		if (input[i] >= *"0" && input[i] <= *"9") num += input[i];
	}

	if (comand == "pop")
	{
		if (stack_fill_element)
		{
			cout << stack_get(stack) << endl;;

			stack_pop(stack);

			stack_fill_element--;
		}

		else cout << "BAD POP" << endl;
	}

	else if (comand == "push")
	{
		if (stack_fill_element + 1 <= stack_size)
		{
			stack_push(stack, stoi(num));

			stack_fill_element++;
		}

		else cout << "BAD PUSH" << endl;
	}

}


int main()
{
	string path = "input.txt"; //file added by cmake command 

	ifstream fin;
	fin.open(path);

	/*if (!fin.is_open())
	{
		cout << "Error not open file" << endl;
		return 1;
	}
	else
	{
		cout << "OPEN FILE!" << endl;
	}*/

	Stack* stack = stack_create();

	string input;
	getline(fin, input);

	int size_stack = stoi(input);
	int stack_fill_element = 0;
	

	while (!fin.eof())
	{
		input = "";

		getline(fin, input);

		check_input(stack, input, size_stack, stack_fill_element);
	}

	fin.close();

	cout << "Stack" << endl;

	//version which not coincide output data form task

	/*while (!stack_empty(stack))
	{
		cout << stack_get(stack) << endl;
		stack_pop(stack);
	}*/

	vector<Data> reverse;

	while (!stack_empty(stack))
	{
		reverse.insert(reverse.begin(), stack_get(stack));
		stack_pop(stack);
	}

	for (vector<Data>::size_type i = 0; i < reverse.size(); i++)
	{
		cout << reverse[i] << endl;
	}
	reverse.clear();

	stack_delete(stack);
	
	return 0;
}
