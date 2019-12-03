#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include "queue.h"

using namespace std;

int main()
{
	ifstream in("data.txt");
	if (!in.is_open())
	{
		cout << "File not found" << endl;
		return 1;
	}
	string input;
	vector<vector<int>> mat;
	int sx = -1, sy = -1, ex = -1, ey = -1;
	while (!in.eof())
	{
		getline(in, input);
		mat.push_back(vector<int>());
		for (size_t i = 0; i < input.length(); i++)
		{
			if (input[i] == 'X')
			{
				sx = mat.size() - 1;
				sy = i;
			}
			if (input[i] == 'Y')
			{
				ex = mat.size() - 1;
				ey = i;
			}
			mat[mat.size() - 1].push_back(input[i] == '#' ? -1 : 1e8);
		}
	}
	if (sx == -1 || ex == -1)
	{
		cout << "Invalid data. No start or end" << endl;
		return 0;
	}
	Queue* q = queue_create();
	queue_insert(q, make_pair(sx, sy));
	mat[sx][sy] = 0;
	while (!queue_empty(q))
	{
		auto curr = queue_get(q);
		queue_remove(q);
		if (curr.first + 1 < mat.size() && mat[curr.first + 1][curr.second] != -1 && mat[curr.first][curr.second] + 1 < mat[curr.first + 1][curr.second])
		{
			queue_insert(q, make_pair(curr.first + 1, curr.second));
			mat[curr.first + 1][curr.second] = mat[curr.first][curr.second] + 1;
		}
		if (curr.first - 1 >= 0 && mat[curr.first - 1][curr.second] != -1 && mat[curr.first][curr.second] + 1 < mat[curr.first - 1][curr.second])
		{
			queue_insert(q, make_pair(curr.first - 1, curr.second));
			mat[curr.first - 1][curr.second] = mat[curr.first][curr.second] + 1;
		}
		if (curr.second + 1 < mat[curr.first].size() && mat[curr.first][curr.second + 1] != -1 && mat[curr.first][curr.second] + 1 < mat[curr.first][curr.second + 1])
		{
			queue_insert(q, make_pair(curr.first, curr.second + 1));
			mat[curr.first][curr.second + 1] = mat[curr.first][curr.second] + 1;
		}
		if (curr.second - 1 >= 0 && mat[curr.first][curr.second - 1] != -1 && mat[curr.first][curr.second] + 1 < mat[curr.first][curr.second - 1])
		{
			queue_insert(q, make_pair(curr.first, curr.second - 1));
			mat[curr.first][curr.second - 1] = mat[curr.first][curr.second] + 1;
		}
	}
	queue_delete(q);
	if (mat[ex][ey] == 1e8)
	{
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	int x = ex;
	int y = ey;
	while (x != sx || y != sy)
	{
		if (x - 1 >= 0 && mat[x - 1][y] == mat[x][y] - 1)
			mat[x--][y] = 'x';
		else
			if (x + 1 < mat.size() && mat[x + 1][y] == mat[x][y] - 1)
				mat[x++][y] = 'x';
			else
				if (y - 1 >= 0 && mat[x][y - 1] == mat[x][y] - 1)
					mat[x][y--] = 'x';
				else
					if (y + 1 < mat[x].size() && mat[x][y + 1] == mat[x][y] - 1)
						mat[x][y++] = 'x';
	}
	mat[sx][sy] = 'X';
	mat[ex][ey] = 'Y';
	for (size_t i = 0; i < mat.size(); i++)
	{
		for (size_t j = 0; j < mat[i].size(); j++)
			cout << ((mat[i][j] == 'x' || mat[i][j] == 'X' || mat[i][j] == 'Y') ? ((char)mat[i][j]) : (mat[i][j] == -1 ? '#' : '.'));
		cout << endl;
	}
}