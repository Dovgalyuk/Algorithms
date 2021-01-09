#include <iostream>
#include "queue.h"
using namespace std;

void searchAlgorithm(int rowSize, int colSize, int row, int col, char** maze, int** visitedCell, int** path, Queue*& map)
{
	if (!visitedCell[row][col])
	{
		if ((row + 1) < rowSize && (row + 1) >= 0 && !visitedCell[row + 1][col] && (maze[row + 1][col] == '.' || maze[row + 1][col] == 'X'))
		{
			path[row + 1][col] = path[row][col] + 1;
			queue_insert(map, row + 1);
			queue_insert(map, col);
		}
		if ((row - 1) < rowSize && (row - 1) >= 0 && !visitedCell[row - 1][col] && (maze[row - 1][col] == '.' || maze[row - 1][col] == 'X'))
		{
			path[row - 1][col] = path[row][col] + 1;
			queue_insert(map, row - 1);
			queue_insert(map, col);
		}
		if ((col + 1) < colSize && (col + 1) >= 0 && !visitedCell[row][col + 1] && (maze[row][col + 1] == '.' || maze[row][col + 1] == 'X'))
		{
			path[row][col + 1] = path[row][col] + 1;
			queue_insert(map, row);
			queue_insert(map, col + 1);
		}
		if ((col - 1) < colSize && (col - 1) >= 0 && !visitedCell[row][col - 1] && (maze[row][col - 1] == '.' || maze[row][col - 1] == 'X'))
		{
			path[row][col - 1] = path[row][col] + 1;
			queue_insert(map, row);
			queue_insert(map, col - 1);
		}
		visitedCell[row][col] = 1;
	}
}

int main()
{
	int row, col, beginX, beginY, endX, endY, x, y;
	Queue* map = queue_create();

	cout << "Numbers of rows: ";
	cin >> row;
	cout << "Numbers of columns: ";
	cin >> col;
	cout << endl;

	int size = (row >= col) ? row : col;

	char** maze = new char* [size];
	int** visitedCell = new int* [size];
	int** path = new int* [size];

	for (int i = 0; i < row; i++)
	{
		maze[i] = new char[size];
		visitedCell[i] = new int[size];
		path[i] = new int[size];

		for (int j = 0; j < col; j++)
		{
			visitedCell[i][j] = 0;
			path[i][j] = -1;
			cin >> maze[i][j];
			if (maze[i][j] == 'Y')
			{
				beginX = i;
				beginY = j;
				queue_insert(map, i);
				queue_insert(map, j);
				path[i][j] = 1;
			}
			else if (maze[i][j] == 'X')
			{
				endX = i;
				endY = j;
			}
		}
	}
	while (!queue_empty(map))
	{
		x = queue_get(map);
		queue_remove(map);

		y = queue_get(map);
		queue_remove(map);

		searchAlgorithm(row, col, x, y, maze, visitedCell, path, map);
	}

	queue_delete(map);

	cout << endl;

	if (!visitedCell[endX][endY])
	{
		cout << "IMPOSSIBLE" << endl;
	}
	else
	{
		x = endX;
		y = endY;

		while (path[x][y] != 2)
		{
			if ((x - 1) >= 0  && (path[x - 1][y] == path[x][y] - 1))
			{
				x = x - 1;
				maze[x][y] = 'x';
			}
			else if ((x + 1) >= 0 && (x + 1) < row && (path[x + 1][y] == path[x][y] - 1))
			{
				x = x + 1;
				maze[x][y] = 'x';
			}
			else if ((y - 1) >= 0  && (path[x][y - 1] == path[x][y] - 1))
			{
				y = y - 1;
				maze[x][y] = 'x';
			}
			else if ((y + 1) >= 0 && (y + 1) < col && (path[x][y + 1] == path[x][y] - 1))
			{
				y = y + 1;
				maze[x][y] = 'x';
			}
		}
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cout << maze[i][j];
			}
			cout << endl;
		}
	}

	system("pause");
	return 0;
}