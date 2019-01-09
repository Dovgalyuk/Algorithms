#include "pch.h"
#include <iostream>
#include "queue.h"
#include <string>
#include <fstream>

using namespace std;

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	string input, result;

	while (!fin.eof())
	{
		Queue* Numbers = queue_create();

		fin >> input;

		for (int i = 0; i < input.size(); i++)
		{
			if (isdigit(input[i]))
			{
				queue_insert(Numbers, input[i]);
			}
			else
			{
				result += input[i];
			}

		}

		while (!queue_empty(Numbers))
		{
			result += queue_get(Numbers);
			queue_remove(Numbers);
		}

		fout << result << endl;

		queue_delete(Numbers);
		result.clear();
	}
}
