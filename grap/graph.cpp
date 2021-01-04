#include <iostream>
#include <algorithm>
#include "graph.h"

using namespace std;

//ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ГРАФ
//Получить позицию вершины в списке
unsigned int Graph::posVertex(unsigned int vertex) {
	return find(vertexList.begin(), vertexList.end(), vertex) - vertexList.begin();
}

//ФУНКЦИИ ГРАФА
//Получить размер графа
unsigned int Graph::sizeGraph() {
	return vertexList.size();
}

//Вывод графа
void Graph::printGraph() {
	unsigned int sizeVertexList = vertexList.size();
	cout << "Список смежности:" << endl;
	for (unsigned int i = 0; i < sizeVertexList; i++) {
		cout << vertexList[i] << "|";
		ListItem *item = list_first(adjacencyList[i]);
		while (item != NULL) {
			cout << " " << list_item_data(item);
			item = list_item_next(item);
		}
		cout << endl;
	}

	cout << "Метки вершин:" << endl;
	for (unsigned int i = 0; i < sizeVertexList;i++) {
		cout << vertexList[i] << "| " << labelVertex[i] << endl;
	}

	cout << "Метки рёбер:" << endl;
	for (unsigned int i = 0; i < sizeVertexList;i++) {
		cout << vertexList[i] << "|";
		for (unsigned int j = 0; j < sizeVertexList; j++) {
			cout << " " << labelEdge[i][j];
		}
		cout << endl;
	}
}

//Добавить вершину
void Graph::addVertex(unsigned int vertex) {
	if (posVertex(vertex) == vertexList.size()) {
		vertexList.push_back(vertex);
		labelVertex.push_back(0);
		adjacencyList.push_back(list_create());

		unsigned int numVertex = labelEdge.size() + 1;
		labelEdge.resize(numVertex);
		for (unsigned int i = 0; i < numVertex; i++) {
			labelEdge[i].resize(numVertex, 0);
		}

		cout << "Вершина добавлена." << endl;
	}
	else {
		cout << "Введённая вершина уже существует." << endl;
	}
}

//Удалить вершину
void Graph::removeVertex(unsigned int vertex) {
	unsigned int posVert = posVertex(vertex);
	if (posVert != vertexList.size()) {
		vertexList.erase(vertexList.begin() + posVert);
		adjacencyList.erase(adjacencyList.begin() + posVert);
		labelVertex.erase(labelVertex.begin() + posVert);
		unsigned int newSizeMatrix = vertexList.size();
		for (unsigned int i = 0; i < newSizeMatrix; i++) {
			labelEdge[i].erase(labelEdge[i].begin() + posVert);
		}
		cout << "Вершина удалена." << endl;
	}
	else {
		cout << "Введённая вершина не существует." << endl;
	}
}

//Добавить ребро
void Graph::addEdge(unsigned int firstVertex, unsigned int secondVertex, unsigned int valueEdge) {
	unsigned int posFirstVertex = posVertex(firstVertex);
	unsigned int posSecondVertex = posVertex(secondVertex);
	if (posFirstVertex != vertexList.size() && posSecondVertex != vertexList.size()) {
		if (labelEdge[posFirstVertex][posSecondVertex] != 0) {
			cout << "Ребро между данными вершинами уже существует." << endl;
		}
		else {
			list_insert(adjacencyList[posFirstVertex], secondVertex);
			addLabelEdge(firstVertex, secondVertex, valueEdge);

			cout << "Ребро между данными вершинами добавлено." << endl;
		}
	}
	else {
		cout << "Одна из введённых вершин (или обе) не существует(ют)." << endl;
	}
}

//Удалить ребро
void Graph::removeEdge(unsigned int firstVertex, unsigned int secondVertex) {
	unsigned int posFirstVertex = posVertex(firstVertex);
	unsigned int posSecondVertex = posVertex(secondVertex);
	if (posFirstVertex != vertexList.size() && posSecondVertex != vertexList.size()) {
		if (labelEdge[posFirstVertex][posSecondVertex] != 0) {
			ListItem *item = list_first(adjacencyList[posFirstVertex]);
			while (item != NULL) {
				if (list_item_data(item) == secondVertex) {
					list_erase(adjacencyList[posFirstVertex], item);
					break;
				}
				else {
					item = list_item_next(item);
				}
			}
			labelEdge[posFirstVertex][posSecondVertex] = 0;
			cout << "Ребро между данными вершинами удалено." << endl;
		}
		else {
			cout << "Ребро между данными вершинами не существует." << endl;
		}
	}
	else {
		cout << "Одна из введённых вершин (или обе) не существует(ют)." << endl;
	}
}

//Проверка на существование ребра
void Graph::existEdge(unsigned int firstVertex, unsigned int secondVertex)
{
	if (posVertex(firstVertex) != vertexList.size() && posVertex(secondVertex) != vertexList.size()) {
		if (readLabelEdge(firstVertex, secondVertex) != 0) {
			cout << "Ребро между данными вершинами существует." << endl;
		}
		else {
			cout << "Ребро между данными вершинами не существует." << endl;
		}
	}
	else {
		cout << "Одна из введённых вершин (или обе) не существует(ют)." << endl;
	}
}

//Добавить метку вершине
void Graph::addLabelVertex(unsigned int vertex, unsigned int valueVertex)
{
	labelVertex[posVertex(vertex)] = valueVertex;
}

//Считать метку вершины
unsigned int Graph::readLabelVertex(unsigned int vertex)
{
	return labelVertex[posVertex(vertex)];
}

//Добавить метку ребру
void Graph::addLabelEdge(unsigned int firstVertex, unsigned int secondVertex, unsigned int valueEdge)
{
	labelEdge[posVertex(firstVertex)][posVertex(secondVertex)] = valueEdge;
}

//Читать метку ребра
unsigned int Graph::readLabelEdge(unsigned int firstVertex, unsigned int secondVertex)
{
	return labelEdge[posVertex(firstVertex)][posVertex(secondVertex)];
}

