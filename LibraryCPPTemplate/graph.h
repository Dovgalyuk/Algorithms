#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"
#include <string>
#include <limits>
#include <stdexcept>

template <typename EdgeData = int, typename VertexData = std::string>
class Graph {
public:
    struct Edge {
        bool exists;
        EdgeData data;
        
        Edge() : exists(false), data() {}
        Edge(bool e, const EdgeData& d) : exists(e), data(d) {}
    };

    Graph(size_t vertexCount = 0) {
        if (vertexCount > 1000) {
            throw std::out_of_range("Too many vertices");
        }
        verticesData.resize(vertexCount);
        adjacencyMatrix.resize(vertexCount);
        for (size_t i = 0; i < vertexCount; ++i) {
            adjacencyMatrix.set(i, Vector<Edge>());
            adjacencyMatrix.get(i).resize(vertexCount);
            for (size_t j = 0; j < vertexCount; ++j) {
                adjacencyMatrix.get(i).set(j, Edge(false, EdgeData()));
            }
        }
    }

    void setEdgeData(size_t from, size_t to, const EdgeData& data) {
        checkVertexIndex(from);
        checkVertexIndex(to);
        adjacencyMatrix.get(from).set(to, Edge(true, data));
    }

    size_t vertexCount() const {
        return verticesData.size();
    }

    size_t addVertex() {
        size_t newIndex = vertexCount();
        
        adjacencyMatrix.resize(newIndex + 1);
        adjacencyMatrix.set(newIndex, Vector<Edge>());
        adjacencyMatrix.get(newIndex).resize(newIndex + 1);
        
        for (size_t j = 0; j <= newIndex; ++j) {
            adjacencyMatrix.get(newIndex).set(j, Edge(false, EdgeData()));
        }
        
        for (size_t i = 0; i < newIndex; ++i) {
            adjacencyMatrix.get(i).resize(newIndex + 1);
            adjacencyMatrix.get(i).set(newIndex, Edge(false, EdgeData()));
        }
        
        verticesData.resize(newIndex + 1);
        return newIndex;
    }

    void addEdge(size_t from, size_t to) {
        if (from >= vertexCount() || to >= vertexCount()) {
            throw std::out_of_range("Vertex index out of range in addEdge");
        }
        adjacencyMatrix.get(from).set(to, Edge(true, EdgeData()));
    }

    void removeVertex(size_t vertex) {
        if (vertex >= vertexCount()) return;
        
        for (size_t i = vertex; i < vertexCount() - 1; ++i) {
            adjacencyMatrix.set(i, adjacencyMatrix.get(i + 1));
        }
        adjacencyMatrix.resize(vertexCount() - 1);
        
        for (size_t i = 0; i < vertexCount(); ++i) {
            Vector<Edge> row = adjacencyMatrix.get(i);
            for (size_t j = vertex; j < vertexCount() - 1; ++j) {
                row.set(j, row.get(j + 1));
            }
            row.resize(vertexCount() - 1);
            adjacencyMatrix.set(i, row);
        }
        
        for (size_t i = vertex; i < vertexCount() - 1; ++i) {
            verticesData.set(i, verticesData.get(i + 1));
        }
        verticesData.resize(vertexCount() - 1);
    }

    void removeEdge(size_t from, size_t to) {
        if (from >= vertexCount() || to >= vertexCount()) return;
        adjacencyMatrix.get(from).set(to, Edge{false, EdgeData()});
    }

    bool hasEdge(size_t from, size_t to) const {
        if (from >= vertexCount() || to >= vertexCount()) return false;
        return adjacencyMatrix.get(from).get(to).exists;
    }

    EdgeData getEdgeData(size_t from, size_t to) const {
        if (from >= vertexCount() || to >= vertexCount()) return EdgeData();
        return adjacencyMatrix.get(from).get(to).data;
    }

    void setVertexData(size_t vertex, const VertexData& data) {
        if (vertex >= vertexCount()) return;
        verticesData.set(vertex, data);
    }

    VertexData getVertexData(size_t vertex) const {
        if (vertex >= vertexCount()) return VertexData();
        return verticesData.get(vertex);
    }

    Vector<VertexData> getAllVertexData() const {
        return verticesData;
    }

    class NeighborIterator {
    public:
        NeighborIterator(const Graph* graph, size_t vertex, size_t index)
            : graph(graph), vertex(vertex), index(index) {
            while (this->index < graph->vertexCount() && 
                   !graph->hasEdge(vertex, this->index)) {
                ++this->index;
            }
        }

        bool operator!=(const NeighborIterator& other) const {
            return index != other.index;
        }

        NeighborIterator& operator++() {
            do {
                ++index;
            } while (index < graph->vertexCount() && !graph->hasEdge(vertex, index));
            return *this;
        }

        size_t operator*() const {
            return index;
        }

    private:
        const Graph* graph;
        size_t vertex;
        size_t index;
    };

    NeighborIterator beginNeighbors(size_t vertex) const {
        return NeighborIterator(this, vertex, 0);
    }

    NeighborIterator endNeighbors(size_t vertex) const {
        return NeighborIterator(this, vertex, vertexCount());
    }
private:
    void checkVertexIndex(size_t index) const {
        if (index >= vertexCount()) {
            throw std::out_of_range("Vertex index out of range");
        }
    }

    Vector<Vector<Edge>> adjacencyMatrix;
    Vector<VertexData> verticesData;
};

#endif 
