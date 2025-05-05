#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

template<typename Data>
class Graph {
public:
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

    ~Graph() {
        for (size_t i = 0; i < edgeMatrix.size(); i++) {
            delete edgeMatrix.get(i);
        }
    }

    Graph(const Graph& a) {
        vertexes = a.vertexes;
        Vector<Edge*> tempEdgeMatrix = a.edgeMatrix;
        edgeMatrix.swap(tempEdgeMatrix);
    }

    Graph& operator=(const Graph& other) {
        if (this == &other) {
            return *this;
        }

        for (size_t i = 0; i < edgeMatrix.size(); i++) {
            delete edgeMatrix.get(i);
        }

        Vector<Vertex> tempVertices = other.vertexes;
        Vector<Edge*> tempEdgeMatrix = other.edgeMatrix;
        vertexes.swap(tempVertices);
        edgeMatrix.swap(tempEdgeMatrix);

        return *this;
    }

    struct Vertex {
    private:
        Data vertexData;

    public:
        Vertex() : vertexData(Data()) {}

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

    size_t getVertexAmount() const {
        return vertexes.size();
    }

    struct Iterator {
    private:
        Graph* graph;
        size_t start;
        int end = -1;

        size_t getNearVertexIndex() {
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

        bool operator*() {
            return end != -1;
        }

        void operator++() {
            end = getNearVertexIndex();
        }

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

    size_t addVertex(Data vertex_data) {
        size_t index = vertexes.size();
        vertexes.resize(index + 1);
        vertexes.set(index, Vertex(vertex_data));

        size_t vertex_amount = getVertexAmount();

        Vector<Edge*> buffMatrix;
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

    Vertex getVertex(size_t index) {
        return vertexes.get(index);
    }

    void addEdge(size_t start_vertex_index, size_t end_vertex_index, Data edge_data) {
        if (start_vertex_index >= getVertexAmount() || end_vertex_index >= getVertexAmount()) {
            std::cerr << "Invalid vertex indices!" << std::endl;
            return;
        }
    
        size_t vertex_amount = getVertexAmount();
        Edge* existingEdge = edgeMatrix.get(start_vertex_index * vertex_amount + end_vertex_index);
    
        if (existingEdge == nullptr) {
            Edge* newEdge = new Edge(edge_data);
            edgeMatrix.set(start_vertex_index * vertex_amount + end_vertex_index, newEdge);
        }
        else {
            existingEdge->setEdgeData(edge_data);
        }
    }
    

    void removeEdge(size_t start_vertex_index, size_t end_vertex_index) {
        size_t vertex_amount = getVertexAmount();
        Edge* edge = edgeMatrix.get(start_vertex_index * vertex_amount + end_vertex_index);
        if (edge) {
            delete edge;
            edgeMatrix.set(start_vertex_index * vertex_amount + end_vertex_index, nullptr);
        }
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
