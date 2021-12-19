#include <iostream>
#include <fstream>
#include "queue.h"



int main()
{
	std::ifstream fin;
	fin.open("first.txt");

	int n = 0;
	//read n
	char ch;
	bool enter = true;
	while (fin.get(ch)) {
		if (ch == '\n') break;
		n = ch - '0';
	}
	//pointer to start
	fin.seekg(0, fin.beg);
	int* arr = new int[n * n];
	//filling the array
	if (fin.is_open()) {
		enter = true;
		int i = 0;
		while (fin.get(ch)) {
			int i_ch = ch - '0';
			if (!enter) {
				if (ch != ' ' && ch != '\n') {
					arr[i] = i_ch;
					i++;
				}
			}
			if (ch == '\n') enter = false;
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
				distance[j] += distance[line] + 1;
				was_in_queue[j] = true;
			}
		}
	}

	std::ofstream fout;
	fout.open("second.txt");

	fout << arr[0] << "\n";
	//output of results
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