#include "queue.h"
#include <iostream>
#include <string>
#include <fstream> 
#include <vector> 
using namespace std;

vector<string> Read(int& sx, int& sy, Queue* queue, int& fx, int& fy) {
	vector<string> labirynth;
	string strbuf;
	ifstream out("maze.txt");
	int k = 0;
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
//выделяет память и инициализирует двумерный массив rast, представляющий карту расстояний в лабиринте. Этот массив будет использоваться для хранения расстояний от начальной позиции до каждой ячейки в лабиринте.
int** setter(vector<string>& labirynth, int sx, int sy) {
	int** rast = new int* [labirynth.size()];
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
//выполняет алгоритм поиска в ширину (BFS) для определения кратчайших расстояний от начальной позиции (X) до всех других доступных ячеек в лабиринте.
void Check(Queue* queue, vector<string>& labirynth, const int* dx, const int* dy, int** rast) {
	while (!queue_empty(queue))
	{
		//получаем текущий x y из очереди
		int x = queue_get(queue);
		queue_remove(queue);
		int y = queue_get(queue);
		queue_remove(queue);
		//Проходим по всем направлениям (вверх, вниз, вправо, влево)
		for (int k_k = 0; k_k < 4; k_k++)
		{
			int xx = x + dx[k_k];
			int yy = y + dy[k_k];
			//Проверяется, что новые координаты находятся в пределах лабиринта.
			if (xx >= 0 && xx < static_cast<int>(labirynth.size()) && yy >= 0 && yy < static_cast<int>(labirynth[1].size()))
			{
				if (rast[xx][yy] == 0 && labirynth[xx][yy] != '#')
				{
					//Устанавливается новое расстояние от начальной позиции до текущей ячейки
					rast[xx][yy] = rast[x][y] + 1;
					//вставляем новые координаты в очередь
					queue_insert(queue, static_cast<int>(xx));
					queue_insert(queue, static_cast<int>(yy));
				}
			}
		}
	}
}
//печать кротчайшего пути
void PrintAndClear(int** rast, vector<string> labirynth, int fx, int fy, const int* dx, const int* dy, Queue* queue) {
	if (rast[fx][fy]) //существует ли путь от начала до конца
	{
		while (rast[fx][fy] - 1 != 1) // пока не достигли начальной точки
		{
			//Проходим по всем направлениям (вверх, вниз, вправо, влево)
			for (int k_k = 0; k_k < 4; k_k++)
			{
				int x = fx + dx[k_k];
				int y = fy + dy[k_k];

				//Если найдена ячейка на предыдущем шаге (расстояние от текущей позиции на 1 меньше), она помечается символом 'x', и текущая позиция обновляется на эту ячейку
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

	for (size_t i = 0; i < labirynth.size(); i++)
		delete[] rast[i];

	delete[] rast;
	queue_delete(queue);
}

int main()
{
	Queue* queue = queue_create();
	//смещения по оси y для движения вверх, вниз, вправо и влево.
	static const int dy[4] = { 0, 0, 1,-1 };
	//смещения по оси x для движения вверх, вниз, вправо и влево.
	static const int dx[4] = { -1, 1, 0, 0 };
	//начальные и конечные координаты x и y
	int sx = 0, sy = 0;
	int fx = 0, fy = 0;
	vector<string> labirynth = Read(sx, sy, queue, fx, fy);
	int** rast = setter(labirynth, sx, sy);
	Check(queue, labirynth, dx, dy, rast);
	PrintAndClear(rast, labirynth,fx, fy, dx, dy, queue);
	return 0;
}