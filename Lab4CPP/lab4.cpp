#include <iostream>
#include <vector>
#include <limits>
#include "graph.h" 
#include <fstream>
#include <stdexcept>
using namespace std;


void Prime(const Graph<std::string, int>& graph) {
	size_t vertexCount = graph.get_VertexAmount();
	vector<bool> inMST(vertexCount, false);
	vector<int> minEdge(vertexCount, numeric_limits<int>::max());
	vector<size_t> parent(vertexCount, numeric_limits<size_t>::max());

	minEdge[0] = 0;
	for (size_t count = 0; count < vertexCount - 1; count++) {

		int minWeight = numeric_limits<int>::max();
		size_t u = numeric_limits<size_t>::max();

		for (size_t v = 0; v < vertexCount; v++) {
			if (!inMST[v] && minEdge[v] < minWeight) {
				minWeight = minEdge[v];
				u = v;
			}
		}

		inMST[u] = true;


		Graph<std::string,int>::Iterator it = graph.get_Iterator(u);
		while (it.hasNext()) {
			size_t v = it.next(); 
			int  weight = graph.get_Edge(u, v)->mark;

			if (!inMST[v] && weight < minEdge[v]) {
				parent[v] = u;
				minEdge[v] = weight;
			}
		}


	}

	cout << "Edges in the Minimum Spanning Tree:\n";
	for (size_t i = 1; i < vertexCount; i++) {
		if (parent[i] != numeric_limits<size_t>::max()) {
			cout << "Vertex " << parent[i] << " -> Vertex " << i << " with weight " << minEdge[i] << endl;
		}
	}
}
int main(int argc, char** argv) {
	int qty_vertex;
	try {
		std::ifstream inputFile(argv[1]);
		if (!inputFile.is_open()) {
			throw std::out_of_range("file opening error");
			return 1;
		}
		Graph<std::string, int>::GraphType type = Graph<std::string, int>::GraphType::Undirected;

		Graph<std::string, int> graph(type);

		std::string temp = "";
		inputFile >> qty_vertex;

		while (qty_vertex) {
			inputFile >> temp;
			graph.add_Vertex(temp);
			qty_vertex--;
		}

		while (true) {
			int start, end, weight;
			inputFile >> start;
			if (start == -1) break;
			inputFile >> end >> weight;

			graph.add_Edge(start, end, weight);
		}

		inputFile.close();

		Prime(graph);
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}