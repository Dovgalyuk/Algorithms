#include "stack.h"
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
	const string input_path ="input.txt";
	const string output_path ="output.txt";

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
	bool flag =true;

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
				flag &= stack_get(stack) == tag;
				stack_pop(stack);
			}
			else
				flag =false;

			if( ! flag)
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
				flag =false;
				while( ! stack_empty(stack))
					stack_pop(stack);
			}
			if(flag)
				fout << "YES" << endl;
			else
			{
				fout << "NO" << endl;
				flag =true;
			}
		}
	}
	fin.close();
	fout.close();
	stack_delete(stack);
}