#include <locale>
#include <iostream>

#include "../Graphs/graph.h"
#include "../Graphs/graph.cpp"
#include "../Graphs/list.cpp"

using namespace std;

//Алгоритм Дейкстры(кратчайшего пути)
void minimWay(Graph graph, unsigned int vertex) {
	//Начальная инициализация
	unsigned int sizeGraph = graph.sizeGraph();			//Размер графа
	vector<bool> visitVertex(sizeGraph, 0);				//Посещенные вершины
	vector<vector<unsigned int>> minWay(sizeGraph);		//Кратчайшие пути
	//Присвоение всем элементам, кроме исходной, максимально большое значение
	for (unsigned int i = 0; i < sizeGraph; i++) {
		if (graph.vertexList[i] != vertex) {
			graph.addLabelVertex(graph.vertexList[i], UINT_MAX);
		}
		else {
			graph.addLabelVertex(graph.vertexList[i], 0);
		}
	}

	//Основной цикл
	unsigned int vertexMinLabel;
	unsigned int valueVertexMinLabel;
	for (unsigned int i = 0; i < sizeGraph; i++) {
		//Выбор не посещенной вершины с наименьшим значением метки
		valueVertexMinLabel = UINT_MAX;
		for (unsigned int j = 0; j < sizeGraph;j++) {
			if (visitVertex[graph.posVertex(graph.vertexList[j])] == 0 && graph.readLabelVertex(graph.vertexList[j]) < valueVertexMinLabel) {
				vertexMinLabel = graph.vertexList[j];
				valueVertexMinLabel = graph.readLabelVertex(graph.vertexList[j]);
			}
		}
		visitVertex[graph.posVertex(vertexMinLabel)] = 1;

		//Перебор всех соседних вершин и подсчёт
		for (ListItem* item = list_first(graph.adjacencyList[graph.posVertex(vertexMinLabel)]); item != NULL; item = list_item_next(item)) {
			if (graph.labelVertex[graph.posVertex(list_item_data(item))] > graph.labelVertex[graph.posVertex(vertexMinLabel)] + graph.labelEdge[graph.posVertex(vertexMinLabel)][graph.posVertex(list_item_data(item))]) {
				bool markNewMinWay = false;
				if (graph.labelVertex[graph.posVertex(list_item_data(item))] != UINT_MAX) {
					markNewMinWay = true;
				}
				graph.labelVertex[graph.posVertex(list_item_data(item))] = graph.labelVertex[graph.posVertex(vertexMinLabel)] + graph.labelEdge[graph.posVertex(vertexMinLabel)][graph.posVertex(list_item_data(item))];
				if (markNewMinWay == true) {
					minWay[graph.posVertex(list_item_data(item))].clear();
				}
				for (unsigned int j = 0; j < minWay[graph.posVertex(vertexMinLabel)].size(); j++) {
					minWay[graph.posVertex(list_item_data(item))].push_back(minWay[graph.posVertex(vertexMinLabel)][j]);
				}
				minWay[graph.posVertex(list_item_data(item))].push_back(vertexMinLabel);
			}
		}
	}

	//Вывод результатов
	for (unsigned int i = 0; i < sizeGraph; i++) {
		if (graph.vertexList[i] != vertex) {
			if (graph.labelVertex[i] != UINT_MAX) {
				cout << "Длина пути от " << vertex << " до " << graph.vertexList[i] << " = " << graph.labelVertex[i] << ". Путь: ";
				for (unsigned int j = 0; j < minWay[i].size(); j++) {
					cout << minWay[i][j] << "->";
				}
				cout << graph.vertexList[i] << endl;
			}
			else {
				cout << "Пути от " << vertex << " до " << graph.vertexList[i] << " не существует." << endl;
			}
		}
	}
}

//ГЛАВНАЯ ФУНКЦИЯ
void main() {
	setlocale(LC_ALL, "Russian");

	//Инициализация графа
	cout << "НАЧАЛЬНАЯ ИНИЦИАЛИЗАЦИЯ ГРАФА" << endl;
	cout << "Введите количество вершин графа: ";
	Graph graph;						//Создаём граф
	unsigned int vertex;				//Номер вершины

	//УБРАТЬ КОММЕНТАРИИ ДЛЯ ПОЛЬЗОВАТЕЛЬСКОГО ВВОДА
	unsigned int numVertex;				//Кол-во вершин в графе
	cin >> numVertex;
	for (unsigned int i = 0; i < numVertex; i++) {
		cout << "Введите номер для новой вершины: ";
		cin >> vertex;
		graph.addVertex(vertex);
	}

	//Пример графа
	/*graph.addVertex(1);
	graph.addVertex(2);
	graph.addVertex(3);
	graph.addVertex(4);
	graph.addVertex(5);
	graph.addEdge(1, 2, 1);
	graph.addEdge(1, 3, 5);
	graph.addEdge(1, 5, 9);
	graph.addEdge(2, 3, 3);
	graph.addEdge(4, 3, 8);
	graph.addEdge(5, 2, 3);
	graph.addEdge(5, 3, 11);
	graph.addEdge(5, 4, 4);*/

	//Меню
	unsigned int numItemMenu;	//Пункт в меню
	unsigned int firstVertex;	//Исходная вершина ребра
	unsigned int secondVertex;	//Конечная вершина ребра
	unsigned int valueEdge;		//Значение метки ребра
	for (;;) {
		system("cls");
		cout << "ПРЕДСТАВЛЕНИЕ ГРАФА В ВИДЕ МАТРИЦЫ СМЕЖНОСТИ:" << endl;
		graph.printGraph();
		cout << endl;
		cout << "МЕНЮ" << endl;
		cout << "1. Добавить вершину." << endl;
		cout << "2. Удалить вершину." << endl;
		cout << "3. Добавить ребро." << endl;
		cout << "4. Удалить ребро" << endl;
		cout << "5. Проверить ребро на существование в графе." << endl;
		cout << "6. Найти кратчайший путь от одной вершины до всех других." << endl;
		cout << "7. Выход." << endl;
		cout << ">";
		cin >> numItemMenu;
		switch (numItemMenu)
		{
		case 1:
			cout << "Введите номер для новой вершины: ";
			cin >> vertex;
			graph.addVertex(vertex);
			system("pause");
			break;
		case 2:
			cout << "Введите номер вершины для удаления: ";
			cin >> vertex;
			graph.removeVertex(vertex);
			system("pause");
			break;
		case 3:
			cout << "Исходная вершина: ";
			cin >> firstVertex;
			cout << "Конечная вершина: ";
			cin >> secondVertex;
			cout << "Метка для данного ребра: ";
			cin >> valueEdge;
			graph.addEdge(firstVertex, secondVertex, valueEdge);
			system("pause");
			break;
		case 4:
			cout << "Исходная вершина: ";
			cin >> firstVertex;
			cout << "Конечная вершина: ";
			cin >> secondVertex;
			graph.removeEdge(firstVertex, secondVertex);
			system("pause");
			break;
		case 5:
			cout << "Исходная вершина: ";
			cin >> firstVertex;
			cout << "Конечная вершина: ";
			cin >> secondVertex;
			graph.existEdge(firstVertex, secondVertex);
			system("pause");
			break;
		case 6:
			cout << "Исходная вершина: ";
			cin >> vertex;
			minimWay(graph, vertex);
			system("pause");
			break;
		case 7:
			return;
		}
	}
}