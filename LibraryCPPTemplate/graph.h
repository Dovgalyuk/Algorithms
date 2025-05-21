
#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"
#include <stdexcept>
#include <iostream>

template <typename V, typename E>
class Graph {
private:
    struct EdgeCell {
        bool exists;
        E label;

        EdgeCell() : exists(false), label(E()) {}
        EdgeCell(const E& l) : exists(true), label(l) {}
    };

    Vector<V> vertexLabels;
    Vector<Vector<EdgeCell>> adjMatrix;

    void checkIndex(size_t index) const {
        if (index >= vertexLabels.size()) {
            throw std::out_of_range("Index out of range");
        }
    }

public:
    Graph(size_t vertexCount = 0) {
        vertexLabels.resize(vertexCount);
        adjMatrix.resize(vertexCount);
        for (size_t i = 0; i < vertexCount; ++i) {
            adjMatrix[i].resize(vertexCount);
        }
    }

    size_t addVertex(const V& label) {
        size_t index = vertexLabels.size();
        vertexLabels.push_back(label);
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            adjMatrix[i].push_back(EdgeCell());
        }

        Vector<EdgeCell> newRow(vertexLabels.size());
        adjMatrix.push_back(newRow);
        return index;
    }

    void removeVertex(size_t index) {
        checkIndex(index);
        vertexLabels.erase(index);
        adjMatrix.erase(index);
        for (size_t i = 0; i < adjMatrix.size(); ++i) {
            adjMatrix[i].erase(index);
        }
    }

    void addEdge(size_t from, size_t to, const E& label) {
        checkIndex(from);
        checkIndex(to);
        adjMatrix[from][to] = EdgeCell(label);
        std::cout << "Edge added from " << from << " to " << to << " with label " << label << std::endl;
    }

    void removeEdge(size_t from, size_t to) {
        checkIndex(from);
        checkIndex(to);
        adjMatrix[from][to] = EdgeCell();
    }

    bool hasEdge(size_t from, size_t to) const {
        checkIndex(from);
        checkIndex(to);
        return adjMatrix[from][to].exists;
    }

    void setVertexLabel(size_t index, const V& label) {
        checkIndex(index);
        vertexLabels[index] = label;
    }

    V getVertexLabel(size_t index) const {
        checkIndex(index);
        return vertexLabels[index];
    }

    void setEdgeLabel(size_t from, size_t to, const E& label) {
        checkIndex(from);
        checkIndex(to);
        if (!adjMatrix[from][to].exists) throw std::runtime_error("Edge does not exist");
        adjMatrix[from][to].label = label;
    }

    E getEdgeLabel(size_t from, size_t to) const {
        checkIndex(from);
        checkIndex(to);
        if (!adjMatrix[from][to].exists) throw std::runtime_error("Edge does not exist");
        return adjMatrix[from][to].label;
    }

    Vector<V> getAllVertexLabels() const {
        return vertexLabels;
    }

    size_t getVertexCount() const {
        return vertexLabels.size();
    }

    class Iterator {
    private:
        const Graph& graph;
        size_t vertex;
        size_t idx;

    public:
        Iterator(const Graph& g, size_t v) : graph(g), vertex(v), idx(0) {
            while (idx < graph.getVertexCount() && !graph.hasEdge(vertex, idx)) {
                ++idx;
            }
        }

        bool hasNext() const {
            return idx < graph.getVertexCount();
        }

        size_t next() {
            if (!hasNext()) throw std::out_of_range("No more edges");
            size_t current = idx++;
            while (idx < graph.getVertexCount() && !graph.hasEdge(vertex, idx)) {
                ++idx;
            }
            return current;
        }
    };

    Iterator getIterator(size_t vertex) const {
        checkIndex(vertex);
        return Iterator(*this, vertex);
    }
};

#endif
