#include "graph.h"
#include "vector.h"

#include <iostream>

typedef Graph<int, int> MyGraph;

int main() {
	MyGraph graph(Graph<int, int>::Graph_Type::Directed, 5);

	// ---------- Test 1 - get vertices labels ---------- //

	Vector<int> vertices = graph.get_vertices_labels();

	if (vertices.size() != 5) {
		std::cout << "Invalid vertices count\n";
		return 1;
	}

	// ---------- Test 2 - add vertices ---------- //

	graph.add_vertex(0);
	graph.add_vertex(1);
	graph.add_vertex(2);
	graph.add_vertex(3);
	graph.add_vertex(4);

	Vector<int> vertices_2 = graph.get_vertices_labels();

	if (vertices_2.size() != 10) {
		std::cout << "Invalid vertices count\n";
		return 1;
	}

	// ---------- Test 3 - add edges ---------- //

	graph.add_edge(0, 1, 5);
	graph.add_edge(0, 2, 10);
	graph.add_edge(0, 3, 100);

	if (!graph.has_edge(0, 1)) {
		std::cout << "Graph does not have an edge 0 --> 1\n";
		return 1;
	}

	if (!graph.has_edge(0, 2)) {
		std::cout << "Graph does not have an edge 0 --> 2\n";		
		return 1;
	}

	if (!graph.has_edge(0, 3)) {
		std::cout << "Graph does not have an edge 0 --> 3\n";		
		return 1;
	}

	// ---------- Test 4 - get neighbors ---------- //

	int expected = 1;
	for (auto current = graph.neighbors_begin(0); current != graph.neighbors_end(0); ++current) {
		if (*current != expected) {
			std::cout << "Invalid neighbor: " << *current << ", expected: " << expected << "\n";
			return 1;
		}

		expected++;
	}
	
	// ---------- Test 5 - remove vertex ---------- //
	
	graph.remove_vertex(4);

	Vector<int> vertices_3 = graph.get_vertices_labels();

	if (vertices_3.size() != 9) {
		std::cout << "Invalid vertices count after removing vertex\n";
		return 1;
	}

	// ---------- Test 6 - remove edge ---------- //

	graph.remove_edge(0, 1);

	if (graph.has_edge(0, 1)) {
		std::cout << "Invalid edge removal (0 --> 1)\n";
		return 1;
	}

	// ---------- Test 7 - set and get vertex label ---------- //

	graph.set_vertex_label(0, 10);

	if (graph.get_vertex_label(0) != 10) {
		std::cout << "Invalid vertex label after set\n";
		return 1;
	}

	// ---------- Test 8 - set and get edge label ---------- //

	graph.set_edge_label(0, 2, 100);

	if (graph.get_edge_label(0, 2) != 100) {
		std::cout << "Invalid edge label after set\n";
		return 1;
	}

	// ---------- Test 9 - print vertices ---------- //

	cout << "Vertices: \n";
	for (size_t i = 0; i < vertices_3.size(); i++) {
		cout << vertices_3.get(i) << " ";
	}

	return 0;
}