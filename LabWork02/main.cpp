// Write a program that uses a breadth-first search and displays a list of substances that can be obtained from the source.
// Example: Input: "A A->B B->C D->E" - Output: "B C"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "queue.h"

using namespace std;

int main()
{
	ifstream fileIn("input.txt");
	ofstream fileOut("output.txt");
	
	Queue* queue = queue_create();
	string iData = "";
	int start = 0;
	bool graph[26][26];
	bool used[26];
	int dst[26];

	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			graph[i][j] = false;
		}
	}

	if (fileIn)
	{
		while (!fileIn.eof())
		{
			getline(fileIn, iData);
			transform(iData.begin(), iData.end(), iData.begin(), ::toupper);

			if (iData.size() == 1)
			{
				start = iData[0] - 'A';
			}
			else
			{
				graph[iData[0] - 'A'][iData[3] - 'A'] = true;
			}
		}
	}
	else
	{
		cout << "Unable to open file!" << endl;
		system("pause");
		return 0;
	}

	for (int i = 0; i < 26; i++)
	{
		used[i] = false;
		dst[i] = -1;
	}
	queue_insert(queue, start);
	while (!queue_empty(queue))
	{
		int current = queue_get(queue);
		queue_remove(queue);
		for (int i = 0; i < 26; i++)
		{
			if (!used[i] && graph[current][i])
			{
				queue_insert(queue, i);
				used[i] = true;
				dst[i] = dst[current] + 1;
			}
		}
	}
	for (int i = 0; i < 26; i++)
	{
		if (dst[i] != -1 && i != start)
		{
			cout << (char)(i + 'A') << endl;
			fileOut << (char)(i + 'A') << endl;
		}
	}
	fileIn.close();
	fileOut.close();
	queue_delete(queue);
	return 0;
}