#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include "vector.h"
#include <stdexcept>
#include <iostream>
using namespace std;
template <typename V, typename E>
class Graph {
private:
    struct Edge {
        size_t to;
        E label;

        Edge(size_t t, const E& l) : to(t), label(l) {}

        bool operator==(const Edge& other) const {
            return to == other.to;  
        }
    };

    Vector<V> vertexLabels;
    Vector<List<Edge>> adjLists;

    void checkIndex(size_t index) const {
        if (index >= vertexLabels.size()) {
            throw  out_of_range("Index out of range");
        }
    }

public:
    Graph(size_t vertexCount = 0) {
        vertexLabels.resize(vertexCount);
        adjLists.resize(vertexCount);
    }

    size_t addVertex(const V& label) {
        size_t index = vertexLabels.size();
        vertexLabels.push_back(label);
        adjLists.push_back(List<Edge>());
        return index;
    }

    void removeVertex(size_t index) {
        checkIndex(index);

        vertexLabels.erase(index);
        adjLists.erase(index);

        for (size_t i = 0; i < adjLists.size(); ++i) {
            for (auto it = adjLists[i].first(); it != nullptr; it = it->next()) {
                if (it->data().to == index) {
                    adjLists[i].erase(it->data());
                    break;  
                }
            }

            for (auto it = adjLists[i].first(); it != nullptr; it = it->next()) {
                if (it->data().to > index) {
                    it->data().to--;  
                }
            }
        }
    }

    void addEdge(size_t from, size_t to, const E& label) {
        checkIndex(from);
        checkIndex(to);

        for (auto it = adjLists[from].first(); it != nullptr; it = it->next()) {
            if (it->data().to == to) {
                it->data().label = label;
                return;
            }
        }

        adjLists[from].push_back(Edge(to, label));
    }

    void removeEdge(size_t from, size_t to) {
        checkIndex(from);
        checkIndex(to);

        for (auto it = adjLists[from].first(); it != nullptr; it = it->next()) {
            if (it->data().to == to) {
                adjLists[from].erase(it->data());
                return;
            }
        }
    }

    bool hasEdge(size_t from, size_t to) const {
        checkIndex(from);
        checkIndex(to);

        for (auto it = adjLists[from].begin(); it != adjLists[from].end(); ++it) {
            if ((*it).to == to) {
                return true;
            }
        }
        return false;
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

        for (auto it = adjLists[from].first(); it != nullptr; it = it->next()) {
            if (it->data().to == to) {
                it->data().label = label;
                return;
            }
        }
        throw runtime_error("Edge does not exist");
    }

    E getEdgeLabel(size_t from, size_t to) const {
        checkIndex(from);
        checkIndex(to);

        for (auto it = adjLists[from].begin(); it != adjLists[from].end(); ++it) {
            if ((*it).to == to) {
                return (*it).label;
            }
        }
        throw  runtime_error("Edge does not exist");
    }

    Vector<V> getAllVertexLabels() const {
        return vertexLabels;
    }

    size_t getVertexCount() const {
        return vertexLabels.size();
    }

    class Iterator {
    private:
        typename List<Edge>::const_iterator current;
        typename List<Edge>::const_iterator end;

    public:
        Iterator(const List<Edge>& list) : current(list.begin()), end(list.end()) {}

        bool hasNext() const {
            return current != end;
        }

        size_t next() {
            if (!hasNext()) throw  out_of_range("No more edges");
            size_t toVertex = (*current).to;
            ++current;
            return toVertex;
        }
    };

    Iterator getIterator(size_t vertex) const {
        checkIndex(vertex);
        return Iterator(adjLists[vertex]);
    }
};

#endif