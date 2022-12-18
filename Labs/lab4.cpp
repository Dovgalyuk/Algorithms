#include <iostream>
#include <math.h>
#include <limits.h>
#include "graph.h"

using namespace std;

void prims_algorithm(Graph<int>& graph) {

	int edges_count = graph.size() - 1;

	Graph<int>::Edge prims_tree[graph.size()];

	for (int i = 0; i < graph.size(); ++i) prims_tree[i] = { 0,INT_MAX };
	
	bool visited[graph.size()]{ false };
	visited[0] = true;

	int near_ver_pos = 0;

	for (int i = 0; i < edges_count; ++i) {

		auto vertex = graph.get_vertex(near_ver_pos);

		for (auto k = vertex->begin(); k.item != 0; ++k) {

			auto edge = k.item->data();

			if (edge.weight < prims_tree[edge.vertex->data].weight) {
				prims_tree[edge.vertex->data].weight = edge.weight;
				prims_tree[edge.vertex->data].vertex = vertex;
			}

		}

		int min_weight = INT_MAX;

		for (int j = 0; j < graph.size(); ++j) {
			if (!visited[j] && prims_tree[j].weight < min_weight) {
				min_weight = prims_tree[j].weight;
				near_ver_pos = j;
			}
		}

		visited[near_ver_pos] = true;
	}

	for (int i = 0; i < graph.size(); ++i) {
		auto edge = prims_tree[i];
		if (edge.vertex == 0) continue;
		printf(
			"%d -> %d : %d \n",
			edge.vertex->data,
			i,
			edge.weight
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