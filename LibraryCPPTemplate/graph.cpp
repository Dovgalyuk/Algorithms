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
	
	int size = 15;

	Graph<int>* testGraph = new Graph<int>(size);

	//Проверка размера графа после его создания
	if (testGraph->getSize() != size) {
		cout << "Error size graph\n\n";
		return 0;
	}

	//Проверка работы итератора вершин
	Graph<int>::vertexIterator vIterator(testGraph);

	int counter = 0;
	while (*vIterator != nullptr) {
		++vIterator;
		counter++;
	}

	if (counter != size) {
		cout << "Vertex Iterator error!";
		return 0;
	}
	vIterator.iteratorBegin(testGraph); //Обнуление значения итератора

	while (*vIterator != nullptr) {
		if (testGraph->getVertexData(*vIterator) != 0) {
			cout << "Error";
			return 0;
		}
		++vIterator;
	}
	vIterator.iteratorBegin(testGraph);

	//Проверка работы заполнения вершин
	int value = 0;
	while (*vIterator != nullptr) {
		testGraph->setVertexData(*vIterator, value);
		++vIterator;
		value++;
	}

	value = 0;
	while (*vIterator != nullptr) {
		if (testGraph->getVertexData(*vIterator) != value) {
			cout << "Error fill vertex value";
			return 0;
		}
		++vIterator;
		value++;
	}
	vIterator.iteratorBegin(testGraph);

	//Проверка удаления вершин
	testGraph->deleteVertex(findVertex(testGraph, size - 1));
	size--;

	testGraph->deleteVertex(findVertex(testGraph, 3));
	size--;

	counter = 0;
	while (*vIterator != nullptr) {
		++vIterator;
		counter++;
	}

	if (counter != size) {
		cout << "Vertex Iterator error!";
		return 0;
	}

	if (counter != size) {
		cout << "Vertex delete error!";
		return 0;
	}
	vIterator.iteratorBegin(testGraph);

	//Проверка метода добавления вершины
	testGraph->addVertex(15);
	size++;

	counter = 0;
	while (*vIterator != nullptr) {
		++vIterator;
		counter++;
	}

	if (counter != size) {
		cout << "Vertex Iterator error!";
		return 0;
	}

	if (counter != size) {
		cout << "Vertex delete error!";
		return 0;
	}
	vIterator.iteratorBegin(testGraph);

	//Проверка работы метода по созданию ребра между вершинами
	testGraph->addEdgeBetween(findVertex(testGraph, 0), findVertex(testGraph, 1));
	if (!testGraph->isEdgeExistBetween(findVertex(testGraph, 0), findVertex(testGraph, 1))) {
		cout << "Error create edge between vertexes";
		return 0;
	}

	testGraph->addEdgeBetween(findVertex(testGraph, 0), findVertex(testGraph, 2));
	if (!testGraph->isEdgeExistBetween(findVertex(testGraph, 0), findVertex(testGraph, 2))) {
		cout << "Error create edge between vertexes";
		return 0;
	}

	testGraph->addEdgeBetween(findVertex(testGraph, 0), findVertex(testGraph, 3), 10);
	if (!testGraph->isEdgeExistBetween(findVertex(testGraph, 0), findVertex(testGraph, 3))) {
		cout << "Error create edge between vertexes";
		return 0;
	}

	//Проверка работы метода по удалению ребра между вершинами
	testGraph->deleteEdgeBetween(findVertex(testGraph, 0), findVertex(testGraph, 2));
	if (testGraph->isEdgeExistBetween(findVertex(testGraph, 0), findVertex(testGraph, 2))) {
		cout << "Error delete edge between vertexes";
		return 0;
	}

	testGraph->setVertexData(findVertex(testGraph, 5), 31);
	if (findVertex(testGraph, 5)->getData() != 31) {
		cout << "Error set data to Vertex";
		return 0;
	}

	if (testGraph->getVertexData(findVertex(testGraph, 5)) != findVertex(testGraph, 5)->getData()) {
		cout << "Error get data to Vertex";
		return 0;
	}

	testGraph->setEdgeWeight(findVertex(testGraph, 0), findVertex(testGraph, 1), 5);
	if (testGraph->getEdgeWeight(findVertex(testGraph, 0), findVertex(testGraph, 1)) != 5) {
		cout << "Error get weight to Edge between Vertexes";
		return 0;
	}

	Graph<int>::edgeIterator eIterator(findVertex(testGraph, 0));
	
	counter = 0;
	while (*eIterator != nullptr) {
		++eIterator;
		counter++;
	}

	if (counter != findVertex(testGraph, 0)->getSize()) {
		cout << "Vertex delete error!";
		return 0;
	}

	cout << "All test have been passed!";
	return 1;
}