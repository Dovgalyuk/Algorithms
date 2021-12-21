#pragma once

#include "vector.h"
#include "iostream"

template <typename VertexData, typename EdgeData>
class Graph {
public:
    Graph(size_t vertex_amount, VertexData default_value) {
        edgeMatrix = new Vector<Edge*>;
        vertices = new Vector<Vertex*>;
        vertices->resize(vertex_amount);
        for (int i = 0; i < vertex_amount; i++) {
            vertices->set(i, new Vertex(default_value));
        }
        edgeMatrix->resize(vertex_amount * vertex_amount);
        for (int i = 0; i < edgeMatrix->size(); ++i) {
            edgeMatrix->set(i, nullptr);
        }
    }

    ~Graph() {
        delete edgeMatrix;
        delete vertices;
    }
    struct Vertex {
        VertexData data;
        Vertex(VertexData data_)
        {
            this->data = data_;
        }
    };

    struct Edge {
        Vertex* first;
        Vertex* second;
        EdgeData data2;
        Edge(Vertex* first_, Vertex* second_){
        first = first_;
        second = second_;
        }
    };

    void setDataEdge(Edge* edge, EdgeData data2_){
        edge->data2 = data2_;
    }

    EdgeData getDataEdge(Edge* edge) {
        return edge->data2;
    }

    struct VertexIterator {
        Graph* graph = nullptr;
        size_t mainVertex = 0;
        int lastIndex = -1;

        VertexIterator(Graph* graph_, size_t mainVertex_){
            graph = graph_;
            mainVertex = mainVertex_;
            lastIndex = nearVertexIndex();
        }

        Vertex* operator *() {
            return lastIndex != -1 ? graph->getVertex(lastIndex) : nullptr;
        }

        size_t getIndex() {
            return lastIndex;
        }



        void operator ++(int i) {
            lastIndex = nearVertexIndex();
        }

        int nearVertexIndex() {
            for (int i = lastIndex + 1; i < graph->getVertexAmount(); ++i) {
                if (graph->containsEdge(mainVertex, i)) {
                    return i;
                }
            }
            return -1;
        }
    };

    VertexIterator getIterator(size_t mainIndex) {
        return VertexIterator(this, mainIndex);
    }

    size_t addVertex(VertexData data) {
        Vertex* vertex = new Vertex(data);
        size_t index = vertices->size();
        vertices->resize(index + 1);
        vertices->set(index, vertex);
        addVertex2(index);
        return index;
    }

    size_t addVertex(Vertex* vertex) {
        size_t index = vertices->size();
        vertices->resize(index + 1);
        vertices->set(index, vertex);
        addVertex2(index);
        return index;
    }

    void removeVertex(size_t index) {
        if (index >= vertices->size()) {
             return;
        }
        int size = vertices->size();
        for (int i = 0; i < size - 1; ++i) {
            vertices->set(i, vertices->get(i + (i >= index)));
        }
        vertices->resize(size - 1);

    
        int vertexAmount = getVertexAmount();
        Vector<Edge*>* newMatrix = new Vector<Edge*>;
        newMatrix->resize(vertexAmount * vertexAmount);
        for (int i = 0; i < vertexAmount; ++i) {
            for (int j = 0; j < vertexAmount; ++j) {
                Edge* edge = edgeMatrix->get(((i + (i >= index)) * size) + (j + (j >= index)));
                newMatrix->set((i * vertexAmount) + j, edge);
            }
        }
        delete edgeMatrix;
        edgeMatrix = newMatrix;
    }

    Vertex* getVertex(size_t index) {
        return vertices->get(index);
    }

    VertexData getData(size_t index) {
        return vertices->get(index)->data;
    }

    size_t getVertexAmount() {
        return vertices->size();
    }

    void set_vertex(size_t index, VertexData data) {
        set_vertex(index, new Vertex(data));
    }

    void set_vertex(size_t index, Vertex* vertex) {
        if (index >= vertices->size()) return;
        vertices->set(index, vertex);
    }

    void setVertexData(size_t index, VertexData data_) {
        vertices->get(index)->data = data_;
    }

    void addEdge(size_t from_vertex_index, size_t to_vertex_index) {
        Edge* edge = new Edge(getVertex(from_vertex_index), getVertex(to_vertex_index));
        edgeMatrix->set(from_vertex_index * getVertexAmount() + to_vertex_index, edge);
    }

    void removeEdge(size_t from_vertex_index, size_t to_vertex_index) {
        edgeMatrix->set(from_vertex_index * getVertexAmount() + to_vertex_index, nullptr);
    }

    Edge* getEdge(size_t from_vertex_index, size_t to_vertex_index) {
        return edgeMatrix->get(from_vertex_index * getVertexAmount() + to_vertex_index);
    }

    bool containsEdge(size_t from_vertex_index, size_t to_vertex_index) {
        Edge* edge = edgeMatrix->get(from_vertex_index * getVertexAmount() + to_vertex_index);
        return edge != nullptr;
    }

    

private:

    void addVertex2(int newAmount) {
        Vector<Edge*>* newMatrix = new Vector<Edge*>;
        int vertexAmount = getVertexAmount();
        newMatrix->resize(vertexAmount * vertexAmount);
        for (int i = 0; i < vertexAmount; ++i) {
            for (int j = 0; j < vertexAmount; ++j) {
                newMatrix->set((i * vertexAmount) + j, edgeMatrix->get(i * newAmount + j));
            }
        }
        delete edgeMatrix;
        edgeMatrix = newMatrix;
    }

    Vector<Vertex*>* vertices;
    Vector<Edge*>* edgeMatrix;
};
