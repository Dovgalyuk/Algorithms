//Попов Владимир 8091
#include <iostream>
#include "queue.h"

int main()
{
	int N, ** a, * from;
	bool* used;
	std::cin >> N;
	a = new int* [N];
	from = new int[N];
	for (int i = 0; i < N; i++)
		from[i] = 0;
	for (int i = 0; i < N; i++)
		a[i] = new int[N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			std::cin >> a[i][j];
	used = new bool[N];
	used[0] = true;
	for (int i = 1; i < N; i++)
		used[i] = false;
	Queue* q;
	q = queue_create();
	queue_insert(q, 0);
	while (!queue_empty(q))
	{
		int v = queue_get(q);
		queue_remove(q);
		for (int i = 0; i < N; i++)
		{
			if (a[v][i] == 1 && (!used[i]))
			{
				used[i] = true;
				from[i] = from[v] + 1;
				queue_insert(q, i);
			}
		}
	}
	for (int i = 0; i < N; i++) {
		std::cout << from[i];
	}
	std::cout << std::endl;
	queue_delete(q);
	delete[] used;
	delete[] from;
	for (int i = 0; i < N; i++)
		delete[] a[i];
	delete[] a;
}