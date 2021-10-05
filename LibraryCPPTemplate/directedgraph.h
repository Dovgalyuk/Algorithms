//
// Created by KirilliriK on 04.10.2021.
//

#ifndef ALGORITHMS_DIRECTEDGRAPH_H
#define ALGORITHMS_DIRECTEDGRAPH_H

#include <iostream>
#include <vector>
#include "array.h"


template <typename Data>
class DirectedGraph {
public:
    struct Vertex {
        Data data;
        Vertex(Data data) {
            this->data = data;
        }
    };

    struct Edge {
        size_t cost;
        Edge() {
            cost = 0;
        }
        Edge(size_t cost) {
            this->cost = cost;
        }
    };

    class Iterator {
    public:
        Iterator &next() {
            for (int i = current + 1; i < graph.vertexCount; i++) {
                current = -1;
                if (!graph.containsVertex(i)) continue;
                current = i;
                break;
            }
            return *this;
        }

        bool hasNext() {
            for (int i = current + 1; i < graph.vertexCount; i++) {
                if (!graph.containsVertex(i)) continue;
                return true;
            }
            return false;
        }

        Iterator(DirectedGraph<Data> &_graph) : graph(_graph) { }

        Iterator(DirectedGraph<Data> &_graph, int current) : graph(_graph) {
            this->current = current;
        }

        Vertex* operator *() {
            return graph.vertices->get(current);
        }

        Iterator& operator ++() {
            return next();
        }

        Iterator operator ++(int) {
            next();
            Iterator it(graph, current);
            return it;
        }
    private:
        DirectedGraph<Data> &graph;
        int current = -1;
    };

    Iterator getIterator() {
        return Iterator(*this);
    }

    typedef Array<Edge> MatrixArray;
    typedef Array<Vertex*> VertexArray;

    DirectedGraph(size_t vertexCount) {
        this->vertexCount = vertexCount;
        size_t size = vertexCount * vertexCount;
        matrix = new MatrixArray(size);
        vertices = new VertexArray(vertexCount);
        for (int i = 0; i < vertices->size(); i++) {
            vertices->set(i, nullptr);
        }
    }

    ~DirectedGraph() {
        delete matrix;
        for (int i = 0; i < vertices->size(); i++) {
            delete vertices->get(i);
        }
        delete vertices;
    }

    void addVertex(size_t index, Data data) {
        if (containsVertex(index)) {
            removeVertex(index);
        }
        vertices->set(index, new Vertex(data));
    }

    void setEdge(size_t firstIndex, size_t secondIndex, size_t cost) {
        matrix->set(firstIndex + secondIndex * vertexCount, Edge(cost));
    }

    void removeVertex(size_t index) {
        if (!containsVertex(index)) {
            std::cout << "Trying remove null vertex" << std::endl;
            exit(-1);
        }

        for (size_t i = 0; i < vertexCount; i++) {
            matrix->set(getIndex(i, index), Edge(0));
            matrix->set(getIndex(index, i), Edge(0));
        }
        delete vertices->get(index);
        vertices->set(index, nullptr);
    }

    void removeEdge(size_t firstIndex, size_t secondIndex) {
        matrix->set(getIndex(firstIndex, secondIndex), Edge(0));
    }

    bool isLinked(size_t firstIndex, size_t secondIndex) {
        return matrix->get(getIndex(firstIndex, secondIndex)).cost != 0;
    }

    bool containsVertex(size_t index) {
        return vertices->get(index) != nullptr;
    }

    size_t getEdgeCost(size_t firstIndex, size_t secondIndex) {
        return matrix->get(getIndex(firstIndex, secondIndex)).cost;
    }

    // Return index vector with next Vertex
    std::vector<int> *getLinkedVertices(size_t index) {
        auto edges = new std::vector<int>;
        for (int i = 0; i < vertexCount; i++) {
            if (matrix->get(getIndex(index, i)).cost == 0) continue;
            edges->push_back(i);
        }
        return edges;
    }

    // @Debug method
    void displayMatrix() {
        std::cout << std::endl;
        std::cout << " /";
        for (int i = 0; i < vertexCount; i++)
            std::cout << i;
        std::cout << std::endl;
        for (int i = 0; i < vertexCount; i++) {
            std::cout << i << "|";
            for (int j = 0; j < vertexCount; j++) {
                if (matrix->get(getIndex(i, j)).cost != 0) std::cout << 1;
                else std::cout << 0;
            }
            std::cout << std::endl;
        }
    }
private:
    inline int getIndex(const int first, const int second) {
        return first + second * vertexCount;
    }
    MatrixArray *matrix;
    VertexArray *vertices;
    size_t vertexCount;
};


#endif //ALGORITHMS_DIRECTEDGRAPH_H
