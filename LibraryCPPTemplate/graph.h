#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <istream>
#include "vector.h"

template <typename VertexData, typename EdgeData> class Graph {
private:
    struct Edge {
        bool exists = false;
        EdgeData data = EdgeData();
    };

    Vector<VertexData> vertices;
    Vector<Edge> matrix;

public:
    class NeighborIterator {
    public:
        NeighborIterator(const Graph* g, size_t v, size_t pos) : graph(g), vertex(v), index(pos) {
            advanceToValid();
        }

        size_t operator*() const {
            return index;
        }

        NeighborIterator& operator++() {
            index++;
            advanceToValid();
            return *this;
        }

        bool operator!=(const NeighborIterator& other) const {
            return index != other.index || vertex != other.vertex || graph != other.graph;
        }

        bool operator==(const NeighborIterator& other) const {
            return !(*this != other);
        }

    private:
        const Graph* graph;
        size_t vertex;
        size_t index;

        void advanceToValid() {
            while (index < graph->vertexCount() && !graph->hasEdge(vertex, index)) index++;
        }
    };

    Graph(size_t count = 0) {
        vertices.resize(count);
        matrix.resize(count * count);
    }

    size_t vertexCount() const {
        return vertices.size();
    }

    size_t addVertex(const VertexData& data = VertexData()) {
        size_t oldN = vertices.size();
        size_t newN = oldN + 1;
        vertices.resize(newN);
        vertices.set(oldN, data);
        Vector<Edge> newMatrix;
        newMatrix.resize(newN * newN);
        for (size_t i = 0; i < oldN; i++) {
            for (size_t j = 0; j < oldN; j++) {
                newMatrix.set(i * newN + j, matrix.get(i * oldN + j));
            }
        }
        matrix = newMatrix;
        return oldN;
    }

    void removeVertex(size_t index) {
        size_t oldN = vertices.size();
        if (index >= oldN) return;
        size_t newN = oldN - 1;
        for (size_t i = index; i < newN; i++) vertices.set(i, vertices.get(i + 1));
        vertices.resize(newN);
        Vector<Edge> newMatrix;
        newMatrix.resize(newN * newN);
        size_t ni = 0;
        for (size_t i = 0; i < oldN; i++) {
            if (i == index) continue;
            size_t nj = 0;
            for (size_t j = 0; j < oldN; j++) {
                if (j == index) continue;
                newMatrix.set(ni * newN + nj, matrix.get(i * oldN + j));
                nj++;
            }
            ni++;
        }
        matrix = newMatrix;
    }

    void addEdge(size_t from, size_t to, const EdgeData& data = EdgeData()) {
        size_t n = vertices.size();
        if (from >= n || to >= n) return;
        Edge e;
        e.exists = true;
        e.data = data;
        matrix.set(from * n + to, e);
    }

    void removeEdge(size_t from, size_t to) {
        size_t n = vertices.size();
        if (from >= n || to >= n) return;
        Edge e;
        e.exists = false;
        matrix.set(from * n + to, e);
    }

    bool hasEdge(size_t from, size_t to) const {
        size_t n = vertices.size();
        if (from >= n || to >= n) return false;
        return matrix.get(from * n + to).exists;
    }

    void setEdgeData(size_t from, size_t to, const EdgeData& data) {
        size_t n = vertices.size();
        if (from >= n || to >= n) return;
        Edge e = matrix.get(from * n + to);
        e.exists = true;
        e.data = data;
        matrix.set(from * n + to, e);
    }

    EdgeData getEdgeData(size_t from, size_t to) const {
        size_t n = vertices.size();
        if (from >= n || to >= n) return EdgeData();
        return matrix.get(from * n + to).data;
    }

    void setVertexData(size_t index, const VertexData& data) {
        if (index < vertices.size()) vertices.set(index, data);
    }

    VertexData getVertexData(size_t index) const {
        if (index < vertices.size()) return vertices.get(index);
        return VertexData();
    }

    size_t findVertex(const VertexData& data) const {
        for (size_t i = 0; i < vertices.size(); i++) {
            if (vertices.get(i) == data) return i;
        }
        return vertices.size();
    }

    void read(std::istream& in) {
        size_t vCount = 0;
        size_t eCount = 0;
        if (!(in >> vCount >> eCount)) return;
        vertices.resize(vCount);
        matrix.resize(vCount * vCount);
        for (size_t i = 0; i < vCount * vCount; i++) matrix.set(i, Edge());
        for (size_t i = 0; i < vCount; i++) {
            VertexData label;
            in >> label;
            vertices.set(i, label);
        }
        for (size_t i = 0; i < eCount; i++) {
            VertexData fromLabel;
            VertexData toLabel;
            EdgeData edgeLabel;
            in >> fromLabel >> toLabel >> edgeLabel;
            size_t fromIdx = findVertex(fromLabel);
            size_t toIdx = findVertex(toLabel);
            if (fromIdx < vCount && toIdx < vCount) addEdge(fromIdx, toIdx, edgeLabel);
        }
    }

    NeighborIterator neighborsBegin(size_t vertex) const {
        return NeighborIterator(this, vertex, 0);
    }

    NeighborIterator neighborsEnd(size_t vertex) const {
        return NeighborIterator(this, vertex, vertices.size());
    }
};

#endif
