#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

template<typename Data>
class Graph {
public:
	//проверено
	//структура вершин
	struct Vertex {
	private:
		Data vertexData;
	public:
		Vertex(Data vertexData) {
			this->vertexData = vertexData;
		}
		void setVertexData(Data vertexData) {
			this->vertexData = vertexData;
		}
		Data getVertexData() {
			return this->vertexData;
		}
	};
	//структора ребра
	struct Edge {
	private:
		Data edgeData;
	public:
		Edge(Data data) {
			this->edgeData = data;
		}
		void setEdgeData(Data data) {
			this->edgeData = data;
		}
		Data getEdgeData() {
			return edgeData;
		}
	};
	//конструктор графа
	Graph(size_t vertexAmount) {
		vertexes = new Vector<Vertex*>;
		vertexes->resize(vertexAmount);
		for (size_t i = 0; i < vertexAmount; i++) {
			vertexes->set(i, new Vertex(static_cast<int>(i)));
		}
		edgeMatrix = new Vector<Edge*>;
		edgeMatrix->resize(vertexAmount * vertexAmount);
		for (size_t i = 0; i < edgeMatrix->size(); i++) {
			edgeMatrix->set(i, nullptr);
		}
	}
	//деструктор
	~Graph() {
		//Удаляем сначала все структоры в векторе
		for (size_t i = 0; i < vertexes->size(); i++) {
			delete vertexes->get(i);
		}
		delete vertexes;//удаляем вектор

		for (size_t i = 0; i < edgeMatrix->size(); i++) {
			delete edgeMatrix->get(i);
		}
		delete edgeMatrix;
	}

	//Конструктор копирования
	Graph(const Graph& a) {
		vertexes = nullptr;
		edgeMatrix = nullptr;
		*this = a;
	}

	Graph& operator=(const Graph& a) {
		if (this != &a) {
			if (vertexes) {
				for (size_t i = 0; i < vertexes->size(); i++) {
					delete vertexes->get(i);
				}
				delete vertexes;//удаляем вектор
			}
			if (edgeMatrix) {
				for (size_t i = 0; i < edgeMatrix->size(); i++) {
					delete edgeMatrix->get(i);
				}
				delete edgeMatrix;
			}

			vertexes = new Vector<Vertex*>;
			vertexes->resize(a.vertexes->size());
			for (size_t i = 0; i < vertexes->size(); i++) {
				vertexes->set(i, new Vertex(*(a.vertexes->get(i))));
			}

			edgeMatrix = new Vector<Edge*>;
			edgeMatrix->resize(a.edgeMatrix->size());
			for (size_t i = 0; i < edgeMatrix->size(); i++) {
				Edge* edge = a.edgeMatrix->get(i);
				edgeMatrix->set(i, new Edge(*(edge)));  // Копирование данных каждого ребра
			}
		}
		return *this;
	}

	size_t getVertexAmount() {
		return vertexes->size();
	}
	
	size_t addVertex(Data vertexData) {
		size_t index = vertexes->size();
		vertexes->resize(index + 1);
		vertexes->set(index, new Vertex(vertexData));

		size_t vertexAmount = getVertexAmount();
		// Создание временной матрицы смежности для включения новой вершины
		Vector<Edge*>* buffMatrix = new Vector<Edge*>;
		// Установка размера новой матрицы смежности, исходя из нового количества вершин
		buffMatrix->resize(vertexAmount * vertexAmount);
		for (size_t i = 0; i < vertexAmount; i++) {
			for (size_t j = 0; j < vertexAmount; j++) {
				// Копирование существующих рёбер в новую матрицу смежности
				// Индекс для получения ребра из старой матрицы смежности обновляется для учёта новой вершины
				buffMatrix->set((i * vertexAmount) + j, edgeMatrix->get(i * index + j));
			}
		}

		//Удаление старых ребер из матрицы
		for (size_t i = 0; i < edgeMatrix->size(); i++) {
			if (edgeMatrix->get(i)) {
				delete edgeMatrix->get(i);
			}
		}
		// Освобождение памяти, занимаемой старой матрицей смежности
		delete edgeMatrix;
		// Установка новой матрицы смежности в качестве текущей для графа
		edgeMatrix = buffMatrix;
		// Возвращение индекса, на который была добавлена новая вершина
		return index;
	}

