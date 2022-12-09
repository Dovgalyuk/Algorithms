#include <iostream>
#include <math.h>
#include <limits.h>
#include "graph.h"

using namespace std;

void prims_algorithm(Graph<int>& graph) {
	
	int edges_count = graph.size() - 1;
	
	Graph<int>::Edge prims_tree[edges_count];

	for (int i = 0; i < edges_count; ++i) prims_tree[i] = { 0,INT_MAX };

	for (int i = 0; i < graph.size(); ++i) {
		
		auto vertex = graph.get_vertex(i);
		
		for (auto j = vertex->begin(); j.item != 0; ++j) {
			
			int vertex_dest = j.item->data().vertex->data;
			
			auto edge = &prims_tree[vertex_dest - 1];
			
			if (edge->weight <= j.item->data().weight) continue;

			edge->vertex = vertex;
			edge->weight = j.item->data().weight;
		}
	}

	for (int i = 0; i < edges_count; ++i) {
		printf(
			"%d -> %d : %d \n",
			prims_tree[i].vertex->data,
			i + 1,
			prims_tree[i].weight
		);
	}
}

int main() {
	
	int vertex_count; cin >> vertex_count;
	
	Graph<int> graph(vertex_count, 0);

	//Numbering the vertices
	for (int i = 0; i < graph.size(); ++i)
		graph.get_vertex(i)->data = i;

	int edges_count; cin >> edges_count;

	for (int i = 0; i < edges_count; ++i) {
		int from, to, weight;
		cin >> from >> to >> weight;
		auto ver1 = graph.get_vertex(from);
		auto ver2 = graph.get_vertex(to);
		graph.add_edge(ver1,ver2,weight);
	}

	prims_algorithm(graph);

}