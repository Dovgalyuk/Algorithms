#include <iostream>
#include <string>
#include "stack.h"
using namespace std;

bool CheckRightStr(string str, const string openDelim = "([{", const string closeDelim = ")]}")
{
	Stack* stack = new Stack();
	for (int i = 0; i < str.length(); i++)
	{
		char ch = str[i];
		if (openDelim.find(ch) != string::npos)
		{
			stack->Push(ch);
			//str.erase(str.begin() + i);
		}
	}
	while (!stack->Empty())
	{
		char ch = stack->Get();
		if (ch < 0) break;
		char toFind = closeDelim[openDelim.find(ch)]; // at the same index like ( and ) is on 0
		if (str.find(toFind) != string::npos) stack->Pop();
		else return false;
	}
	delete stack;
	return true;
}

void Say(bool value)
{
	if (value) cout << "YES";
	else cout << "NO";
}

int main()
{
	string toCheck;
	cout << "Enter string to check: ";
	cin >> toCheck;
	Say(CheckRightStr(toCheck));
	//Fixed for "(][)" it says YES, is it right? i think so because there was no condition about mark order
}