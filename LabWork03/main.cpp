#include <iostream>
#include <vector>
#include <algorithm>
#include "graph.h"

using namespace std;

struct Edge {
	size_t head;
	size_t tail;
	size_t eweight;
};

int main()
{
	size_t graphSize = 0;
	size_t weight = 0;
	size_t fv, sv;
	size_t sc = 0;
	size_t sumWeight = 0;
	cout << "Enter the number of vertices of the graph: ";
	cin >> graphSize;
	cout << "Enter first vertex, second vertex and their weight. " << endl;
	Graph* graph = graph_create(graphSize);
	vector <Edge> edges;
	vector <Edge> res;

	for (size_t i = 0; i < graphSize; i++)
	{
		graph_setVertexWeight(graph, i, i);
	}

	while (cin >> fv)
	{
		cin >> sv >> weight;
		Edge edge;
		edge.head = fv;
		edge.tail = sv;
		edge.eweight = weight;
		edges.push_back(edge);
		graph_addEdge(graph, fv, sv);
		graph_setEdgeWeight(graph, fv, sv, weight);
	}

	sort(edges.begin(), edges.end(), [](Edge first, Edge second) { return first.eweight < second.eweight; });

	for (size_t i = 0; i < edges.size(); i++)
	{
		int first = edges[i].head; 
		int second = edges[i].tail;
		int firstWeight = graph_getVertexWeight(graph, first);
		int secondWeight = graph_getVertexWeight(graph, second);
		if (firstWeight != secondWeight)
		{
			res.push_back(edges[i]);

			for (size_t j = 0; j < graphSize; j++)
			{
				if (graph_getVertexWeight(graph, j) == secondWeight)
				{
					graph_setVertexWeight(graph, j, firstWeight);
				}
			}
		}
	}
	
	if (res.size() != graphSize - 1)
	{
		cout << "Can't build tree." << endl;
	}
	else
	{
		for (size_t i = 0; i < res.size(); i++)
		{
			cout << res[i].head << " " << res[i].tail << " " << res[i].eweight << endl;
			sumWeight += res[i].eweight;
		}
		cout << "Covering tree weight = " << sumWeight << endl;
	}

	return 0;
}