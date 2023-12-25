#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

template<typename Data>
class Graph {
public:
   Graph(size_t vertex_amount, Data vertex_data) : vertexes(), edgeMatrix() {
        // Заполнение вершинами
        vertexes.resize(vertex_amount);
        for (size_t i = 0; i < vertex_amount; i++) {
            vertexes.set(i, Vertex(vertex_data));
        }

        // Создание матрицы смежности
        edgeMatrix.resize(vertex_amount * vertex_amount);

        // Заполнение матрицы смежности указателями на Edge (nullptr для отсутствующих ребер)
        for (size_t i = 0; i < edgeMatrix.size(); i++) {
            edgeMatrix.set(i, nullptr);
        }
    }

    ~Graph() {
        // Используем деструктор Vector для удаления объектов Edge
        for (size_t i = 0; i < edgeMatrix.size(); i++) {
            delete edgeMatrix.get(i);
        }
    }

    Graph(const Graph& other) : vertexes(), edgeMatrix() {
        *this = other;
    }

    Graph& operator=(const Graph& other) {
        if (this == &other) {
            return *this;
        }

        // Освобождаем память от существующих объектов Edge
        for (size_t i = 0; i < edgeMatrix.size(); i++) {
            delete edgeMatrix.get(i);
        }

        // Создаем временные копии объектов
        Vector<Vertex> tempVertices = other.vertexes;
        Vector<Edge> tempEdgeMatrix = other.edgeMatrix;

        // Используем swap для обмена данными между объектами Vector
        vertexes.swap(tempVertices);
        edgeMatrix.swap(tempEdgeMatrix);

        return *this;
    }


    struct Vertex {
private:
    Data vertex_data;

public:
    Vertex() : vertex_data(Data()) {}

    void setVertexData(Data data) {
        this->vertex_data = data;
    }

    Data getVertexData() const {
        return vertex_data;
    }
    
    
};

struct Edge {
private:
    Data edge_data;

public:
    Edge() : edge_data() {}

    void setEdgeData(Data data) {
        this->edge_data = data;
    }

    Data getEdgeData() const {
        return edge_data;
    }

    void destroy() {
        delete this;
    }
};

size_t getVertexAmount() const {
    return vertexes.size();
}

    // Вложенная структура Iterator для обхода вершин графа(не используется)
struct Iterator {
        private:
            Graph* graph;  // Указатель на граф
            size_t start;  // Индекс начальной вершины
            size_t end;  // Индекс следующей смежной вершины

            // метод для поиска индекса ближайшей вершины, смежной с текущей
            size_t getNearVertexIndex() {
                for (size_t i = end + 1; i < graph->getVertexAmount(); i++) {
                    if (graph->isEdgeExist(start, i)) {
                        return i;
                    }
                }
                return graph->getVertexAmount();  // Return invalid index
            }

        public:
            // Конструктор итератора
            Iterator(Graph* graph, size_t start) : graph(graph), start(start), end(getNearVertexIndex()) {}

            // Оператор разыменования
            size_t operator *() {
                return end != graph->getVertexAmount() ? end : static_cast<size_t>(-1);
            }

            // Префиксный оператор инкремента для перехода к следующей смежной вершине
            void operator ++() {
                end = getNearVertexIndex();
            }
        };

    Iterator getIterator(size_t start) {
        return Iterator(this, start);
    }

size_t addVertex(Data vertex_data) {
    size_t index = vertexes.size();
    vertexes.resize(index + 1);
    vertexes.set(index, Vertex(vertex_data));

    size_t vertex_amount = getVertexAmount();

    Vector<Edge> buffMatrix;
    buffMatrix.resize(vertex_amount * vertex_amount);
    for (size_t i = 0; i < vertex_amount; i++) {
        for (size_t j = 0; j < vertex_amount; j++) {
            buffMatrix.set((i * vertex_amount) + j, edgeMatrix.get(i * index + j));
        }
    }

    edgeMatrix.swap(buffMatrix);


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


    edgeMatrix.swap(buffMatrix);

}

    Vertex* getVertex(size_t index) {
        return vertexes.get(index);
    }

    void addEdge(size_t start_vertex_index, size_t end_vertex_index, Data edge_data) {
    size_t vertex_amount = getVertexAmount();

    Edge* existingEdge = edgeMatrix.get(start_vertex_index * vertex_amount + end_vertex_index);

    if (existingEdge == nullptr) {
        Edge* newEdge = new Edge(edge_data);
        edgeMatrix.set(start_vertex_index * vertex_amount + end_vertex_index, *newEdge);
    }
    else {
        existingEdge->setEdgeData(edge_data);
    }
}

    void removeEdge(size_t start_vertex_index, size_t end_vertex_index) {
        size_t vertex_amount = getVertexAmount();
        Edge* edge = edgeMatrix.get(start_vertex_index * vertex_amount + end_vertex_index);
        delete edge;
        edgeMatrix.set(start_vertex_index * vertex_amount + end_vertex_index, nullptr);
    }

    Edge* getEdge(size_t start_vertex_index, size_t end_vertex_index) {
    size_t vertex_amount = getVertexAmount();
    return edgeMatrix.get(start_vertex_index * vertex_amount + end_vertex_index);
}


    bool isEdgeExist(size_t start_vertex_index, size_t end_vertex_index) {
        return getEdge(start_vertex_index, end_vertex_index) != nullptr;
    }
private:
    Vector<Vertex> vertexes;
    Vector<Edge*> edgeMatrix;
};

#endif