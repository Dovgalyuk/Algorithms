#include<iostream>
#include "directed_graph.h"

int main()
{
	directed_graph* graph = create_directed_graph(3);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (edge_exists(graph, i, j) == true)
			{
				std::cout << "edge initialization error" << "\n";
				return 1;
			}
		}
	}

	add_edge(graph, 0, 1);
	if (edge_exists(graph, 0, 1) == false)
	{
		std::cout << "edge creating error" << "\n";
		return 1;
	}

	set_edge_label(graph, 0, 1, 11);

	if (get_edge_label(graph, 0, 1) != 11)
	{
		std::cout << "incorrect work with edge label" << "\n";
		return 1;
	}

	set_edge_label(graph, 0, 1, 10);

	if (get_edge_label(graph, 0, 1) != 10)
	{
		std::cout << "incorrect update of the edge label" << "\n";
		return 1;
	}

	set_vertex_label(graph, 0, 9);

	if (get_vertex_label(graph, 0) != 9)
	{
		std::cout << "incorrect work with vertex label" << "\n";
		return 1;
	}

	add_vertex(&graph);
	set_vertex_label(graph, 3, 8);

	if (get_edge_label(graph, 0, 1) != 10 or get_vertex_label(graph, 0) != 9)
	{
		std::cout << "incorrect addition of a vertex" << "\n";
		return 1;
	}

	remove_vertex(&graph, 0);
	if (get_vertex_label(graph, 0) == 9 or get_vertex_label(graph, 2) != 8)
	{
		std::cout << "incorrect removal of the vertex" << "\n";
		return 1;
	}

	remove_edge(graph, 0, 1);

	if (edge_exists(graph, 0, 1) != false)
	{
		std::cout << "incorrect removal of the edge" << "\n";
		return 1;
	}

	add_edge(graph, 1, 0);
	add_edge(graph, 1, 2);

	auto iter = new_iterator(graph);

	int i = 0;
	int arr[2] = { 0,2 };
	int neigbor_arr[2];
	while (!iter->NeighborListEmpty(1))
	{
		neigbor_arr[i] = iter->NextNeighborIndex(1);
		if (i < 2 and neigbor_arr[i] == arr[i])
			i++;
		else
		{
			std::cout << "incorrect iterator work" << "\n";
			return 1;
		}
	}

	delete_directed_graph(graph);
