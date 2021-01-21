#include <iostream>
#include "queue.h"
using namespace std;

string grid[100];
const int num_path = -5, num_lattice = -4, num_dot = -3, num_end = -2, num_start = -1;

int main()
{
	int x_row = 0, x_col = 0;
	size_t col_count = 0, row_count = 0;

	string row;

	for (int i = 0; cin; i++)
	{
		cin >> row;

		col_count = row.length();
		grid[i] = row;

		for (int j = 0; j < row.length(); j++)
		{
			char symbol = grid[i][j];
			int symbolNum = 0;
			switch (symbol)
			{
			case '#':
				symbolNum = num_lattice;
				break;
			case '.':
				symbolNum = num_dot;
				break;
			case 'Y':
				symbolNum = num_end;
				break;
			case 'X':
				symbolNum = num_start;
				break;

			default: break;
			}
			grid[i][j] = symbolNum;

			if (symbol == 'X')
			{
				x_row = i, x_col = j;
			}
		}

		row_count++;
	}

	row_count--;

	Queue* queue_row = queue_create();
	Queue* queue_col = queue_create();
	Queue* queue_dist = queue_create();

	int curr_row = x_row, curr_col = x_col, curr_dist = 0;
	queue_insert(queue_row, curr_row);
	queue_insert(queue_col, curr_col);
	queue_insert(queue_dist, 0);

	Data cell = 0;
	while (cell != num_end && !queue_empty(queue_row))
	{
		curr_row = queue_get(queue_row);
		curr_col = queue_get(queue_col);
		curr_dist = queue_get(queue_dist);
		queue_remove(queue_row);
		queue_remove(queue_col);
		queue_remove(queue_dist);

		[&] {for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i * i + j * j != 0 && i * j == 0)
				{
					int row = curr_row + i;
					int col = curr_col + j;
					if (row < 0 || col < 0 || row >= row_count || col >= col_count)
					{
						continue;
					}

					cell = grid[row][col];
					if (cell == num_end)
					{
						grid[curr_row][curr_col] = curr_dist + 1;
						curr_row = row;
						curr_col = col;
						return;
					}

					else if (cell == num_dot)
					{
						queue_insert(queue_row, row);
						queue_insert(queue_col, col);
						queue_insert(queue_dist, curr_dist + 1);
						grid[curr_row][curr_col] = curr_dist + 1;
					}

				}
			}
		}}();
		
	}

	if (grid[curr_row][curr_col] != num_end)
	{
		cout << "Impossible";
	}
	else
	{
		int prev_number = INT_MAX;
		Data cell = 0;
		while (cell != 1)
		{
			[&] {for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i * i + j * j != 0 && i * j == 0)
					{
						int row = curr_row + i;
						int col = curr_col + j;

						if (row < 0 || col < 0 || row >= row_count || col >= col_count)
						{
							continue;
						}

						cell = grid[row][col];
						if (cell == 1)
						{
							curr_row = row;
							curr_col = col;
							i = 1, j = 1;
							return;
						}
						else if (cell > 0 && cell < prev_number)
						{
							grid[row][col] = num_path;
							prev_number = cell;
							curr_row = row;
							curr_col = col;
						}

					}
				}
			}}();
		}

		cout << endl;

		for (int i = 0; i < row_count; i++)
		{
			for (int j = 0; j < col_count; j++)
			{
				int cell = grid[i][j];
				if (i == x_row && j == x_col) cout << 'X';
				else if (cell == num_path) cout << 'x';
				else if (cell == num_lattice) cout << '#';
				else if (cell == num_end) cout << 'Y';
				else if (cell == num_start) cout << 'X';
			}
			cout << endl;
		}
	}
}
