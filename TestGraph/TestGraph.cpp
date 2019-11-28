#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
	Graph* graph = graph_create(5);
	for (int i = 0; i < 5; i++)
	{
		graph_set_vertex_mark(graph, i, i);
	}
	for (int i = 0; i < 5; i++)
	{
		if (graph_get_vertex_mark(graph, i) != i)
		{
			cout << "Wrong mark on " << i << " vertex" << endl;
		}
	}
	graph_add_edge(graph, 1, 2);
	graph_add_edge(graph, 3, 4);
	if (!graph_check_edge(graph, 1, 2) || !graph_check_edge(graph, 3, 4))
	{
		cout << "Wrong edge checking result(no edges)" << endl;
	}
	graph_set_edge_mark(graph, 1, 2, 12);
	if (graph_get_edge_mark(graph, 1, 2) != 12)
	{
		cout << "Edge marks aren't adding properly" << endl;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (!((i == 1 && j == 2) || (i == 3 && j == 4)) && graph_check_edge(graph, i, j))
			{
				cout << "Wrong edge checking result(too many edges)" << endl;
			}
		}
	}
	graph_remove_vertex(graph, 0);
	for (int i = 0; i < 4; i++)
	{
		if (graph_get_vertex_mark(graph, i) != i + 1)
		{
			cout << "Wrong mark on " << i << " vertex after vertex removed" << endl;
		}
	}
	if (!graph_check_edge(graph, 2, 3) || !graph_check_edge(graph, 0, 1) || graph_get_edge_mark(graph, 0, 1) != 12)
	{
		cout << "Indexies aren't ajusted after vertex is removed" << endl;
	}
	graph_add_vertex(graph);
	graph_add_vertex(graph);
	graph_add_edge(graph, 4, 5);
	if (!graph_check_edge(graph, 4, 5))
	{
		cout << "Wrong edge checking result(no edges) after vertexes added" << endl;
	}
	graph_remove_vertex(graph, 3);
	if (graph_check_edge(graph, 1, 2) || !graph_check_edge(graph, 3, 4) || graph_get_edge_mark(graph, 0, 1) != 12)
	{
		cout << "Indexies aren't ajusted after vertex is removed" << endl;
	}
	graph_delete(graph);
	graph = graph_create(1);

	cout << "Memory leak test started" << endl;
	for (int i = 0; i < 10000; i++)
	{
		graph_add_vertex(graph);
		graph_set_vertex_mark(graph, i + 1, i);
		graph_add_edge(graph, i, i + 1);
		graph_set_edge_mark(graph, i, i + 1, i);
	}
	cout << "Memory leak test finished filling" << endl;
	for (int i = 0; i < 10001; i++)
	{
		graph_remove_vertex(graph, 0);
	}
	cout << "Memory leak test ended" << endl;

}

