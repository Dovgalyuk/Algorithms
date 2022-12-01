#include "queue.h"
#include "list.h"
#include <iostream>
#include <string>
#include <fstream> 
#include <vector> 


using namespace std;
int main()
{
	Queue* queue = queue_create();
	int dy[4] = { 0, 0, 1,  -1 };
	int dx[4] = { -1, 1, 0, 0 };
	int n, m;
	int k = 0;
	int sx, sy;
	int fx, fy;
	string strbuf;
	vector<string> labirynth;
	ifstream out("vhod.txt");
	while (getline(out, strbuf))
	{
		labirynth.resize(k);
		labirynth.push_back(strbuf);
		for (int i = 0; i < labirynth[k].size(); i++)
		{
			if (labirynth[k][i] == 'X')
			{
				sx = k;
				sy = i;
				queue_insert(queue, sx);
				queue_insert(queue, sy);
			}
			if (labirynth[k][i] == 'Y')
			{
				fx = k;
				fy = i;
			}
		}
		k++;
	}
	int** rast = new int* [labirynth.size()];
	for (int i = 0; i < labirynth.size(); i++)
	{
		rast[i] = new int[labirynth[i].size()];
		for (int l = 0; l < labirynth[i].size(); l++)
		{
			rast[i][l] = 0;
		}
	}
	rast[sx][sy] = 1;
	while (!queue_empty(queue))
	{
		int x = queue_get(queue);
		queue_remove(queue);
		int y = queue_get(queue);
		queue_remove(queue);
		for (int k = 0; k < 4; k++)
		{
			int xx = x + dx[k];
			int yy = y + dy[k];	
			if (xx >= 0 && xx < labirynth.size() && yy >= 0 && yy < labirynth[1].size())
			{
				if (rast[xx][yy] == 0 && labirynth[xx][yy] != '#')
				{
					labirynth[xx][yy] = 'x';
					rast[xx][yy] = rast[x][y] + 1;
					queue_insert(queue, xx);
					queue_insert(queue, yy);
				}

			}
		}
	}
	for (int i = 0; i < labirynth.size(); i++)
	{
		for (int l = 0; l < labirynth[i].size(); l++)
		{
			if (i == fx && l == fy)
			{
				cout << 'Y';
			}
			else
			{
				cout << labirynth[i][l];
			}
		}
		cout << endl;
	}
	queue_delete(queue);
}

