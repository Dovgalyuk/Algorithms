#include <iostream>
#include <algorithm>
#include "graph.h"
-finput-charset=cp866 -fexec-charset=utf-8
using namespace std;

int Graph::posVertex(unsigned int vertex) {
	if (find(vertexList.begin(), vertexList.end(), vertex) != vertexList.end()) {
		return find(vertexList.begin(), vertexList.end(), vertex) - vertexList.begin();
	}
	return -1;
}

//ÔÓÍÊÖÈÈ ÃÐÀÔÀ
//Ïîëó÷èòü ðàçìåð ãðàôà
unsigned int Graph::sizeGraph() {
	return vertexList.size();
}

unsigned int Graph::vertexGraph(unsigned int numVertexInList) {
	if (vertexList[numVertexInList] != NULL) {
		return vertexList[numVertexInList];
	}
	else {
		return 0;
	}
}

//Âûâîä ãðàôà
void Graph::printGraph() {
	unsigned int sizeVertexList = vertexList.size();
	cout << "Ñïèñîê ñìåæíîñòè:" << endl;
	for (unsigned int i = 0; i < sizeVertexList; i++) {
		cout << vertexList[i] << "|";
		ListItem *item = list_first(adjacencyList[i]);
		while (item != NULL) {
			cout << " " << list_item_data(item)[0] << "|" << list_item_data(item)[1];
			item = list_item_next(item);
		}
		cout << endl;
	}

	cout << "Ìåòêè âåðøèí:" << endl;
	for (unsigned int i = 0; i < sizeVertexList;i++) {
		cout << vertexList[i] << "| " << labelVertex[i] << endl;
	}
}

//Äîáàâèòü âåðøèíó
bool Graph ::addVertex(unsigned int vertex) {
	if (posVertex(vertex) != sizeGraph()) {
		vertexList.push_back(vertex);
		labelVertex.push_back(0);
		adjacencyList.push_back(list_create());
		return 1;
	}
        else
		return 0;
	}
}

//Óäàëèòü âåðøèíó
bool Graph::removeVertex(unsigned int vertex) {
 int posVert = posVertex(vertex);
	if (posVert != sizeGraph()) {
		vertexList.erase(vertexList.begin() + posVert);
		adjacencyList.erase(adjacencyList.begin() + posVert);
		labelVertex.erase(labelVertex.begin() + posVert);
		}
		return 1;
	}
	else {
		return 0;
	}
}

//Äîáàâèòü ðåáðî
bool Graph::addEdge(unsigned int firstVertex, unsigned int secondVertex, unsigned int valueEdge) {
	if (posVertex(FirstVertex) != -1  && posVertex(SecondVertex) != -1) {
		if (existEdge(FirstVertex,secondVertex)== 0) {
		addLabelEdge(firstVertex, secondVertex, valueEdge);
			return 1;
	}
		return 0;
}

//Óäàëèòü ðåáðî
bool Graph::removeEdge(unsigned int firstVertex, unsigned int secondVertex) {
	if (existEdge(firstVertex, secondVertex)) {
		ListItem *item = NULL;
			while (item =neighborsVertex(firstVertex, item)) {
				if (list_item_data(item)[0] == secondVertex) {
					list_erase(adjacencyList[posVertex], item);
					return 1;
				}
			
			}
}
	return 0;

//Ïðîâåðêà íà ñóùåñòâîâàíèå ðåáðà
bool Graph::existEdge(unsigned int firstVertex, unsigned int secondVertex)
{
	unsigned int posFirstVertex = posVertex(firstVertex);
	unsigned int posSecondVertex = posVertex(secondVertex);
	if (posFirstVertex!= vertexList.size() && posSecondVertex!= vertexList.size()) {
	ListItem *item = NULL;
		while ((item = neighborsVertex(firstVertex, item))) {
			if (list_item_data(item)[0] == secondVertex) {
				return 1;
			}
		}
	}
	return 0;
}
		
//Äîáàâèòü ìåòêó âåðøèíå
void Graph::addLabelVertex(unsigned int vertex, unsigned int valueVertex)
{
	labelVertex[posVertex(vertex)] = valueVertex;
}

//Ñ÷èòàòü ìåòêó âåðøèíû
unsigned int Graph::readLabelVertex(unsigned int vertex)
{
	return labelVertex[posVertex(vertex)];
}

//Äîáàâèòü ìåòêó ðåáðó
void Graph::addLabelEdge(unsigned int firstVertex, unsigned int secondVertex, unsigned int valueEdge)
{
	Data *secondVertexWithValueEdge = (Data*)malloc(2 * sizeof(Data));
	secondVertexWithValueEdge[0] = secondVertex;
	secondVertexWithValueEdge[1] = valueEdge;
	list_insert(adjacencyList[posVertex(firstVertex)], secondVertexWithValueEdge);
}

//×èòàòü ìåòêó ðåáðà
unsigned int Graph::readLabelEdge(unsigned int firstVertex, unsigned int secondVertex)
{
	if (existEdge(firstVertex, secondVertex)) {
		ListItem *item = NULL;
		while (item = neighborsVertex(posVertex(firstVertex), item)) {
			if (list_item_data(item)[0] == secondVertex) {
				return list_item_data(item)[1];
			}
		}
	}
	return 0;
}
ListItem* Graph::neighborsVertex(unsigned int vertex, ListItem *currentNeighbor) {
	if (currentNeighbor == NULL) {
		currentNeighbor = list_first(adjacencyList[posVertex(vertex)]);
	}
	else {
		currentNeighbor = list_item_next(currentNeighbor);
	}
	if (currentNeighbor != NULL) {
		return currentNeighbor;
	}
	else {
		return 0;
	}
}
