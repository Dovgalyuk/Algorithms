#include "queue.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

bool markPath(string &maze, int width, int start, int finish)
{
	const int size = static_cast<int>(maze.size());
	vector<int> parent(size, -1), origin(size, -1);
	Queue *queue = queue_create();

	for (int cell : {start, finish})
	{
		origin[cell] = parent[cell] = cell;
		queue_insert(queue, cell);
	}

	while (!queue_empty(queue))
	{
		int cell = queue_get(queue);
		queue_remove(queue);
		int col = cell % width;
		int neighbors[] = {
				cell >= width ? cell - width : -1,
				cell < size - width ? cell + width : -1,
				col > 0 ? cell - 1 : -1,
				col < width - 1 ? cell + 1 : -1};

		for (int next : neighbors)
		{
			if (next < 0 || maze[next] == '#')
				continue;

			if (origin[next] == -1)
			{
				origin[next] = origin[cell];
				parent[next] = cell;
				queue_insert(queue, next);
			}
			else if (origin[next] != origin[cell])
			{
				for (int end : {cell, next})
					for (int p = end; parent[p] != p; p = parent[p])
						if (maze[p] == '.')
							maze[p] = 'x';

				queue_delete(queue);
				return true;
			}
		}
	}

	queue_delete(queue);
	return false;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;

	ifstream input(argv[1]);
	string maze, row;
	size_t width = 0;
	while (input >> row)
	{
		if (width == 0)
			width = row.size();
		if (row.size() != width)
			return 1;
		maze += row;
	}

	auto start = maze.find('X'), finish = maze.find('Y');
	if (start == string::npos || finish == string::npos ||
			maze.size() > static_cast<size_t>(numeric_limits<int>::max()))
		return 1;

	if (!markPath(maze, static_cast<int>(width), static_cast<int>(start), static_cast<int>(finish)))
		cout << "IMPOSSIBLE\n";
	else
		for (size_t i = 0; i < maze.size(); i += width)
			cout << maze.substr(i, width) << '\n';
}
