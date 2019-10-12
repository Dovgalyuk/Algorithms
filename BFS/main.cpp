#include "queue.h"
#include <iostream>

using namespace std;

int main()
{
	int size, start, end;
	cin >> size >> start >> end;
	start -= 1;
	end -= 1;
	int** mat = new int* [size];
	bool* used = new bool[size];
	int* dst = new int[size];
	for (int i = 0; i < size; i++)
	{
		mat[i] = new int[size];
		used[i] = false;
		dst[i] = -1;
	}
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			cin >> mat[i][j];
	Queue* q = queue_create();
	queue_insert(q, start);
	used[start] = true;
	dst[start] = 0;
	while (!queue_empty(q))
	{
		int curr = queue_get(q);
		queue_remove(q);
		for (int i=0; i< size; i++)
			if (!used[i] && mat[curr][i])
			{
				queue_insert(q, i);
				used[i] = true;
				dst[i] = dst[curr] + 1;
			}
	}
	if (dst[end] == -1)
		cout << "IMPOSSIBLE\n";
	else
		cout << dst[end] << '\n';
	
	for (int i = 0; i < size; i++)
		delete[] mat[i];
	delete[] mat;
	delete[] used;
	delete[] dst;
	queue_delete(q);
}