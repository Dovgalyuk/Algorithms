#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include "vector.h"
#include <stdexcept>

template <typename V, typename E>
class Graph {
public:
    struct Edge {
        size_t path;
        E sign;

        Edge(size_t edgeTo, E edgeMark) : path(edgeTo), sign(edgeMark) {}
    };

    Graph(size_t vertices) : vertexCount(vertices) {
        adjacencyList.resize(vertices);
        verticesMarks.resize(vertices);
        for (size_t i = 0; i < vertices; ++i) {
            adjacencyList.set(i, List<Edge>());
        }
    }

    void addEdge(size_t from, size_t path, E mark) {
        if (from >= vertexCount) {
            throw std::invalid_argument("It's impossible to add an edge, the vertex doesn't exist. addEdge");
        }
        if (!hasEdge(from, path)) {
            adjacencyList.get(from).insert(Edge(path, mark));
        } else {
            throw std::invalid_argument("This edge already exists. addEdge");
        }
    }

    void removeEdge(size_t from, size_t path) {
        if (from >= vertexCount || path >= vertexCount) {
            throw std::invalid_argument("It's impossible to remove an edge, the vertex doesn't exist. removeEdge");
        }

        auto& edges = adjacencyList.get(from);
        auto* current = edges.first();
        typename List<Edge>::Item* prev = nullptr;

        while (current) {
            if (current->data().path == path) {
                if (prev) {
                    edges.erase_next(prev);
                } else {
                    edges.erase_first();
                }
                return;
            }
            prev = current;
            current = current->next();
        }
    }

    void addVertex() {
        adjacencyList.resize(vertexCount + 1);
        verticesMarks.resize(vertexCount + 1);
        adjacencyList.set(vertexCount, List<Edge>());
        verticesMarks.set(vertexCount, V());
        ++vertexCount;
    }

    void removeVertex(size_t vertex) {
        if (vertex >= vertexCount) {
            throw std::invalid_argument("Not found specified vertex. removeVertex");
        }

        for (size_t i = 0; i < vertexCount; ++i) {
            if (i != vertex) {
                removeEdge(i, vertex);
            }
        }

        auto& edges = adjacencyList.get(vertex);
        auto* current = edges.first();
        while (current) {
            auto* next = current->next();
            removeEdge(vertex, current->data().path);
            current = next;
        }

        for (size_t i = vertex; i < vertexCount - 1; ++i) {
            swap(adjacencyList, i, i + 1);
            swap(verticesMarks, i, i + 1);
        }

        adjacencyList.resize(vertexCount - 1);
        verticesMarks.resize(vertexCount - 1);
        --vertexCount;
    }

    bool hasEdge(size_t from, size_t path) const {
        if (from >= vertexCount || path >= vertexCount) {
            return false;
        }

        auto& edges = adjacencyList.get(from);
        auto* current = edges.first();
        while (current) {
            if (current->data().path == path) {
                return true;
            }
            current = current->next();
        }
        return false;
    }

    E getEdgeMark(size_t from, size_t path) const {
        if (from >= vertexCount || path >= vertexCount) {
            throw std::invalid_argument("Not found specified vertex. getEdgeMark");
        }

        auto& edges = adjacencyList.get(from);
        auto* current = edges.first();
        while (current) {
            if (current->data().path == path) {
                return current->data().sign;
            }
            current = current->next();
        }
        throw std::invalid_argument("Edge does not exist. getEdgeMark");
    }

    void setEdgeMark(size_t from, size_t path, E mark) {
        if (from >= vertexCount || path >= vertexCount) {
            throw std::invalid_argument("Not found specified vertex. setEdgeMark");
        }

        auto& edges = adjacencyList.get(from);
        auto* current = edges.first();

        while (current) {
            if (current->data().path == path) {
                current->data() = Edge(path, mark);
                return;
            }
            current = current->next();
        }
    }

    V getVertexMark(size_t vertex) const {
        if (vertex >= vertexCount) {
            throw std::invalid_argument("Not found specified vertex. getVertexMark");
        }
        return verticesMarks.get(vertex);
    }

    void setVertexMark(size_t vertex, V new_mark) {
        if (vertex >= vertexCount) {
            throw std::invalid_argument("Not found specified vertex. setVertexMark");
        }
        verticesMarks.set(vertex, new_mark);
    }

    Vector<V> getAllVertexMarks() const {
        return verticesMarks;
    }

    size_t getSize() const {
        return vertexCount;
    }

    class Iterator {
    public:
        Iterator(typename List<Edge>::Item* start) : currentItem_(start) {}

        bool operator==(const Iterator& other) const { return currentItem_ == other.currentItem_; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }

        Iterator& operator++() {
            if (currentItem_) {
                currentItem_ = currentItem_->next();
            }
            return *this;
        }

        Edge operator*() const {
            return currentItem_->data();
        }

    private:
        typename List<Edge>::Item* currentItem_;
    };

    Iterator begin(size_t vertex) {
        if (vertex >= vertexCount) {
            throw std::invalid_argument("Not found specified vertex.");
        }
        return Iterator(adjacencyList.get(vertex).first());
    }

    Iterator end(size_t vertex) {
        return Iterator(nullptr);
    }

private:
    size_t vertexCount;
    Vector<List<Edge>> adjacencyList;
    Vector<V> verticesMarks;

    template <typename T>
    void swap(Vector<T>& vec, size_t i, size_t j) {
        T temp = vec.get(i);
        vec.set(i, vec.get(j));
        vec.set(j, temp);
    }
};

#endif // GRAPH_H
