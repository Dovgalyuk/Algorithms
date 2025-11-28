#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <functional>

template<typename VertexLabel, typename EdgeLabel>
class Graph {
private:
    struct Edge {
        size_t to_vertex;
        EdgeLabel label;
        Edge(size_t to, const EdgeLabel& lbl = EdgeLabel()) : to_vertex(to), label(lbl) {}

        bool operator==(const Edge& other) const {
            return to_vertex == other.to_vertex;
        }
    };

    struct VertexData {
        VertexLabel label;
        List<Edge> edges;

        VertexData() = default;
        VertexData(const VertexLabel& lbl) : label(lbl) {}
    };

    std::vector<VertexData> vertices;

public:
    class NeighborIterator {
    private:
        const Graph* graph;
        size_t current_vertex;
        typename List<Edge>::Iterator edge_iter;

    public:
        NeighborIterator(const Graph* g, size_t vertex) : graph(g), current_vertex(vertex) {
            if (vertex < graph->vertices.size()) {
                edge_iter = graph->vertices[vertex].edges.getIterator();
            }
        }

        bool hasNext() const {
            return edge_iter.hasNext();
        }

        int next() {
            if (!hasNext()) throw std::runtime_error("No more neighbors");
            Edge& edge = edge_iter.next();
            return static_cast<int>(edge.to_vertex);
        }

        EdgeLabel getEdgeLabel() const {
            throw std::runtime_error("Not implemented in this iterator version");
        }
    };

    Graph(size_t initial_vertices = 0) {
        vertices.reserve(initial_vertices);
        for (size_t i = 0; i < initial_vertices; ++i) {
            vertices.emplace_back();
        }
    }

    size_t addVertex() {
        vertices.emplace_back();
        return vertices.size() - 1;
    }

    size_t addVertex(const VertexLabel& label) {
        vertices.emplace_back(label);
        return vertices.size() - 1;
    }

    bool setVertexLabel(size_t vertex, const VertexLabel& label) {
        if (vertex >= vertices.size()) return false;
        vertices[vertex].label = label;
        return true;
    }

    VertexLabel getVertexLabel(size_t vertex) const {
        if (vertex >= vertices.size()) return VertexLabel();
        return vertices[vertex].label;
    }

    bool addEdge(size_t from, size_t to, const EdgeLabel& label = EdgeLabel()) {
        if (from >= vertices.size() || to >= vertices.size()) {
            return false;
        }

        auto iter = vertices[from].edges.getIterator();
        while (iter.hasNext()) {
            Edge& edge = iter.next();
            if (edge.to_vertex == to) {
                return false;
            }
        }

        vertices[from].edges.insert(Edge(to, label));
        return true;
    }

    bool removeEdge(size_t from, size_t to) {
        if (from >= vertices.size() || to >= vertices.size()) {
            return false;
        }

        auto& edges = vertices[from].edges;

        List<Edge> new_edges;
        bool removed = false;
        auto iter = edges.getIterator();

        while (iter.hasNext()) {
            Edge& edge = iter.next();
            if (edge.to_vertex != to) {
                new_edges.insert(edge);
            }
            else {
                removed = true;
            }
        }

        if (removed) {
            vertices[from].edges = std::move(new_edges);
        }

        return removed;
    }

    bool removeVertex(size_t vertex) {
        if (vertex >= vertices.size()) return false;

        for (size_t i = 0; i < vertices.size(); ++i) {
            if (i != vertex) {
                removeEdge(i, vertex);
            }
        }

        vertices.erase(vertices.begin() + vertex);
        return true;
    }

    bool hasEdge(size_t from, size_t to) const {
        if (from >= vertices.size() || to >= vertices.size()) {
            return false;
        }

        auto iter = vertices[from].edges.getIterator();
        while (iter.hasNext()) {
            Edge& edge = iter.next();
            if (edge.to_vertex == to) {
                return true;
            }
        }
        return false;
    }

    bool setEdgeLabel(size_t from, size_t to, const EdgeLabel& label) {
        if (from >= vertices.size() || to >= vertices.size()) return false;

        if (removeEdge(from, to)) {
            return addEdge(from, to, label);
        }
        return false;
    }

    EdgeLabel getEdgeLabel(size_t from, size_t to) const {
        if (from >= vertices.size() || to >= vertices.size()) return EdgeLabel();

        auto iter = vertices[from].edges.getIterator();
        while (iter.hasNext()) {
            Edge& edge = iter.next();
            if (edge.to_vertex == to) {
                return edge.label;
            }
        }
        return EdgeLabel();
    }

    std::vector<VertexLabel> getAllVertexLabels() const {
        std::vector<VertexLabel> labels;
        labels.reserve(vertices.size());
        for (const auto& vertex : vertices) {
            labels.push_back(vertex.label);
        }
        return labels;
    }

    NeighborIterator getNeighbors(size_t vertex) const {
        return NeighborIterator(this, vertex);
    }

    size_t getVertexCount() const { return vertices.size(); }

    std::vector<std::vector<int>> findAllShortestPaths(int start, int end) const;

    ~Graph() = default;
};

#endif