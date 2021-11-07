#include <iostream>
#include "queue.h"

int main()
{
	int n = 0;
	std::cin >> n;
	int *arr = new int[n * n];
	for (int i = 0; i < n * n; i++)
	{
		std::cin >> arr[i];
	}

	Queue* queue = queue_create();
	bool* was_in_queue = new bool[n]();
	int* main_ancestor = new int[n]();
	main_ancestor[0] = -1;
	queue_insert(queue, 0);
	was_in_queue[0] = 1;
	while (!queue_empty(queue))
	{
		int line = queue_get(queue);
		queue_remove(queue);
		for (int j = 0; j < n; j++)
		{
			if (arr[(line * n) + j] == 1 && was_in_queue[j] == 0)
			{
				queue_insert(queue, j);
				main_ancestor[j] = line;
				was_in_queue[j] = 1;
			}
		}
	}
	std::cout << arr[0] << "\n";
	for (int i = 1; i < n; i++)
	{
		if (was_in_queue[i] == 0) std::cout << "none" << "\n";
		else {
			int way = 0, j = i;
			while (main_ancestor[j] != -1)
			{
				j = main_ancestor[j];
				way++;
			}
			std::cout << way << "\n";
		}
	}
	delete[] was_in_queue;
	delete queue;

}
