#include <iostream>
#include <fstream>
#include "queue.h"

int main()
{
	std::ifstream fin;
	fin.open("first.txt");

	int n = 0;
	//read n
	fin >> n;

	//pointer to start
	int* arr = new int[n * n];

	//filling the array
	if (fin.is_open()) {
		for (int i = 0; i < n * n; i++)
		{
			fin >> arr[i];
		}
	}
	else {
		std::cout << "Open error!\n";
	}
	fin.close();

	Queue* queue = queue_create();
	bool* was_in_queue = new bool[n]();
	int* distance = new int[n]();
	queue_insert(queue, 0);
	was_in_queue[0] = true;
	while (!queue_empty(queue))
	{
		int line = queue_get(queue);
		queue_remove(queue);
		for (int j = 0; j < n; j++)
		{
			if (arr[(line * n) + j] == 1 && was_in_queue[j] == false)
			{
				queue_insert(queue, j);
				distance[j] = distance[line] + 1;
				was_in_queue[j] = true;
			}
		}
	}

	std::ofstream fout;
	fout.open("second.txt");

	//output of results
	fout << arr[0] << "\n";
	for (int i = 1; i < n; i++)
	{
		if (was_in_queue[i] == false) fout << "none" << "\n";
		else fout << distance[i] << "\n";
	}
	delete[] was_in_queue;
	delete[] distance;
	queue_delete(queue);
	fout.close();
}