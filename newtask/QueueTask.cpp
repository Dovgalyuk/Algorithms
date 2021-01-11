#include <iostream>
#include "queue.h"

using namespace std;

const unsigned max_letter_cnt = 26;
const unsigned asciiDiff = 65;
char matrix[max_letter_cnt][max_letter_cnt];

int main()
{
	cout << "Enter elements or '.' to end: " << endl;
	char start;
	cin >> start;
	start -= asciiDiff;

	while (true)
	{
		char trash;
		char chain1, chain2;
		cin >> chain1;

		if (chain1 == '.') break;

		cin >> trash >> trash >> chain2;

		chain1 -= asciiDiff;
		chain2 -= asciiDiff;
		matrix[chain1][chain2] = 1;
	}
	
	bool* vertexes = new bool[26];
	for (int i = 0; i < 26; i++)
	{
		vertexes[i] = false;
	}

	vertexes[start] = 0;
	Queue* queue = new Queue();
	queue->Insert(start);
	while (!queue->IsEmpty())
	{
		Data vertex = queue->Get();
		queue->Remove();
		for (int i = 0; i < max_letter_cnt; i++)
		{
			if (vertexes[i] == false && matrix[vertex][i] == 1)
			{
				queue->Insert(i);
				vertexes[i] = true;
			}
		}
	}

	for (int i = 0; i < max_letter_cnt; i++)
	{
		if (vertexes[i] == true)
		{
			char symbol = i + asciiDiff;
			cout << symbol << " ";
		}
	}

	delete queue;
}