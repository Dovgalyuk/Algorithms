#include <iostream>
#include <cctype>
#include "queue.h"
#include "vector.h"
#include <set>
#include <fstream>

using namespace std;

void poisk_v_shirinu(bool** matr, int n, int x, int y)
{
	Queue* queue = queue_create();
	Vector* dist = vector_create(); // расстояния до начальной вершины
	set <int> visited; // множество посещенных
	for (int i = 0; i < n; i++) // заполним нулями для дальнейшей проверки
	{
		vector_set(dist, i, 0);
	}
	queue_insert(queue, x - 1); // помещаем начальную вершину в очередь
	while (!queue_empty(queue)) // пока очередь не опустела
	{
		int kk = queue_get(queue); // берем из очереди крайний элемент
		queue_remove(queue); // удаляем его
		visited.insert(kk); // родитель посещен
		for (int i = 0; i < n; i++) // смотрим, с какими вершинами смежна kk
		{
			if ((matr[kk][i] == true) && (vector_get(dist, i) == 0) && (i != (x - 1))) // последнее условие - чтобы не трогать начальную вершину в массиве по ее индексу
			{
				queue_insert(queue, i);  //добавляем в очередь вершину i
				vector_set(dist, i, vector_get(dist, kk) + 1); // записываем расстояние до i 
			}
		}
	}
	ofstream fout("vivod.txt"); // файл будет создан в текущей директории 
	if (vector_get(dist, y - 1) == 0)
	{
		fout << "IMPOSSIBLE";
    }
	else 
	{
		fout << vector_get(dist, y - 1);
	}
	fout.close();
	vector_delete(dist);
	queue_delete(queue);
}

int main()
{
	setlocale(LC_ALL, "RU");
	ifstream fin("vvod.txt");  // мой файл лежит в текущей директории с программой
	if (!fin.is_open()) // если файл не открыт
	{
		cout << "Файл не может быть открыт!\n";
	}
	int n, x, y;
	int a, b;
	fin >> n;
	fin >> x;
	fin >> y;
	bool** matr = new bool* [n]; // матрица смежности
	for (int i = 0; i < n; i++)
	{
		matr[i] = new bool[n];
		for (int j = 0; j < n; j++)
		{
			matr[i][j] = false;
		}
	}
	while (!fin.eof())
	{
		fin >> a;
		fin >> b;
		matr[a - 1][b - 1] = true;
		matr[b - 1][a - 1] = true;
	}
	fin.close();
	poisk_v_shirinu(matr, n, x, y);
	for (int i = 0; i < n; i++)
	{ 
		delete[] matr[i];
	}
	delete[] matr;
}
