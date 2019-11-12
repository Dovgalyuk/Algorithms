#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "stack.h"

using namespace std;

int main()
{
	ifstream fileIn("input.txt"); 

	Stack* stack = stack_create(); 
	bool is_correct = true; 
	string Data; 
	while (!fileIn.eof()) 
	{
		getline(fileIn, Data); 
		transform(Data.begin(), Data.end(), Data.begin(), ::toupper); 
		while (Data.find(' ') != string::npos) 
			Data.erase(Data.begin() + Data.find(' ')); 
		size_t sl_pos = Data.find('/'); 
		size_t op_pos = Data.find('<'); 
		if (sl_pos == string::npos) 
		{
			stack_push(stack, Data.substr(op_pos + 1, Data.find('>') - op_pos - 1)); 
		}
		else
		{
			if (!stack_empty(stack) && stack_get(stack) == Data.substr(sl_pos + 1, Data.find('>') - sl_pos - 1)) 
				stack_pop(stack); 
			else
			{
				is_correct = false; 
				break; 
			}
		}
	}
	
	if (is_correct && stack_empty(stack)) 
		cout << "YES";
	else
		cout << "NO";
	stack_delete(stack);
}