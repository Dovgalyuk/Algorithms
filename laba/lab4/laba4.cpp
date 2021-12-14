#include "graph.h"
#include <iostream>
#include <ctime>
#include <queue>

using namespace std;

void algoritm(int end, queue<int> que, Graph<int>* graph)
{
	int a = que.front();

	graph->getVershina(a)->data.length = 0;
	graph->getVershina(a)->data.status = 2;
	while (a!=end)
	{
		for (int i = 0; i < graph->getVershinaSum(); i++)
		{
			if (graph->containsRebroBetweenVershina(graph->getVershina(a),graph->getVershina(i)))
			{
				if (graph->getVershina(i)->data.status <= 1)
				{
					if (graph->getRebro(graph->getVershina(a), graph->getVershina(i))->data + graph->getVershina(a)->data.length < graph->getVershina(i)->data.length)
					{
						graph->getVershina(i)->data.length = graph->getRebro(graph->getVershina(a), graph->getVershina(i))->data + graph->getVershina(a)->data.length;
						graph->getVershina(i)->data.status = 1;
						que.push(i);
					}
				}

			}
		}
		que.pop();
		a = que.front();
	}
	cout << "наименьший путь до конца :=" << graph->getVershina(end)->data.length;
}

int main()
{
	setlocale(0,"");
	cout << "Сколько вершин будет в программе?" << endl;
	int num;
	cin >> num;

	auto* graph = new Graph<int>(num);

	for (int i = 0; i < graph->getVershinaSum(); i++)
	{
		graph->getVershina(i)->data.length = 1000;
	}

	cout << "Сколько будет рёбер?" << endl;

	cin >> num;

	int size, start, end;

	for (int i = 0; i < num; i++)
	{
		cout << "Передай длину ребра,из какой вершины выйдет ребро, и в какую вершину оно войдет" << endl;
		cout << "длина:=";
		cin >> size;
		cout << "от ";
		cin >> start;
		cout << " до ";
		cin >> end;
		graph->setRebro(graph->getVershina(start), graph->getVershina(end), size);
	}

	cout << "дай две точку, которые будут началом и концом(1вая - начало, 2ая - конец)" << endl;
	cin >> start >> end;

	queue<int> next_versh;
	next_versh.push(start);

	algoritm(end, next_versh, graph);
	return 0;
}