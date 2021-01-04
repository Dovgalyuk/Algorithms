#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "interface.h"

class Graph :public Interface {
public:
	vector <unsigned int> vertexList;				//Список вершин графа
	vector <List*> adjacencyList;					//Список смежности
	vector <unsigned int> labelVertex;				//Метка вершин
	vector <vector<unsigned int>> labelEdge;		//Метки рёбер

	//Вспомогательные функции
	unsigned int posVertex(unsigned int vertex);	//Получить позицию вершины в списке

	//Конструктор
	Graph() {}
	//Деструктор
	virtual ~Graph() {}

	//Функции
	virtual unsigned int sizeGraph();																			//Размер графа
	virtual void printGraph();																					//Вывод графа
	virtual void addVertex(unsigned int vertex);																//Добавить вершину
	virtual void removeVertex(unsigned int vertex);																//Удалить вершину
	virtual void addEdge(unsigned int firstVertex, unsigned int secondVertex, unsigned int valueEdge);			//Добавить ребро
	virtual void removeEdge(unsigned int firstVertex, unsigned int secondVertex);								//Удалить ребро
	virtual void existEdge(unsigned int firstVertex, unsigned int secondVertex);								//Проверка на существование ребра
	virtual void addLabelVertex(unsigned int vertex, unsigned int valueVertex);									//Задать метку вершине
	virtual unsigned int readLabelVertex(unsigned int vertex);													//Считать метку вершины
	virtual void addLabelEdge(unsigned int firstVertex, unsigned int secondVertex, unsigned int valueEdge);		//Задать метку ребру
	virtual unsigned int readLabelEdge(unsigned int firstVertex, unsigned int secondVertex);					//Считать метку ребра
};

#endif