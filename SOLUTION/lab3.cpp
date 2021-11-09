#include <iostream>
#include "queue.h"

int main()
{
	int n = 0;
	std::cin >> n;
	int* arr = new int[n * n];
	for (int i = 0; i < n * n; i++)
	{
		std::cin >> arr[i];
	}

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
	std::cout << arr[0] << "\n";
	for (int i = 1; i < n; i++)
	{
		if (was_in_queue[i] == false) std::cout << "none" << "\n";
		else std::cout << distance[i] << "\n";
	}
	delete[] was_in_queue;
	delete[] distance;
	queue_delete(queue);

}
