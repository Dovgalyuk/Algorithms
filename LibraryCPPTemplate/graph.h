#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

template<typename VertexData, typename EdgeData>
class Graph {
public:
	struct Vertex {
	private:
		VertexData vertexData;

	public:
		Vertex() : vertexData(VertexData()) {}

		Vertex(VertexData data) {
			this->vertexData = data;
		}

		void setVertexData(VertexData data) {
			this->vertexData = data;
		}

		VertexData getVertexData() {
			return this->vertexData;
		}
	};

	struct Edge {
	private:
		EdgeData edgeData;

	public:
		Edge(EdgeData data) {
			this->edgeData = data;
		}

		void setEdgeData(EdgeData data) {
			this->edgeData = data;
		}

		EdgeData getEdgeData() {
			return edgeData;
		}
	};
	//конструктор графа
	Graph(size_t vertexAmount) {
		vertexes.resize(vertexAmount);
		for (size_t i = 0; i < vertexAmount; i++) {
			vertexes.set(i, Vertex(static_cast<int>(i)));
		}
		edgeMatrix.resize(vertexAmount * vertexAmount);
		for (size_t i = 0; i < edgeMatrix.size(); i++) {
			edgeMatrix.set(i, nullptr);
		}
	}
	//деструктор графа
	~Graph() {
		for (size_t i = 0; i < edgeMatrix.size(); i++) {
			delete edgeMatrix.get(i);
		}
	}

	//конструктор копирования
	Graph(const Graph& a) {
		// Копирование вершин
		vertexes = a.vertexes;

		// Глубокое копирование рёбер
		edgeMatrix.resize(a.edgeMatrix.size());
		for (size_t i = 0; i < a.edgeMatrix.size(); i++) {
			if (a.edgeMatrix.get(i) != nullptr) {
				edgeMatrix.set(i, new Edge(a.edgeMatrix.get(i)->getEdgeData()));
			}
			else {
				edgeMatrix.set(i, nullptr);
			}
		}
	}

	Graph& operator=(const Graph& a) {
		if (this != &a) {
			if (edgeMatrix) {
				for (size_t i = 0; i < edgeMatrix.size(); i++) {
					delete edgeMatrix.get(i);
				}
			}
			vertexes.resize(a.vertexes.size());
			for (size_t i = 0; i < vertexes.size(); i++) {
				vertexes.set(i, Vertex(a.vertexes.get(i)));
			}

			edgeMatrix.resize(a.edgeMatrix.size());
			for (size_t i = 0; i < edgeMatrix.size(); i++) {
				Edge* edge = a.edgeMatrix.get(i);
				edgeMatrix.set(i, new Edge(*(edge)));
			}
		}
		return *this;
	}

	size_t getVertexAmount() {
		return vertexes.size();
	}

	size_t addVertex(VertexData vertexData) {
		size_t index = vertexes.size();
		vertexes.resize(index + 1);
		vertexes.set(index, Vertex(vertexData));

		size_t vertexAmount = getVertexAmount();
		Vector<Edge*> buffMatrix;
		buffMatrix.resize(vertexAmount * vertexAmount);
		for (size_t i = 0; i < index; i++) {
			for (size_t j = 0; j < index; j++) {
				buffMatrix.set((i * vertexAmount) + j, edgeMatrix.get(i * index + j));
			}
		}

		for (size_t i = 0; i < edgeMatrix.size(); i++) {
			if (edgeMatrix.get(i)) {
				delete edgeMatrix.get(i);
			}
		}

		edgeMatrix = buffMatrix;
		return index;
	}

	void removeVertex(size_t index) {
		size_t _vertexAmount = getVertexAmount();

		if (index >= _vertexAmount) {
			return;
		}

		for (size_t i = index; i < _vertexAmount - 1; i++) {
			vertexes.set(i, vertexes.get(i + 1));
		}
		vertexes.resize(_vertexAmount - 1);

		for (size_t i = 0; i < _vertexAmount; i++) {
			Edge* edge = edgeMatrix.get(index * _vertexAmount + i);
			if (edge) {
				delete edge;
			}
			edge = edgeMatrix.get(i * _vertexAmount + index);
			if (edge) {
				delete edge;
			}
		}

		size_t vertex_amount = getVertexAmount();
		Vector<Edge*> buffMatrix;
		buffMatrix.resize(vertex_amount * vertex_amount);
		for (size_t i = 0; i < vertex_amount; i++) {
			for (size_t j = 0; j < vertex_amount; j++) {
				Edge* edge = edgeMatrix.get(((i + (i >= index)) * _vertexAmount) + (j + (j >= index)));
				buffMatrix.set((i * vertex_amount) + j, edge);
			}
		}

		edgeMatrix = buffMatrix;
	}

	Vertex getVertex(size_t index) {
		return vertexes.get(index);
	}

	Edge* getEdge(size_t startVertexIndex, size_t endVertexIndex) {
		size_t vertexAmount = getVertexAmount();
		return edgeMatrix.get(startVertexIndex * vertexAmount + endVertexIndex);
	}

	bool isEdgeExist(size_t startVertexIndex, size_t endVertexIndex) {
		return getEdge(startVertexIndex, endVertexIndex) != nullptr;
	}

	void addEdge(size_t startVertexIndex, size_t endVertexIndex, EdgeData edgeData) {
		size_t vertexAmount = getVertexAmount();

		Edge* edge = edgeMatrix.get(startVertexIndex * vertexAmount + endVertexIndex);
		if (edge) {
			edge->setEdgeData(edgeData);
		}
		else {
			Edge* newEdge = new Edge(edgeData);
			edgeMatrix.set(startVertexIndex * vertexAmount + endVertexIndex, newEdge);
		}
	}

	void removeEdge(size_t startVertexIndex, size_t endVertexIndex) {
		size_t vertexAmount = getVertexAmount();
		Edge* edge = edgeMatrix.get(startVertexIndex * vertexAmount + endVertexIndex);
		delete edge;
		edgeMatrix.set(startVertexIndex * vertexAmount + endVertexIndex, nullptr);
	}

	struct Iterator {
	private:
		Graph* graph;
		size_t start;
		size_t end;

		size_t getNearVertex() {
			for (size_t i = end + 1; i < graph->getVertexAmount(); i++) {
				if (graph->isEdgeExist(start, i)) {
					return i;
				}
			}
			return graph->getVertexAmount();
		}

	public:
		Iterator(Graph* graph, size_t start) : graph(graph), start(start), end(start - 1) {
			end = getNearVertex();
		}

		bool operator*() {
			return end != graph->getVertexAmount();
		}

		void operator++() {
			end = getNearVertex();
		}

		size_t getIndex() const {
			return end;
		}

		size_t getStart() const {
			return start;
		}
	};

	Iterator getIterator(size_t start) {
		return Iterator(this, start);
	}

private:
	Vector<Vertex> vertexes;
	Vector<Edge*> edgeMatrix;
};

#endif