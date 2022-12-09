#include <iostream>
#include "graph.h"

using namespace std;

void print_graph_vertexes(Graph<int>* graph) {
	for (int i = 0; i < graph->size(); i++) {
		auto vertex = graph->get_vertex(i);
		cout << vertex->data << ' ';
	}

	cout << '\n';
}

void print_vertex_edges(Graph<int>::Vertex* vertex) {
	for (auto i = vertex->begin(); i.item != 0; ++i) {
		cout << i.item->data().vertex->data << ' ';
	}
	cout << '\n';
}

int main() {

	Graph<int>* graph = new Graph<int>(5,0);

	//graph initialization test
	if (graph->size() != 5) {
		cout << "Wrong graph size";
		return 1;
	}
	for (int i = 0; i < graph->size(); i++) {
		if (graph->get_vertex(i)->data != 0) {
			cout << "Wrong initial vertex data";
			return 1;
		}
	}
	print_graph_vertexes(graph);

	//graph change vertex data test
	for (int i = 0; i < graph->size(); i++) {
		graph->get_vertex(i)->data = i;
	}
	for (int i = 0; i < graph->size(); i++) {
		if (graph->get_vertex(i)->data != i) {
			cout << "Wrong vertex data";
			return 1;
		}
	}
	print_graph_vertexes(graph);

	//graph add new vertex test
	graph->add_vertex(6);
	if (!graph->get_vertex(5)) {
		cout << "Vertex was not added in graph";
		return 1;
	}
	if (graph->get_vertex(5)->data != 6) {
		cout << "Wrong vertex data";
		return 1;
	}
	print_graph_vertexes(graph);

	//graph remove vertex test
	graph->remove_vertex(5);
	if (graph->get_vertex(5)) {
		cout << "Vertex was not deleted";
		return 1;
	}
	print_graph_vertexes(graph);

	//graph add edge test
	auto from = graph->get_vertex(0);
	for (int i = 1; i < graph->size(); i++) {
		graph->add_edge(from, graph->get_vertex(i), i);
	}
	for (int i = 1; i < graph->size(); i++) {
		auto to = graph->get_vertex(i);
		if (!graph->is_edge_exists(from, to)) {
			cout << "Vertex 0 hasn't edge with vertex " << i;
			return 1;
		}
		if (graph->get_edge(from, to).weight != i) {
			cout << "Edge has wrong weight";
			return 1;
		}
	}
	print_vertex_edges(from);

	//graph iterator test
	const int expected_number_of_edges = 4;
	int number_of_edges = 0;
	for (auto i = from->begin(); i.item != 0; ++i) {
		number_of_edges++;
		auto to = i.item->data().vertex;
		if (!graph->is_edge_exists(from, to)) {
			cout << "The iterator refers to a nonexistent edge";
			return 1;
		}
	}

	if (expected_number_of_edges != number_of_edges) {
		cout << "Vertex iterator has wrong size";
		return 1;
	}

	//graph remove edge test
	auto to = graph->get_vertex(4);
	graph->remove_edge(from, to);
	for (auto i = from->begin(); i.item != 0; ++i) {
		if (i.item->data().vertex == to) {
			cout << "Edge was not deleted";
			return 1;
		}
	}

	delete graph;
}