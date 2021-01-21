#include <iostream>
#include <fstream>
#include <algorithm>
#include "stack.h"
using namespace std;

bool is_open_tag(string tag)
{
	return tag[1] != '/';
}

bool tag_same(string open, string close)
{
	for (int i = 0; i < open.size(); i++)
	{
		open[i] = tolower(open[i]);
	}
	string newclose;
	for (int i = 0; i < close.size(); i++)
	{
		if (i == 1) continue; // '/' symbol
		newclose += tolower(close[i]);
	}
	return open == newclose;
}

int main()
{
	fstream file;
	file.open("input.txt");
	string tag;
	MyStack<string>* stack = new MyStack<string>();
	bool right = true;
	while (file >> tag)
	{
		if (is_open_tag(tag))
		{
			stack->Push(tag);
		}
		else
		{
			string opentag = stack->Get();
			if (!tag_same(opentag, tag))
			{
				right = false;
				break;
			}

			stack->Pop();
		}
	}
	if (right && stack->Empty())
	{
		cout << "Yes";
	}
	else
	{
		cout << "No";
	}
}