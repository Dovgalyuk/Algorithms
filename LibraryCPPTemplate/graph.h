#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>  // Для использования std::remove_if

template <typename T>
class Graph {
private:
    struct Vertex {
        T data;
        Vertex(T data) : data(data) {}
        T getVertexData() const { return data; }
    };

    struct Edge {
        size_t start;
        size_t end;
        int weight;
        Edge(size_t start, size_t end, int weight) : start(start), end(end), weight(weight) {}
        int getEdgeData() const { return weight; }
        void setEdgeData(int newWeight) { weight = newWeight; }
    };

    std::vector<Vertex> vertexes;
    std::vector<Edge*> edges;

public:
    Graph(size_t vertexCount) {
        for (size_t i = 0; i < vertexCount; ++i) {
            vertexes.push_back(Vertex(T(i))); // Initializing vertex data with their index.
        }
    }

    size_t getVertexAmount() const {
        return vertexes.size();
    }

    Vertex getVertex(size_t index) const {
        if (index >= vertexes.size()) {
            throw std::out_of_range("Vertex index out of range");
        }
        return vertexes[index];
    }

    void addEdge(size_t start, size_t end, int weight) {
        if (start >= vertexes.size() || end >= vertexes.size()) {
            throw std::out_of_range("Edge vertices are out of range");
        }
        edges.push_back(new Edge(start, end, weight));
    }

    bool isEdgeExist(size_t start, size_t end) const {
        for (const auto& edge : edges) {
            if (edge->start == start && edge->end == end) {
                return true;
            }
        }
        return false;
    }

    Edge* getEdge(size_t start, size_t end) const {
        for (auto& edge : edges) {
            if (edge->start == start && edge->end == end) {
                return edge;
            }
        }
        return nullptr; 
    }

    void removeEdge(size_t start, size_t end) {
        edges.erase(
            std::remove_if(edges.begin(), edges.end(), [start, end](Edge* edge) {
                return edge->start == start && edge->end == end;
            }),
            edges.end()
        );
    }

    void removeVertex(size_t index) {
        if (index >= vertexes.size()) {
            throw std::out_of_range("Vertex index out of range");
        }

        // Remove edges connected to this vertex
        edges.erase(
            std::remove_if(edges.begin(), edges.end(), [index](Edge* edge) {
                return edge->start == index || edge->end == index;
            }),
            edges.end()
        );

        // Remove vertex
        vertexes.erase(vertexes.begin() + index);

        // Reindex the remaining vertices
        for (auto& edge : edges) {
            if (edge->start > index) edge->start--;
            if (edge->end > index) edge->end--;
        }
    }

    class Iterator {
    private:
        size_t index;
        Graph* graph;

    public:
        // Поменяли местами порядок объявления переменных
        Iterator(Graph* graph, size_t index) : index(index), graph(graph) {}

        bool operator!=(const Iterator& other) const {
            return index != other.index;
        }

        Iterator& operator++() {
            ++index;
            return *this;
        }

        Vertex operator*() const {
            return graph->getVertex(index);
        }

        size_t getIndex() const {
            return index;
        }
    };

    Iterator getIterator(size_t startIndex) {
        return Iterator(this, startIndex);
    }
};

#endif
