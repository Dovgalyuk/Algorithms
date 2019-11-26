#include <iostream>
#include <graph.h>


int main()
{
	size_t v;
	std::cin >> v;
	Graph* graph = graph_create(v);
	size_t* marksC = new size_t[v];
	for (size_t i = 0; i < v; i++) {
		marksC[i] = 1;
		graph_set_vertex_mark(graph, i, i);
	}
	size_t e;
	std::cin >> e;
	for (size_t i = 0; i < e; i++)
	{
		size_t a, b, length;
		std::cin >> a >> b >> length;
		graph_add_edge(graph, a, b);
		graph_add_edge(graph, b, a);
		graph_set_edge_mark(graph, a, b, length);
		graph_set_edge_mark(graph, b, a, length);
	}

	size_t currA;
	do {
		size_t minA = -1, minB = -1, min = -1;
		currA = -1;
		for (size_t i = 0; i < v; i++)
		{
			for (size_t j = 0; j < v; j++)
			{
				if (graph_check_edge(graph, i, j) && graph_get_vertex_mark(graph, i) != graph_get_vertex_mark(graph, j))
				{
					if (graph_get_edge_mark(graph, i, j) < min)
					{
						minA = i;
						minB = j;
						min = graph_get_edge_mark(graph, i, j);
					}
				}
			}
		}
		if (minA != -1)
		{
			if (graph_get_vertex_mark(graph, minA) == minA && graph_get_vertex_mark(graph, minB) != minB)
			{
				std::swap(minA, minB);
			}
			int aMark = graph_get_vertex_mark(graph, minA);
			int bMark = graph_get_vertex_mark(graph, minB);
			for (size_t i = 0; i < v; i++)
			{
				if (graph_get_vertex_mark(graph, i) == bMark)
				{
					graph_set_vertex_mark(graph, i, aMark);
					marksC[aMark]++;
				}
			}
			currA = aMark;
		}


	} while (currA != -1 && marksC[currA] != v);
	std::cout << currA;
}
