#include <iostream>
#include <fstream>
#include <algorithm>
#include "stack.h"
using namespace std;


int main()
{
	fstream file;
	file.open("input.txt");
	string tag;
	MyStack<string>* stack = new MyStack<string>();
	while (file >> tag)
	{
		std::transform(tag.begin(), tag.end(), tag.begin(), tolower);
		if (stack->Empty())
		{
			stack->Push(tag);
		}
		else
		{
			string without;
			if (tag[1] == '/')
			{
				tag.erase(tag.begin() + 1);
			}
			string lastElement = stack->Get();
			if (tag == lastElement)
			{
				stack->Pop();
			}
			else
			{
				stack->Push(tag);
			}
		}
	}
	if (stack->Empty())
	{
		cout << "Yes";
	}
	else
	{
		cout << "No";
	}
}