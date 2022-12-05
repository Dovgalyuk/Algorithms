#include <iostream>
#include <algorithm>
#include <math.h>
#include "graph.h"

using namespace std;

void prims_algorithm(Graph<int>& graph) {
	
	int edges_count = graph.size() - 1;
	
	bool visited[graph.size()]{ false };
	visited[0] = true;

	for (int i = 0; i < edges_count; ++i) {
		
		int min_weight = INFINITY;
		int from, to;
		
		for (int j = 0; j < graph.size(); ++j) {
			
			if (!visited[j]) continue;

			auto vertex = graph.get_vertex(j);

			for (auto k = vertex->begin(); k.item != 0; ++k) {
				
				auto edge = k.item->data();

				if (edge.weight > min_weight) continue;

				if (visited[edge.vertex->data]) continue;

				min_weight = edge.weight;
				
				from = vertex->data;
				to = edge.vertex->data;

			}
		}

		visited[to] = true;

		cout << from << "->" << to << " : " << min_weight << endl;

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