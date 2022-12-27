#include <iostream>	
#include "list.h"
#include "graph.h"
#include <stack>

using namespace std;

//Function that return link to needed Vertex from list of Vertexes
Graph<int>::Vertex* linkToVertex (Graph<int>* graph, int count) {
	Graph<int>::vertexIterator vIterator(graph);
	int counter = 0;
	while (counter != count) {
		++vIterator;
		counter++;
	}
	return *vIterator;
}
//Function of search in Depth
void searchInDepth(Graph<int>::Vertex* vertex, List<Graph<int>::Vertex*>* visitedVertexes) {
	bool isEnd = false;
	stack<Graph<int>::Vertex*> stack;

	while (!isEnd) {
		Graph<int>::edgeIterator eIterator(vertex);

		while (*eIterator != nullptr) {
			Graph<int>::Edge* i = *eIterator;
			stack.push(i->getDirection());
			++eIterator;
		}
		eIterator.iteratorBegin(vertex);

		if (visitedVertexes->isListEmpty()) visitedVertexes->insert(vertex);
		else visitedVertexes->insert_after(visitedVertexes->last(), vertex);

		if (!stack.empty()) {
			vertex = stack.top();
			stack.pop();
			for (List<Graph<int>::Vertex*>::Item* i = visitedVertexes->first(); i != nullptr; i = i->getNext()) {
				if (i->data == vertex && !stack.empty()) {
					vertex = stack.top();
					stack.pop();
					i = visitedVertexes->first();
				} 
				else if (i->data == vertex && stack.empty()) {
					isEnd = true;
					break;
				}
			}
		}
		else isEnd = true;
	}
}


int main() {
	
	//value to define size of graph
	size_t size = 10;

	//Creating graph
	Graph<int>* graph = new Graph<int>(size);
	//Creating massive of visited vertexes by searchInDeep
	List<Graph<int>::Vertex*> visitedVertexes;

	//Making vertex Iterator
	Graph<int>::vertexIterator vIterator(graph);

	//Vertex filling
	int value = 1;
	while (*vIterator != nullptr) {
		graph->setVertexData(*vIterator, value);
		++vIterator;
		value++;
	}
	vIterator.iteratorBegin(graph);

	//Making edges between Vertexes
	graph->addEdgeBetween(linkToVertex(graph, 0), linkToVertex(graph, 1));
	graph->addEdgeBetween(linkToVertex(graph, 0), linkToVertex(graph, 3));
	graph->addEdgeBetween(linkToVertex(graph, 0), linkToVertex(graph, 2));
	graph->addEdgeBetween(linkToVertex(graph, 4), linkToVertex(graph, 5));
	graph->addEdgeBetween(linkToVertex(graph, 5), linkToVertex(graph, 6));
	graph->addEdgeBetween(linkToVertex(graph, 6), linkToVertex(graph, 4));
	graph->addEdgeBetween(linkToVertex(graph, 7), linkToVertex(graph, 8));

	int connectivityCount = 0;
	for (size_t graphItem = 0; visitedVertexes.getSize() != size; graphItem++) {
		if (visitedVertexes.isListEmpty()) {
			searchInDepth(linkToVertex(graph, graphItem), &visitedVertexes);
			connectivityCount++;
		}
		else {
			bool isVisited = false;
			for (List<Graph<int>::Vertex*>::Item* i = visitedVertexes.first(); i != nullptr; i = i->getNext()) {
				if (linkToVertex(graph, graphItem) == i->data) {
					isVisited = true;
					break;
				} 
			}
			if (!isVisited) {
				searchInDepth(linkToVertex(graph, graphItem), &visitedVertexes);
				connectivityCount++;
			}
		}
	}

	while (!visitedVertexes.isListEmpty()) {
		cout << visitedVertexes.first()->data->getData() << " | ";
		visitedVertexes.erase(visitedVertexes.first());
	}
	cout  << "\n\n" << "Graph connectivity components count is: " << connectivityCount;

	//Memory clear
	delete graph;
	return 0;
}