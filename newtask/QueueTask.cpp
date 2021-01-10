#include <iostream>
#include "queue.h"

using namespace std;

char matrix[26][26];
const unsigned diff = 65;

bool find_elem(Vector* vec, char to_check, size_t& index, size_t& element_count)
{
	for (int i = 0; i < element_count; i++)
	{
		if (vec->GetValue(i) == to_check)
		{
			index = i;
			return true;
		}
	}
	index = element_count++;
	return false;
}

int main()
{
	char start;
	cin >> start;
	size_t elem_count = 0;
	Vector* elements = new Vector();
	while (cin)
	{
		char trash;
		char chain1, chain2;
		cin >> chain1 >> trash >> trash >> chain2;
		size_t index1, index2;
		if (!find_elem(elements, chain1, index1, elem_count))
		{
			elements->Set(index1, chain1);
		}
		if (!find_elem(elements, chain2, index2, elem_count))
		{
			elements->Set(index2, chain2);
		}
		matrix[index1][index2] = 1;
	}

	size_t startIndex;
	find_elem(elements, start, startIndex, elem_count);

	bool* vertexes = new bool[elem_count];
	for (int i = 0; i < elem_count; i++)
	{
		vertexes[i] = false;
	}

	vertexes[start] = 0;
	Queue* queue = new Queue();
	queue->Insert(startIndex);
	while (!queue->IsEmpty())
	{
		Data vertex = queue->Get();
		queue->Remove();
		for (int i = 0; i < elem_count; i++)
		{
			if (vertexes[i] == false && matrix[vertex][i] == 1)
			{
				queue->Insert(i);
				vertexes[i] = true;
			}
		}
	}

	for (int i = 0; i < elem_count; i++)
	{
		if (vertexes[i] == true)
			cout << (char)elements->GetValue(i) << " ";
	}

	delete elements;
	delete queue;
}