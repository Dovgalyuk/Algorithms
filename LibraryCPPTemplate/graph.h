#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include "list.h"

template <typename V, typename E>
class Graph {
public:
    struct Edge {
        size_t to;
        E weight;
    };

    Graph(size_t n = 0) : vertices(n) {}

    void setLabel(size_t v, const V& data) { vertices[v].label = data; }
    V getLabel(size_t v) const { return vertices[v].label; }
    size_t size() const { return vertices.size(); }

    void addEdge(size_t from, size_t to, const E& weight) {
        vertices[from].edges.push_back({ to, weight });
    }

    const List<Edge>& getEdges(size_t id) const { return vertices[id].edges; }

private:
    struct Vertex {
        V label;
        List<Edge> edges;
    };
    std::vector<Vertex> vertices;
};

#endif