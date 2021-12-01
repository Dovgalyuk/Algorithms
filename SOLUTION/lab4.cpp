#include<iostream>
#include "directed_graph.h" //Kosaraju

void SearchInDepth(int vertex, directed_graph* graph, int* time, bool** considered_vertex) //Search in depth with time
{
	(*considered_vertex)[vertex] = true;
	auto iter = new_iterator(graph);
	(*time)++;
	while (!iter->NeighborListEmpty(vertex))
	{
		int next = iter->NextNeighborIndex(vertex);
		if ((*considered_vertex)[next] == false)
			SearchInDepth(next, graph, &(*time), &(*considered_vertex));
	}
	(*time)++;
	set_vertex_label(graph, vertex, *time);

}

void SearchInDepth2(int vertex, directed_graph* graph, bool** considered_vertex) //Search in depth without time
{
	(*considered_vertex)[vertex] = true;
	auto iter = new_iterator(graph);
	while (!iter->NeighborListEmpty(vertex))
	{
		int next = iter->NextNeighborIndex(vertex);
		if ((*considered_vertex)[next] == false)
			SearchInDepth2(next, graph, &(*considered_vertex));
	}

}

int main()
{
	//---------------------- Graph enter ----------------------//
	int vertex_amount = 0;
	std::cout << "Enter the number of vertices of the graph:";
	std::cin >> vertex_amount;
	directed_graph* graph = create_directed_graph(vertex_amount);

	std::cout << "Enter adjacency matrix: \n";
	for (int i = 0; i < vertex_amount; i++)
	{
		for (int j = 0; j < vertex_amount; j++)
		{
			int number = 0;
			std::cin >> number;
			if (number == 1)
				add_edge(graph, i, j);
		}
	}
	//---------------------------------------------------------//

	//---Search in depth + count the time for the Kosaraju algorithm---//
	int time = -1;
	bool* considered_vertex = new bool[vertex_amount] {0};

	for (int i = 0; i < vertex_amount; i++)
	{
		if (considered_vertex[i] == 0)
		{
			SearchInDepth(i, graph, &time, &considered_vertex);
		}
	}
	//---------------------------------------------------------------//

	//-------------------inverting the edges-------------------//
	directed_graph* graph2 = create_directed_graph(vertex_amount);

	for (int i = 0; i < vertex_amount; i++)
	{
		for (int j = 0; j < vertex_amount; j++)
		{
			if (edge_exists(graph, i, j))
			{
				add_edge(graph2, j, i);
			}
		}
	}
	//---------------------------------------------------------//

	//--using *time* sort the vertex order in decreasing order--//
	int* vertex_order = new int[vertex_amount];
	for (int i = 0; i < vertex_amount; i++)
	{
		int maxIndex = 0;
		for (int j = 0; j < vertex_amount; j++)
		{
			if (get_vertex_label(graph, j) > get_vertex_label(graph, maxIndex))
				maxIndex = j;
		}
		vertex_order[i] = maxIndex;
		set_vertex_label(graph, maxIndex, 0);
	}
	delete_directed_graph(graph);
	//---------------------------------------------------------//

	for (int i = 0; i < vertex_amount; i++)
	{
		considered_vertex[i] = false;
	}

	//----------search in depth using vertex order-------------//
	int connectivity_component = 0;
	for (int i = 0; i < vertex_amount; i++)
	{
		if (considered_vertex[vertex_order[i]] == false)
		{
			SearchInDepth2(vertex_order[i], graph2, &considered_vertex);
			connectivity_component++;
		}
	}
	//---------------------------------------------------------//
	std::cout << connectivity_component;

	delete_directed_graph(graph2);
}