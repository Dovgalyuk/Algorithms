#include <iostream>
#include <list.h>
#include <graph.h>
#include <graph_iterator.hpp>
#include <vector>
#include <algorithm>
#include "defines.h"

int main()
{
	//ѕрограмма считывает сначала колличество верши, затем количество св€зей, а затем дл€ каждой св€зи откуда она идЄт, куда и какой у неЄ вес(индексаци€ начинаетс€ с 0)
	size_t v;
	std::cin >> v;
	Graph* graph = graph_create(v);
	for (size_t i = 0; i < v; i++) {
		graph_set_vertex_mark(graph, i, i);
	}
	size_t e;
	std::cin >> e;
	for (size_t i = 0; i < e; i++)
	{
		size_t a, b, length;
		std::cin >> a >> b >> length;
		graph_add_edge(graph, a, b);
		graph_set_edge_mark(graph, a, b, length);
	}

	std::vector<Edge> edges;
	for (size_t i = 0; i < v; i++)
	{
		for (Graph_iterator it = graph_iterator_begin(graph, i); it != graph_iterator_end(graph, 0); ++it)
		{
			Edge edge;
			edge.head = (*it)->head;
			edge.tail = (*it)->tail;
			edge.mark = (*it)->tail;
			edges.push_back(edge);
		}
	}
	std::sort(edges.begin(), edges.end(), [](Edge a, Edge b) {return a.mark < b.mark; });
	size_t i = 0;
	std::vector<Edge> res;
	while (i < edges.size())
	{
		Edge currEdge = edges[i];
		size_t a = currEdge.head;
		size_t b = currEdge.tail;
		int aMark = graph_get_vertex_mark(graph, a);
		int bMark = graph_get_vertex_mark(graph, b);
		if (aMark != bMark)
		{
			Edge edge;
			edge.head = a;
			edge.tail = b;
			res.push_back(edge);

			for (size_t i = 0; i < v; i++)
			{
				if (graph_get_vertex_mark(graph, i) == bMark)
				{
					graph_set_vertex_mark(graph, i, aMark);
				}
			}
		}
		i++;
	}

	std::cout << std::endl;
	if (res.size() != v - 1)
	{
		std::cout << "Can't build tree";
	}
	else {
		for (size_t i = 0; i < res.size(); i++)
		{
			std::cout << res[i].head << " " << res[i].tail << std::endl;
		}
	}
	graph_delete(graph);
}
