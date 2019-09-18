// Write a program that checks the correct placement of two types of quotation marks and brackets in a line. The program should output YES for the correct sequence and NO for the incorrect one.
// Example: Input: "ab(c 'de' f)gt" - Output: YES
// Example 2: Input: "adjsk 'z' frr') - Output: NO
// ("") - true, а (")" - false
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "list.h"
#include "stack.h"

using namespace std;

int main()
{
	ifstream fileIn("input.txt");
	ofstream fileOut("output.txt");

	Stack* stack = stack_create();
	string iData;

	if (fileIn)
	{
		while (!fileIn.eof())
		{
			getline(fileIn, iData);
			transform(iData.begin(), iData.end(), iData.begin(), ::tolower);
			
			cout << iData << endl;

			for (int i = 0; i < int(iData.size()); i++)
			{
				string current;
				current = iData[i];

				if (current == "(")
				{
					stack_push(stack, current);
				}
				else if (current == "'")
				{
					if (stack_get(stack) == "'" && current == "'")
					{
						stack_pop(stack);
					}
					else
					{
						stack_push(stack, current);
					}
				}
				else if (current == "\"")
				{
					if (stack_get(stack) == "\"" && current == "\"")
					{
						stack_pop(stack);
					}
					else
					{
						stack_push(stack, current);
					}
				}
				else if (current == ")")
				{
					if (stack_empty(stack))
					{
						fileOut << "NO";
						cout << "NO";
						return 0;
					}
					string last = stack_get(stack);
					if (current == ")" && last == "(")
					{
						stack_pop(stack);
					}
				}

			}
		}
	}
	else
	{
		cout << "Unable to open file!" << endl;
		system("pause");
		return 0;
	}
	if (stack_empty(stack))
	{
		cout << "YES" << endl;
		fileOut << "YES" << endl;
	}
	else
	{
		cout << "NO";
		fileOut << "NO" << endl;
	}
	fileIn.close();
	fileOut.close();
	stack_delete(stack);
	return 0;
} 