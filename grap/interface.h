#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include "list.h"

using namespace std;

//1. ИНТЕРФЕЙС
class Interface {
public:
	vector <unsigned int> vertexList;				//Список вершин графа
	vector <List*> adjacencyList;					//Список смежности
	vector <unsigned int> labelVertex;				//Метка вершин
	vector <vector<unsigned int>> labelEdge;		//Метки рёбер


	Interface() {}									//Конструктор
	virtual ~Interface() {}							//Деструктор 

	//Функции
	virtual unsigned int sizeGraph() = 0;								//Размер графа
	virtual void printGraph() {};										//Вывод графа
	virtual void addVertex() {};										//Добавить вершину
	virtual void removeVertex() {};										//Удалить вершину
	virtual void addEdge() {};											//Добавить ребро
	virtual void removeEdge() {};										//Удалить ребро
	virtual void existEdge() {};										//Проверка на существование ребра
	virtual void addLabelVertex() {};									//Задать метку вершине
	virtual unsigned int readLabelVertex(unsigned int) = 0;				//Считать метку вершины
	virtual void addLabelEdge() {};										//Задать метку ребру
	virtual unsigned int readLabelEdge(unsigned int, unsigned int) = 0;	//Считать метку ребра
};

#endif