[file name]: LibraryCPPTemplate / graph.h
[file content begin]
#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <stdexcept>
#include <cstddef>
#include <iostream>
#include "vector.h"

template<typename VertexLabel = int, typename EdgeLabel = int>
class Digraph {
private:
    Vector<Vector<EdgeLabel>> adjacencyMatrix;
    Vector<VertexLabel> vertexLabels;

    bool isValidVertex(size_t v) const {
        return v < countVertices();
    }

public:
    Digraph() = default;

    explicit Digraph(size_t vertexCount)
        : adjacencyMatrix(vertexCount, Vector<EdgeLabel>(vertexCount, EdgeLabel{}))
        , vertexLabels(vertexCount, VertexLabel{}) {
    }

    Digraph(const Digraph& other) = default;
    Digraph& operator=(const Digraph& other) = default;

    size_t addVertex() {
        size_t oldSize = countVertices();

        for (size_t i = 0; i < oldSize; ++i) {
            adjacencyMatrix[i].push_back(EdgeLabel{});
        }

        Vector<EdgeLabel> newRow(oldSize + 1, EdgeLabel{});
        adjacencyMatrix.push_back(newRow);

        vertexLabels.push_back(VertexLabel{});

        return oldSize;
    }

    bool removeVertex(size_t vertex) {
        if (!isValidVertex(vertex)) {
            return false;
        }

        size_t newSize = countVertices() - 1;
        if (newSize == 0) {
            adjacencyMatrix.resize(0);
            vertexLabels.resize(0);
            return true;
        }

        Vector<Vector<EdgeLabel>> newMatrix(newSize);
        Vector<VertexLabel> newLabels(newSize);

        size_t newRowIndex = 0;
        for (size_t i = 0; i < countVertices(); ++i) {
            if (i == vertex) continue;

            Vector<EdgeLabel> newRow(newSize);
            size_t newColIndex = 0;

            for (size_t j = 0; j < countVertices(); ++j) {
                if (j == vertex) continue;
                newRow[newColIndex] = adjacencyMatrix[i][j];
                ++newColIndex;
            }

            newMatrix[newRowIndex] = newRow;
            newLabels[newRowIndex] = vertexLabels[i];
            ++newRowIndex;
        }

        adjacencyMatrix = newMatrix;
        vertexLabels = newLabels;
        return true;
    }

    bool addEdge(size_t from, size_t to, const EdgeLabel& label = EdgeLabel{}) {
        if (!isValidVertex(from) || !isValidVertex(to)) {
            return false;
        }

        if (adjacencyMatrix[from][to] != EdgeLabel{}) {
            return false;
        }

        adjacencyMatrix[from][to] = label;
        return true;
    }

    bool removeEdge(size_t from, size_t to) {
        if (!isValidVertex(from) || !isValidVertex(to)) {
            return false;
        }

        if (adjacencyMatrix[from][to] == EdgeLabel{}) {
            return false; 
        }

        adjacencyMatrix[from][to] = EdgeLabel{};
        return true;
    }

    bool hasEdge(size_t from, size_t to) const {
        if (!isValidVertex(from) || !isValidVertex(to)) {
            return false;
        }

        return adjacencyMatrix[from][to] != EdgeLabel{};
    }

    bool setEdgeLabel(size_t from, size_t to, const EdgeLabel& label) {
        if (!isValidVertex(from) || !isValidVertex(to)) {
            return false;
        }

        if (adjacencyMatrix[from][to] == EdgeLabel{}) {
            return false; 
        }

        adjacencyMatrix[from][to] = label;
        return true;
    }

    EdgeLabel getEdgeLabel(size_t from, size_t to) const {
        if (!isValidVertex(from) || !isValidVertex(to)) {
            return EdgeLabel{};
        }

        return adjacencyMatrix[from][to];
    }

    bool setVertexLabel(size_t vertex, const VertexLabel& label) {
        if (!isValidVertex(vertex)) {
            return false;
        }

        vertexLabels[vertex] = label;
        return true;
    }

    VertexLabel getVertexLabel(size_t vertex) const {
        if (!isValidVertex(vertex)) {
            return VertexLabel{};
        }

        return vertexLabels[vertex];
    }

    int getVertexId(const VertexLabel& label) const {
        for (size_t i = 0; i < vertexLabels.size(); ++i) {
            if (vertexLabels[i] == label) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    Vector<VertexLabel> getAllVertexLabels() const {
        return vertexLabels;
    }

    size_t countVertices() const {
        return vertexLabels.size();
    }

    void printAdjacencyMatrix(std::ostream& os = std::cout) const {
        os << "Adjacency matrix (" << countVertices() << " vertices):\n";

        os << "\t";
        for (size_t j = 0; j < countVertices(); ++j) {
            os << vertexLabels[j] << "\t";
        }
        os << "\n";

        for (size_t i = 0; i < countVertices(); ++i) {
            os << vertexLabels[i] << "\t";
            for (size_t j = 0; j < countVertices(); ++j) {
                EdgeLabel label = adjacencyMatrix[i][j];
                if (label == EdgeLabel{}) {
                    os << ".\t";
                }
                else {
                    os << label << "\t";
                }
            }
            os << "\n";
        }
    }

    class NeighborIterator {
    private:
        const Digraph* graph;
        size_t sourceVertex;
        size_t currentNeighbor;

        void findNextNeighbor() {
            while (currentNeighbor < graph->countVertices()) {
                if (graph->adjacencyMatrix[sourceVertex][currentNeighbor] != EdgeLabel{}) {
                    return;
                }
                ++currentNeighbor;
            }
        }

    public:
        NeighborIterator(const Digraph* g, size_t source, size_t start = 0)
            : graph(g), sourceVertex(source), currentNeighbor(start) {
            if (currentNeighbor < graph->countVertices() &&
                graph->adjacencyMatrix[sourceVertex][currentNeighbor] == EdgeLabel{}) {
                findNextNeighbor();
            }
        }

        size_t getNeighborId() const {
            return currentNeighbor;
        }

        EdgeLabel getEdgeLabel() const {
            return graph->adjacencyMatrix[sourceVertex][currentNeighbor];
        }

        NeighborIterator& operator++() {
            ++currentNeighbor;
            findNextNeighbor();
            return *this;
        }

        NeighborIterator operator++(int) {
            NeighborIterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const NeighborIterator& other) const {
            return graph == other.graph &&
                sourceVertex == other.sourceVertex &&
                currentNeighbor == other.currentNeighbor;
        }

        bool operator!=(const NeighborIterator& other) const {
            return !(*this == other);
        }

        std::pair<size_t, EdgeLabel> operator*() const {
            return { currentNeighbor, graph->adjacencyMatrix[sourceVertex][currentNeighbor] };
        }
    };

    NeighborIterator neighborBegin(size_t vertex) const {
        if (!isValidVertex(vertex)) {
            return NeighborIterator(this, vertex, countVertices());
        }
        return NeighborIterator(this, vertex, 0);
    }

    NeighborIterator neighborEnd(size_t vertex) const {
        return NeighborIterator(this, vertex, countVertices());
    }
};

#endif // GRAPH_H
[file content end]