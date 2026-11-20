#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "stack.h"

using namespace std;

string to_lower(string s)
{
	transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
		return static_cast<char>(tolower(c));
	});

	return s;
}

bool validate_tags(const char* filename)
{
	ifstream input(filename);

	if (!input.is_open()) return false;

	Stack* stack = stack_create();
	string str;

	bool is_corect = 1;

	while (getline(input, str))
	{
		if (str.empty()) continue;

		string tag = to_lower(str);

		if (tag[1] == '/')
		{
			if (stack_empty(stack))
			{
				is_corect = 0;
				break;
			}

			tag.erase(1, 1);

			string top_tag = stack_get(stack);
			stack_pop(stack);

			if (top_tag != tag)
			{
				is_corect = 0;
				break;
			}
		} else stack_push(stack, tag);
	}

	if (!stack_empty(stack)) is_corect = 0;

	stack_delete(stack);

	return is_corect;
}

int main(int argc, char* argv[])
{
	char* file = argv[1];

	if (argc < 2)
	{
		cerr << "Eror open file" << endl;
		return 1;
	}

	if (validate_tags(file)) cout << "YES" << endl;
	else cout << "NO" << endl;
}