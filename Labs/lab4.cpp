#include <iostream>
#include <math.h>
#include <limits.h>
#include "graph.h"

using namespace std;

void print_prims_tree(Graph<int>& graph) {
	
	for (int i = 0; i < graph.size(); ++i) {
		
		auto from = graph.get_vertex(i);

		for (auto k = from->begin(); k.item != 0; ++k) {
			
			auto edge = k.item->data();

			auto to = k.item->data().vertex;

			printf(
				"%d -> %d : %d \n",
				from->data,
				to->data,
				edge.weight
			);

		}
	}
}

Graph<int> prims_algorithm(Graph<int>& graph) {

	int edges_count = graph.size() - 1;

	Graph<int> prim_tree(1,0);
	
	bool visited[graph.size()]{ false };
	visited[0] = true;

	for (int i = 0; i < edges_count; ++i) {
		
		//Start position of nearest vertex 
		int from = 0;	

		//End position of nearest vertex
		int to = 0;

		int min_weight = INT_MAX;

		for (int j = 0; j < prim_tree.size(); ++j) {
			
			int pos = prim_tree.get_vertex(j)->data;

			auto vertex = graph.get_vertex(pos);

			for (auto k = vertex->begin(); k.item != 0; ++k) {
				
				auto edge = k.item->data();

				if (edge.weight > min_weight) continue;
				
				if (visited[edge.vertex->data]) continue;

				from = pos;
				to = edge.vertex->data;
				min_weight = edge.weight;

			}
		}

		auto vertex = prim_tree.find_vertex(to);

		if (!vertex) prim_tree.add_vertex(to);

		auto from_vec = prim_tree.find_vertex(from);
		auto to_vec = prim_tree.find_vertex(to);

		prim_tree.add_edge(from_vec,to_vec,min_weight);

		visited[to] = true;

	}

	return prim_tree;
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

	auto prim_tree = prims_algorithm(graph);

	print_prims_tree(prim_tree);

}