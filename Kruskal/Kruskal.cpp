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
		graph_set_edge_mark(graph, a, b, length);
	}
	List* sortedEdges = list_create();
	for (size_t i = 0; i < v; i++)
	{
		for (size_t j = 0; j < v; j++)
		{
			if (graph_check_edge(graph, i, j))
			{
				size_t len = graph_get_edge_mark(graph, i, j);
				Edge* edge = new Edge();
				edge->head = i;
				edge->tail = j;
				edge->mark = len;

				ListItem* currEdgeItem = list_first(sortedEdges);
				Edge* currEdge = list_item_data(currEdgeItem);
				if (currEdge == NULL || len < currEdge->mark)
				{
					list_insert(sortedEdges, edge);
				}
				else {
					while (currEdgeItem != NULL)
					{
						if (currEdge->mark > len)
						{
							list_insert_after(sortedEdges, list_item_prev(currEdgeItem), edge);
						}
						currEdgeItem = list_item_next(currEdgeItem);
					}
				}
			}
		}
	}
	size_t currA;
	do {
		size_t minA = -1, minB = -1, min = -1;
		currA = -1;

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
