#include "stack.h"
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
	const string input_path ="../../TestHTML/input.txt";
	const string output_path ="../../TestHTML/output.txt";

	ifstream fin;
	ofstream fout;

	fin.open(input_path);
	fout.open(output_path);
	if(! fin.is_open() || ! fout.is_open())
	{
		fin.close();
		fout.close();
		return 0;
	}

	string tag;
	string flag ="YES";

	Stack *stack =stack_create();

	while( ! fin.eof())
	{
		fin >> tag;

		tag.pop_back();
		tag.erase(0, 1);
		transform(tag.begin(), tag.end(), tag.begin(), tolower);

		if(tag.front() == '/')
		{
			tag.erase(0, 1);
			if( ! stack_empty(stack))
			{
				if(stack_get(stack) != tag)
					flag ="NO";
				stack_pop(stack);
			}
			else
				flag ="NO";

			if(flag =="NO")
			{
				while(fin.peek() != '\n' && ! fin.eof())
					fin.get();
			}
		}
		else
			stack_push(stack, tag);

		if(fin.peek() =='\n'|| fin.eof() )
		{
			if( ! stack_empty(stack))
			{
				flag ="NO";
				while( ! stack_empty(stack))
					stack_pop(stack);
			}
			fout << flag << endl;
			flag ="YES";
		}
	}
	fin.close();
	fout.close();
	stack_delete(stack);
}