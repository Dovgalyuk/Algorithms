#include <iostream>	
#include "list.h"
#include "graph.h"

using namespace std;

Graph<int>::Vertex* findVertex (Graph<int>* graph, int count) {
	Graph<int>::vertexIterator vIterator(graph);
	int counter = 0;
	while (counter != count) {
		++vIterator;
		counter++;
	}
	return *vIterator;
}

int main() {
	
	int size = 11;

	Graph<int>* graph = new Graph<int>(size);

	Graph<int>::vertexIterator vIterator(graph);

	int value = 0;
	while (*vIterator != nullptr) {
		graph->setVertexData(*vIterator, value);
		++vIterator;
		value++;
	}
	vIterator.iteratorBegin(graph);

	graph->addEdgeBetween(findVertex(graph, 0), findVertex(graph, 1));
	graph->addEdgeBetween(findVertex(graph, 0), findVertex(graph, 2), 19);
	graph->addEdgeBetween(findVertex(graph, 0), findVertex(graph, 3));
	graph->addEdgeBetween(findVertex(graph, 3), findVertex(graph, 2));
	graph->addEdgeBetween(findVertex(graph, 2), findVertex(graph, 4));
	graph->addEdgeBetween(findVertex(graph, 4), findVertex(graph, 5));
	graph->addEdgeBetween(findVertex(graph, 6), findVertex(graph, 7));
	graph->addEdgeBetween(findVertex(graph, 7), findVertex(graph, 8));
	graph->addEdgeBetween(findVertex(graph, 9), findVertex(graph, 10));


	return 0;
}