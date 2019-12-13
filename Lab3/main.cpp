#include <iostream>
#include <list.h>
#include <graph.h>

#include <vector>
#include "defines.h"
using namespace std;


int main()
{
	size_t n;
	int start, a;
	std::vector <size_t> c;
	cin >> n;
	cin >> start;
	Graph* data = graph_create(n);

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++)
		{
			
			int a;
			cin >> a;
			
			if (a != -1) {
				graph_add_edge(data, i, j);
				graph_set_edge_mark(data, i, j, a);
			}
				
		}
		
	}

	graph_set_vertex_mark(data, start, 1);
	c.push_back(0);
	for (size_t i = 0; i < start; i++) {
		graph_set_vertex_mark(data, i, 1);
		c.push_back((size_t)-1);
	}
	for (size_t i = 1 + start; i < n; i++) {
		graph_set_vertex_mark(data, i, 1);
		c.push_back((size_t)-1);
	}
	
	while (start != -1)
	{
		for (Iterator it = graph_iterator_begin(data, start); it != graph_iterator_end(data, 0); ++it)
		{
			auto k = *it;
			
			if (c[k->tail] > c[start] + graph_get_edge_mark(data, start, k->tail)) {
				c[k->tail] = c[start] + graph_get_edge_mark(data, start, k->tail);
				graph_set_vertex_mark(data, k->tail, 0);
			}
		}
		graph_set_vertex_mark(data, start, -1);

		int min = -1;
		for (size_t j = 0; j < n; j++)
			if (graph_get_vertex_mark(data, j) == 0 && (min == -1 || c[j] < c[min]))
				min = j;
		start = min;
	}
	cout << "Distances to vertexs:" << endl;
	for (size_t j = 0; j < n; j++)
		cout << c[j] << " ";
}
