#include "queue.h"
#include <iostream>
#include <string>
#include <fstream> 
#include <vector> 
using namespace std;


int main()
{
	Queue* queue = queue_create(); // создаём очередь
	int dy[4] = { 0, 0, 1,-1 };   // нужно будет для проверки соседних клеток, всего 4 варианта, 
	int dx[4] = { -1, 1, 0, 0 }; // так как в лабиринте можно ходить только в окрестность фон Неймана
	int k = 0; //счетчик для изменения размера вектора
	int sx = 0, sy = 0; //координата старта
	int fx = 0, fy = 0; //координата финиша
	string strbuf; // строка для считывания из файла
	vector<string> labirynth; //вектор для хранения лабиринта
	ifstream out("vhod.txt");
	while (getline(out, strbuf))
	{
		labirynth.resize(k);
		labirynth.push_back(strbuf);
		for (int i = 0; i < labirynth[k].size(); i++)
		{
			if (labirynth[k][i] == 'X') // если нашли старт - записываем координаты и вносим их в очередь
			{
				sx = k;
				sy = i;
				queue_insert(queue, sx);
				queue_insert(queue, sy);
			}
			if (labirynth[k][i] == 'Y') // координаты финиша
			{
				fx = k;
				fy = i;
			}
		}
		k++;
	}
	out.close();
	int** rast = new int* [labirynth.size()]; //создаём двумерный массив расстояний и заполняем его нулями
	for (int i = 0; i < labirynth.size(); i++)
	{
		rast[i] = new int[labirynth[i].size()];
		for (int l = 0; l < labirynth[i].size(); l++)
		{
			rast[i][l] = 0;
		}
	}
	rast[sx][sy] = 1; // расстояние старта равняется одному. Это нужно для того, чтобы сразу отметить, что мы в нём были
	while (!queue_empty(queue))
	{
		int x = queue_get(queue);
		queue_remove(queue);
		int y = queue_get(queue);
		queue_remove(queue); //берём координаты
		for (int k = 0; k < 4; k++) // проверяем возможных соседей
		{
			int xx = x + dx[k];
			int yy = y + dy[k];
			if (xx >= 0 && xx < labirynth.size() && yy >= 0 && yy < labirynth[1].size()) //проверяем, существует ли такая точка
			{
				if (rast[xx][yy] == 0 && labirynth[xx][yy] != '#') // если мы в ней не были и она не стена
				{
					rast[xx][yy] = rast[x][y] + 1; //расстояние до точки это расстояние его предка + 1
					queue_insert(queue, xx);
					queue_insert(queue, yy);
				}

			}
		}
	}
	if (rast[fx][fy]) //если финиш достигнут
	{
		while (rast[fx][fy] - 1 != rast[sx][sy])
		{
			for (int k = 0; k < 4; k++) //возвращаемся от конца к началу
			{
				int x = fx + dx[k];
				int y = fy + dy[k];

				if (rast[fx][fy] - 1 == rast[x][y])
				{
					labirynth[x][y] = 'x'; // рисуем путь
					fx = x;
					fy = y;
				}
			}
		}
		for (int l = 0; l < labirynth.size(); l++) //выводим лабиринт с кратчайшим путём
		{
			cout << labirynth[l] << endl;
		}
	}
	else
	{
		cout << "IMPOSSIBLE";
	}
	for (int i = 0; i < k; i++)
	{
		delete[] rast[i];
	}
	delete[] rast;
	vector<string>().swap(labirynth);
	queue_delete(queue);
}
