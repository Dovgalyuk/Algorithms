#include <iostream>
#include "graph.h"
#include <vector>

using namespace std;

void floyd(Graph<int>& graph) {
	vector<vector<int>> adjacencyMatrix(graph.getVertexAmount(), vector<int>(graph.getVertexAmount(), INT_MAX));
	for (size_t i = 0; i < graph.getVertexAmount(); i++) {
		Graph<int>::Iterator iterator = graph.getIterator(i);
		while (*iterator) {
			adjacencyMatrix[i][iterator.getEnd()] = graph.getEdge(iterator.getStart(), iterator.getEnd()).getWeight();
			++iterator;
		}
		adjacencyMatrix[i][i] = 0;
	}

	int maxpath = -1;
	int start = 0;
	int end = 0;

	for (size_t attempt = 0; attempt < graph.getVertexAmount(); attempt++) {
		for (size_t i = 0; i < graph.getVertexAmount(); i++) {
			for (size_t j = 0; j < graph.getVertexAmount(); j++) {
				adjacencyMatrix[i][j] = adjacencyMatrix[i][j] <
					(adjacencyMatrix[i][attempt] + adjacencyMatrix[attempt][j]) ||
					(adjacencyMatrix[i][attempt] + adjacencyMatrix[attempt][j]) < 0
					? adjacencyMatrix[i][j] : adjacencyMatrix[i][attempt] + adjacencyMatrix[attempt][j];
				if (attempt == graph.getVertexAmount() - 1 && adjacencyMatrix[i][j] > maxpath && adjacencyMatrix[i][j] != INT_MAX) {
					maxpath = adjacencyMatrix[i][j];
					start = i;
					end = j;
				}
			}
		}
	}

	cout << "Longest shortest path according to Floyd's algorithm: " << start << "->" << end << " with weight = " << maxpath << "\n";
}

int main() {
	size_t vertexAmount;
	cout << "Enter vertex amount: ";
	cin >> vertexAmount;

	Graph<int> graph(vertexAmount);

	size_t edgeAmount;
	cout << "Enter edge amount: ";
	cin >> edgeAmount;
	for (size_t i = 0; i < edgeAmount; i++) {
		size_t start, end;
		int data;
		cout << "Enter vertex start(0-" << vertexAmount - 1 << "), vertex end(0-" << vertexAmount - 1 << ") and data: ";
		cin >> start >> end >> data;
		graph.addEdge(start, end, data);
	}
	/*Graph<int> graph(3);
	graph.addEdge(0, 1, 8);
	graph.addEdge(0, 2, 5);
	graph.addEdge(1, 0, 3);
	graph.addEdge(2, 1, 2);*/
	floyd(graph);
}