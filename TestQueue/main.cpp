//Попов Владимир 8091
//Алгоритм Флойда
#include <iostream>
#include "queue.h"
#include "Graphs.h"

int main()
{
	Graph* a;
	int num, v1, v2, mark;
	std::cin >> num;
	a = graph_create(num);
	std::cin >> v1 >> v2 >> mark; //v1 - первая вершина v2 - вторая вершина mark - вес ребра
	while (v1 != -1)
	{
		add_edge(a, v1, v2);
		add_mark_edge(a, v1, v2, mark); 
		std::cin >> v1 >> v2 >> mark;
	}
	/*
	for (int i = 1; i <= num; i++)
	{
		std::cout << '\n';
		for (int j = 1; j <= num; j++)
		{
			std::cout << read_mark_edge(a, i, j) << ' ';
		}
	}
	*/
	for (int i=1; i<=num; i++)
		for (int j = 1; j <= num; j++)
		{
			if (i == j)
			{
				add_mark_edge(a, i, j, 0);
			}
			else if (read_mark_edge(a, i, j)==0)
			{
				add_mark_edge(a, i, j, 9999);
			}
		}
	for (int k=1; k<=num; k++)
		for (int i=1; i<=num; i++)
			for (int j = 1; j <= num; j++)
			{
				if (read_mark_edge(a, i, j) > (read_mark_edge(a, i, k) + read_mark_edge(a, k, j)))
				{
					add_mark_edge(a, i, j, read_mark_edge(a, i, k)+ read_mark_edge(a, k, j));
				}
			}
	/*
	for (int i = 1; i <= num; i++)
	{
		std::cout << '\n';
		for (int j = 1; j <= num; j++)
		{
			std::cout << (int)check_edge(a, i, j) <<' ';
		}
	}
	*/
	for (int i = 1; i <=num; i++)
	{
		std::cout << '\n';
		for (int j = 1; j <=num; j++)
		{
			std::cout << read_mark_edge(a, i, j) << ' ';
		}
	}
	graph_delete(a);
	return 0;
}