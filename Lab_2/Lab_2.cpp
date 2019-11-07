#include <iostream>
#include "queue.h"
#include <fstream>

using namespace std;

int main()
{
	Queue* queue = queue_create();
	int a, b;
	ifstream fin("input.txt");

	if (!fin)
	{
		cout << "Unable to open file!/n";
		system("Pause");
		return 0;
	}

	fin >> a >> b;

	while (!fin.eof())
	{
		int temp;
		fin >> temp;
		if (temp < a)
		{
			cout << temp << " ";
		}
		else if (temp >= a && temp <= b)
		{
			if (!queue_empty(queue) && queue_get(queue) > b)
			{
				queue_insert(queue, temp);
			}
			else
			{
				if (!queue_empty(queue))
				{
					while (queue_get(queue) <= b) 
					{
						queue_insert(queue, queue_get(queue));
						queue_remove(queue);
					}
				}
				queue_insert(queue, temp);
			}
		}
		else 
		{
			if (!queue_empty(queue) && queue_get(queue) <= b)
			{
				queue_insert(queue, temp);
			}
			else
			{
				if (!queue_empty(queue))
				{
					while (queue_get(queue) > b)
					{
						queue_insert(queue, queue_get(queue));
						queue_remove(queue);
					}
				}
				queue_insert(queue, temp);
			}
		}
	}
	
	if (queue_get(queue) > b)
	{
		while (queue_get(queue) > b)
		{
			queue_insert(queue, queue_get(queue));
			queue_remove(queue);
		}
	}

	while (!queue_empty(queue))
	{
		cout << queue_get(queue) << " ";
		queue_remove(queue);
	}

	queue_delete(queue);
	fin.close();

	system("Pause");
	return 0;
}

