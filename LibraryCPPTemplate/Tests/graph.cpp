#include "graph.h"
#include "vector.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <limits> 

int main() {
	Graph<std::string, std::string>::GraphType type = Graph<std::string, std::string>::GraphType::Directed;
	///////////Checking the number of vertices///////////////////////
	Graph<std::string, std::string> graph(type);
	graph.add_Vertex("A");
	graph.add_Vertex("B");
	graph.add_Vertex("C");
	graph.add_Vertex("D");
	graph.add_Vertex("E");
	if (graph.get_VertexAmount() != 5) {
		std::cout << "Invalid  vertex amount\n" << std::endl;
		return 1;
	}
	else {
		std::cout << "correct number of vertices\n" << std::endl;
	}
	///////////////iterator test and add edge//////////////////////////////////
	graph.add_Edge(0, 1, "m");
	graph.add_Edge(1, 2, "f");
	graph.add_Edge(2, 3, "s");
	graph.add_Edge(1, 3, "o");
	graph.add_Edge(3, 0, "t");
	graph.add_Edge(3, 4, "e");

	for (size_t vertex = 0; vertex < graph.get_VertexAmount(); ++vertex) {
		Graph<std::string, std::string>::Iterator it = graph.get_Iterator(vertex);
		std::set<int> actual;

		while (it.hasNext()) {
			actual.insert((int)it.next());
		}

		std::set<int> expected;
		if (vertex == 0) {
			expected = { 1 }; 
		}
		else if (vertex == 1) {
			expected = { 2,3 }; 
		}
		else if (vertex == 2) {
			expected = {3}; 
		}
		else if (vertex == 3) {
			expected = { 0,4}; 
		}
		else if (vertex == 4) {
			expected = { }; 
		}
		if (actual == expected) {
			std::cout << "Test passed for vertex " << vertex << ": ";
			for (int v : actual) {
				std::cout << v << " ";
			}
			std::cout << std::endl;
		}
		else {
			std::cout << "Test failed for vertex " << vertex << ": expected { ";
			for (int v : expected) {
				std::cout << v << " ";
			}
			std::cout << "} but got { ";
			for (int v : actual) {
				std::cout << v << " ";
			}
			std::cout << "}" << std::endl;
			return 1;
		}
	}
	/////////////Edge removal check//////////////////////////////////////////
	graph.remove_Edge(1, 2);
	for (size_t vertex = 0; vertex < graph.get_VertexAmount(); ++vertex) {
		Graph<std::string, std::string>::Iterator it = graph.get_Iterator(vertex);
		std::set<int> actual;

		while (it.hasNext()) {
			actual.insert((int)it.next());
		}

		std::set<int> expected;
		if (vertex == 0) {
			expected = { 1 };
		}
		else if (vertex == 1) {
			expected = { 3 }; 
		}
		else if (vertex == 2) {
			expected = { 3 };
		}
		else if (vertex == 3) {
			expected = { 0, 4 };
		}
		else if (vertex == 4) {
			expected = {};
		}

		if (actual == expected) {
			std::cout << "Post-removal test passed for vertex " << vertex << ": ";
			for (int v : actual) {
				std::cout << v << " ";
			}
			std::cout << std::endl;
		}
		else {
			std::cout << "Post-removal test failed for vertex " << vertex << ": expected { ";
			for (int v : expected) {
				std::cout << v << " ";
			}
			std::cout << "} but got { ";
			for (int v : actual) {
				std::cout << v << " ";
			}
			std::cout << "}" << std::endl;
			return 1;
		}
	}
	//////////Vertex removal check//////////////////////////////////////////
	int index1 = 3; 
	std::cout << "Deleting a vertex with an index: " << index1 << std::endl;
	graph.remove_Vertex(index1);
	if (graph.get_VertexAmount() != 4) {
		std::cout << "Invalid vertex deletion" << std::endl;
		return 1;
	}
	else {
		std::cout << "valid vertex removal" << std::endl;
	}

	return 0;
}