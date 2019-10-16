#include <fstream>
#include <string>
#include <algorithm>
#include <stack.h>

using namespace std;

int main()
{
	ifstream fileIn("input.txt");
	ofstream fileOut("output.txt");

	Stack* stack = stack_create();
	string Data;
	while (!fileIn.eof())
	{
		getline(fileIn, Data);
		transform(Data.begin(), Data.end(), Data.begin(), ::toupper);
		while (Data.find(' ') != string::npos)
			Data.erase(Data.begin() + Data.find(' '));
		if (Data.find('/') == string::npos)
		{
			Data.erase(Data.begin() + Data.find('<'));
			Data.erase(Data.begin() + Data.find('>'));
			stack_push(stack, Data);
		}
		else
		{
			Data.erase(Data.begin() + Data.find('<'));
			Data.erase(Data.begin() + Data.find('/'));
			Data.erase(Data.begin() + Data.find('>'));
			if (stack_get(stack) == Data)
				stack_pop(stack);
			else
			{
				stack_delete(stack);
				fileOut << "NO";
				return 0;
			}
		}
	}

	if (stack_empty(stack))
		fileOut << "YES";
	else
		fileOut << "NO";
	stack_delete(stack);
}