	void removeVertex(size_t index) {
		//Получение текущего кол-ва вершин
		size_t _vertexAmount = getVertexAmount();

		//Если указанный индекс выходит за пределы кол-ва вершин, выходим из функции
		if (index >= _vertexAmount) {
			return;
		}

		//Удаление вершины из вектора вершин
		Vertex* vertex = vertexes->get(index);
		delete vertex;

		//Сдвиг вершин в векторе вершин на одну позицию назад
		for (size_t i = index; i < _vertexAmount - 1; i++) {
			vertexes->set(i, vertexes->get(i + 1));
		}
		vertexes->resize(_vertexAmount - 1); //Уменьшение размера вектора вершин

		//Удаление всех ребер, соответсвуюших удаленной вершине
		for (size_t i = 0; i < _vertexAmount; i++) {
			Edge* edge = edgeMatrix->get(index * _vertexAmount + i);
			if (edge) {
				delete edge;
			}
			edge = edgeMatrix->get(i * _vertexAmount + index);
			if (edge) {
				delete edge;
			}
		}

		// После удаления вершины обновляем количество вершин для новой матрицы смежности
		size_t vertex_amount = getVertexAmount();
		
		Vector<Edge*>* buffMatrix = new Vector<Edge*>;
		buffMatrix->resize(vertex_amount * vertex_amount);
		for (size_t i = 0; i < vertex_amount; i++) {
			for (size_t j = 0; j < vertex_amount; j++) {
				Edge* edge = edgeMatrix->get(((i + (i >= index)) * _vertexAmount) + (j + (j >= index)));
				buffMatrix->set((i * vertex_amount) + j, edge);
			}
		}
		//Удаление старой матрицы
		delete edgeMatrix;
		//устанавливаем новую матрицу
		edgeMatrix = buffMatrix;
	}

	//получение вершины
	Vertex* getVertex(size_t index) {
		return vertexes->get(index);
	}

	Edge* getEdge(size_t startVertexIndex, size_t endVertexIndex) {
		size_t vertexAmount = getVertexAmount();
		return edgeMatrix->get(startVertexIndex * vertexAmount + endVertexIndex);
	}

	bool isEdgeExist(size_t startVertexIndex, size_t endVertexIndex) {
		return getEdge(startVertexIndex, endVertexIndex) != nullptr;
	}

	void addEdge(size_t startVertexIndex, size_t endVertexIndex, Data edgeData) {
		// Получение общего количества вершин в графе для расчета индексов в матрице смежности
		size_t vertexAmount = getVertexAmount();

		//Попытка получить рубро из метрицы смежности по индексам начала и конца
		Edge* edge = edgeMatrix->get(startVertexIndex * vertexAmount + endVertexIndex);
		if (edge) {
			//если ребро существует просто обновляем его значение
			edge->setEdgeData(edgeData);
		}
		else {
			//иначе создаем новое ребро
			Edge* newEdge = new Edge(edgeData);
			edgeMatrix->set(startVertexIndex * vertexAmount + endVertexIndex, newEdge);
		}
	}

	void removeEdge(size_t startVertexIndex, size_t endVertexIndex) {
		size_t vertexAmount = getVertexAmount();
		Edge* edge = edgeMatrix->get(startVertexIndex * vertexAmount + endVertexIndex);
		delete edge; //удаляем данные ребра
		edgeMatrix->set(startVertexIndex * vertexAmount + endVertexIndex, nullptr);
	}

	struct Iterator {
	private:
		Graph* graph; // Указатель на граф, по которому будет производиться итерация
		size_t start; // Индекс начальной вершины для итерации
		//end это int, потому что size_t не может быть отрицательным числом
		int end = -1; // Индекс следующей смежной вершины. Инициализируется как -1, что означает конец итерации
		
	
		//близжайшая смежная вершина
		int getNearVertex() {
			for (size_t i = end + 1; i < graph->getVertexAmount(); i++) {
				if (graph->isEdgeExist(start, i)) {
					return static_cast<int>(i);
				}
			}
			return -1;
		}
	public:
		Iterator(Graph* graph, size_t start) {
			this->graph = graph;
			this->start = start;
			this->end = getNearVertex();
		}

		Vertex* operator *() {
			if (end != -1) {
				//если есть смежные вершины, то возвращаем смежную вершину
				return graph->getVertex(end);
			}
			else {
				//иначе вершины нет
				return nullptr;
			}
		}
		
		//переход к следующей смежной вершине
		void operator ++() {
			end = getNearVertex(); // Обновление индекса смежной вершины
		}

		//получение индекса текущей смежной вершины
		//const означает, что нельзя изменить переменную, которую возвращает этот метод
		size_t getIndex() const {
			return end;
		}

		int getStart() const {
			return start;
		}
	};

	Iterator getIterator(size_t start) {
		return Iterator(this, start);
	}

private:
	Vector<Vertex*>* vertexes; //вершины
	Vector<Edge*>* edgeMatrix; //матрица смежности
};

#endif