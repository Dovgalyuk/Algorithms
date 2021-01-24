#include <iostream>
#include "queue.h"
using namespace std;

unsigned board[100][100];

int main()
{
	cout << "Enter N M: " << endl;
	int N, M;
	cin >> N >> M;
	Queue* x_queue = queue_create();
	Queue* y_queue = queue_create();
	cout << "Enter start spots: (0 0 to stop): " << endl;
	while (true)
	{
		int x, y;
		cin >> x >> y;
		if (x == 0) break;
		queue_insert(x_queue, x - 1);
		queue_insert(y_queue, y - 1);

		board[x - 1][y - 1] = 1;
	}
	
	unsigned k = 0;
	while (!queue_empty(x_queue))
	{
		int x_start = queue_get(x_queue);
		int y_start = queue_get(y_queue);
		unsigned intensity = board[x_start][y_start];

		queue_remove(x_queue);
		queue_remove(y_queue);
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i * i + j * j != 0 && i * j == 0)
				{
					int x = x_start + i;
					int y = y_start + j;
					if (x < 0 || y < 0 || x >= N || y >= M)
					{
						continue;
					}
					if (board[x][y] == 0)
					{
						k = intensity + 1;
						board[x][y] = k;
						//cout << "(" << x << ", " << y << "): " << k << endl;
						queue_insert(x_queue, x);
						queue_insert(y_queue, y);
					}
				}

			}
		}
	}
	cout << k;
}