#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

template<typename Data>
class Graph {
public:
    Graph(size_t vertex_amount, Data vertex_data) {
        vertexes = new Vector<Vertex*>;
        // Заполнение вершинами
        vertexes->resize(vertex_amount);
        for (size_t i = 0; i < vertex_amount; i++) {
            vertexes->set(i, new Vertex(vertex_data));
        }
        // Создание матрицы смежности
        edgeMatrix = new Vector<Edge*>;
        edgeMatrix->resize(vertex_amount * vertex_amount);

        for (size_t i = 0; i < edgeMatrix->size(); i++) {
            edgeMatrix->set(i, nullptr);
        }

    }
    ~Graph() {
        for (size_t i = 0; i < vertexes->size(); i++) {
            delete vertexes->get(i);
        }
        for (size_t i = 0; i < edgeMatrix->size(); i++) {
            delete edgeMatrix->get(i);
        }
        delete vertexes;
        delete edgeMatrix;
    }
    Graph(const Graph& other) {
        // Глубокое копирование вершин
        vertexes = new Vector<Vertex*>;
        vertexes->resize(other.vertexes->size());
        for (size_t i = 0; i < other.vertexes->size(); ++i) {
            vertexes->set(i, new Vertex(other.vertexes->get(i)->getVertexData()));
        }

        // Глубокое копирование матрицы смежности
        edgeMatrix = new Vector<Edge*>;
        edgeMatrix->resize(other.edgeMatrix->size());
        for (size_t i = 0; i < other.edgeMatrix->size(); ++i) {
            Edge* edge = other.edgeMatrix->get(i);
            if (edge) {
                edgeMatrix->set(i, new Edge(edge->getEdgeData()));
            }
            else {
                edgeMatrix->set(i, nullptr);
            }
        }
    }
    Graph& operator=(const Graph& other) {
        if (this == &other) {
            return *this;  // Защита от самоприсваивания
        }

        // Удаление текущих данных
        delete vertexes;
        delete edgeMatrix;

        // Глубокое копирование вершин
        vertexes = new Vector<Vertex*>;
        vertexes->resize(other.vertexes->size());
        for (size_t i = 0; i < other.vertexes->size(); ++i) {
            vertexes->set(i, new Vertex(other.vertexes->get(i)->getVertexData()));
        }

        // Глубокое копирование матрицы смежности
        edgeMatrix = new Vector<Edge*>;
        edgeMatrix->resize(other.edgeMatrix->size());
        for (size_t i = 0; i < other.edgeMatrix->size(); ++i) {
            Edge* edge = other.edgeMatrix->get(i);
            if (edge) {
                edgeMatrix->set(i, new Edge(edge->getEdgeData()));
            }
            else {
                edgeMatrix->set(i, nullptr);
            }
        }

        return *this;
    }
    struct Vertex {
    private:
        Data vertex_data;
    public:
        Vertex(Data vertex_data) {
            this->vertex_data = vertex_data;
        }
        void setVertexData(Data data) {
            this->vertex_data = data;
        }
        Data getVertexData() {
            return vertex_data;
        }
    };

    struct Edge {
    private:
        Data edge_data;
    public:
        Edge(Data data) {
            this->edge_data = data;
        }
        void setEdgeData(Data data) {
            this->edge_data = data;
        }
        Data getEdgeData() {
            return edge_data;
        }
    };

    size_t getVertexAmount() {
        return vertexes->size();
    }

    struct Iterator {
    private:
        Graph* graph;
        size_t start;
        int end = -1;

        int getNearVertexIndex() {
            // Поиск доступной вершины
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
            this->end = getNearVertexIndex();
        }

        Vertex* operator *() {
            if (end != -1) {
                return graph->getVertex(end);
            }
            else {
                return nullptr;
            }
        }

        void operator ++() {
            end = getNearVertexIndex();
        }
    };

    Iterator getIterator(size_t start) {
        return Iterator(this, start);
    }
    size_t addVertex(Data vertex_data) {
        // Добавление вершины
        size_t index = vertexes->size();
        vertexes->resize(index + 1);
        vertexes->set(index, new Vertex(vertex_data));
        // Новое кол-во вершин
        size_t vertex_amount = getVertexAmount();

        // Переопределение матрицы смежности
        Vector<Edge*>* buffMatrix = new Vector<Edge*>;
        buffMatrix->resize(vertex_amount * vertex_amount);
        for (size_t i = 0; i < vertex_amount; i++) {
            for (size_t j = 0; j < vertex_amount; j++) {
                buffMatrix->set((i * vertex_amount) + j, edgeMatrix->get(i * index + j));
            }
        }

        delete edgeMatrix;
        edgeMatrix = buffMatrix;
        return index;
    }
    void removeVertex(size_t index) {
        // Кол-во вершин исходного графа
        size_t _vertex_amount = getVertexAmount();

        if (index >= _vertex_amount) {
            return;
        }

        Vertex* vertex = vertexes->get(index);
        delete vertex;
        for (size_t i = index; i < _vertex_amount - 1; i++) {
            // Смещение вершин в векторе
            vertexes->set(i, vertexes->get(i + 1));
        }
        vertexes->resize(_vertex_amount - 1);

        // Новое кол-во вершин
        size_t vertex_amount = getVertexAmount();
        // Переопределение матрицы смежности
        Vector<Edge*>* buffMatrix = new Vector<Edge*>;
        buffMatrix->resize(vertex_amount * vertex_amount);
        for (size_t i = 0; i < vertex_amount; i++) {
            for (size_t j = 0; j < vertex_amount; j++) {
                Edge* edge = edgeMatrix->get(((i + (i >= index)) * _vertex_amount) + (j + (j >= index)));
                buffMatrix->set((i * vertex_amount) + j, edge);
            }
        }
        delete edgeMatrix;
        edgeMatrix = buffMatrix;
    }
    Vertex* getVertex(size_t index) {
        return vertexes->get(index);
    }

    void addEdge(size_t start_vertex_index, size_t end_vertex_index, Data edge_data) {
        size_t vertex_amount = getVertexAmount();
        size_t index = start_vertex_index * vertex_amount + end_vertex_index;
        if (edgeMatrix->get(index)) {  // Check if there's already an edge
            delete edgeMatrix->get(index);  // Delete the existing edge
        }
        Edge* edge = new Edge(edge_data);
        edgeMatrix->set(index, edge);  // Set the new edge
    }

    void removeEdge(size_t start_vertex_index, size_t end_vertex_index) {
        size_t vertex_amount = getVertexAmount();
        edgeMatrix->set(start_vertex_index * vertex_amount + end_vertex_index, nullptr);
    }

    Edge* getEdge(size_t start_vertex_index, size_t end_vertex_index) {
        size_t vertex_amount = getVertexAmount();
        return edgeMatrix->get(start_vertex_index * vertex_amount + end_vertex_index);
    }

    bool isEdgeExist(size_t start_vertex_index, size_t end_vertex_index) {
        return getEdge(start_vertex_index, end_vertex_index) != nullptr;
    }
private:
    Vector<Vertex*>* vertexes;
    Vector<Edge*>* edgeMatrix;
};

#endif