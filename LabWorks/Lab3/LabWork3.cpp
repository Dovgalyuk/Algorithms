#include <iostream>
#include "vector.h"
#include "queue.h"
#include <fstream>
using namespace std;

int BFS(int** matrix, int start, int end, int V)
{
	bool* used = new bool[V];
	for (int i = 0; i < V; i++)
	{
		used[i] = false;
	}
	int min = NULL;
	Queue* queue;
	queue = queue_create();
	queue_insert(queue, start);
	int count = 0;
	while (!queue_empty(queue))
	{
		int st = queue_get(queue);
		used[st] = true;
		queue_remove(queue);
		count++;
		for (int i = 0; i < V; i++)
		{
			if ((matrix[st][i]) == 1 && (!used[i]))
			{
				if (i == end)
				{
					if (count < min || min == NULL)
					{
						min = count;
					}
				}
				queue_insert(queue, i);
			}
		}
	}
	delete[] used;
	return min;
}




int main()
{
	int V;
	ifstream file("input.txt");
	if (!file.is_open())
	{
		cout << "Error" << '\n';
	}
	file >> V;
	int** matrix = new int* [V];
	for (int i = 0; i < V; i++)
	{
		matrix[i] = new int[V];
	}
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			file >> matrix[i][j];
		}
	}
	file.close();
	ofstream out("output.txt");
	for (int i = 0; i < V; i++)
	{
		out << BFS(matrix, 0, i, V) << '\n';
	}
	



	for (int i = 0; i < V; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	return 0;
}
