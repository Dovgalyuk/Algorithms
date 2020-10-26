#include <iostream>
#include <string>
#include "..\..\..\..\Desktop\stack.h"
using namespace std;

bool CheckRightStr(string str, const string openDelim = "([{", const string closeDelim = ")]}")
{
	Stack* stack = new Stack();
	for (int i = 0; i < str.length(); i++)
	{
		char ch = str[i];
		if (openDelim.find(ch))
		{
			stack->Push(ch);
			str.erase(str.begin() + i);
		}
	}
	while (!stack->Empty())
	{
		char ch = stack->Get();
		char toFind = closeDelim[openDelim.find(ch)]; // at the same index like ( and ) is on 0
		if (str.find(toFind)) stack->Pop();
		else return false;
	}
	return true;
}

void Say(bool value)
{
	if (value) cout << "YES";
	else cout << "NO";
}

int main()
{
	//CheckRightStr("([])");
	Say(CheckRightStr("(]"));
}