#include "queue.h"
#include <iostream>
#include <string>
#include <fstream> 
#include <vector> 
using namespace std;

vector<string> Read(int& k, int& sx, int& sy, Queue* queue, int& fx, int& fy) {
	vector<string> labirynth;
	string strbuf;
	ifstream out("maze.txt");
	while (getline(out, strbuf))
	{
		labirynth.push_back(strbuf);
		for (size_t i = 0; i < labirynth[k].size(); i++)
		{
			if (labirynth[k][i] == 'X')
			{
				sx = static_cast<int>(k);
				sy = static_cast<int>(i);
				queue_insert(queue, sx);
				queue_insert(queue, sy);
			}
			if (labirynth[k][i] == 'Y')
			{
				fx = static_cast<int>(k);
				fy = static_cast<int>(i);
			}
		}
		k++;
	}
	out.close();
	return labirynth;
}
int** setter(int** rast, vector<string>& labirynth, int& sx, int& sy) {
	for (size_t i = 0; i < labirynth.size(); i++)
	{
		rast[i] = new int[labirynth[i].size()];
		for (size_t l = 0; l < labirynth[i].size(); l++)
		{
			rast[i][l] = 0;
		}
	}
	rast[sx][sy] = 1;
	return rast;
}
void Check(Queue* queue, vector<string>& labirynth, int* dx, int* dy, int** rast) {
	while (!queue_empty(queue))
	{
		int x = queue_get(queue);
		queue_remove(queue);
		int y = queue_get(queue);
		queue_remove(queue);
		for (int k_k = 0; k_k < 4; k_k++)
		{
			int xx = x + dx[k_k];
			int yy = y + dy[k_k];
			if (xx >= 0 && xx < static_cast<int>(labirynth.size()) && yy >= 0 && yy < static_cast<int>(labirynth[1].size()))
			{
				if (rast[xx][yy] == 0 && labirynth[xx][yy] != '#')
				{
					rast[xx][yy] = rast[x][y] + 1;
					queue_insert(queue, static_cast<int>(xx));
					queue_insert(queue, static_cast<int>(yy));
				}
			}
		}
	}
}
void PrintAndClear(int** rast, vector<string>& labirynth, int& sx, int& sy, int& fx, int& fy, int* dx, int* dy, int& k, Queue* queue) {
	if (rast[fx][fy])
	{
		while (rast[fx][fy] - 1 != rast[sx][sy])
		{
			for (int k_k = 0; k_k < 4; k_k++)
			{
				int x = fx + dx[k_k];
				int y = fy + dy[k_k];

				if (rast[fx][fy] - 1 == rast[x][y])
				{
					labirynth[x][y] = 'x';
					fx = x;
					fy = y;
				}
			}
		}
		for (size_t l = 0; l < labirynth.size(); l++)
			cout << labirynth[l] << endl;
	}
	else
		cout << "IMPOSSIBLE" << endl;

	for (int i = 0; i < k; i++)
		delete[] rast[i];

	delete[] rast;
	queue_delete(queue);
}

int main()
{
	Queue* queue = queue_create();
	int dy[4] = { 0, 0, 1,-1 };
	int dx[4] = { -1, 1, 0, 0 };
	int k = 0;
	int sx = 0, sy = 0;
	int fx = 0, fy = 0;
	vector<string> labirynth = Read(k,sx,sy,queue, fx, fy);
	int** rast = new int* [labirynth.size()];
	rast = setter(rast, labirynth, sx, sy);
	Check(queue, labirynth, dx, dy, rast);
	PrintAndClear(rast, labirynth, sx, sy, fx, fy, dx, dy, k, queue);
	return 0;
}