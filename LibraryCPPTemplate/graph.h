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
    };
    List<VertexData> vertices;
    size_t vertex_count;

    typename List<VertexData>::Item* getVertexItem(size_t index) const {
        auto item = vertices.first();
        for (size_t i = 0; i < index && item; ++i) {
            auto next = item->next();
            delete item;
            item = next;
        }
        return item;
    }

public:
    class NeighborIterator {
    private:
        typename List<Edge>::Item* current;

    public:
        NeighborIterator(typename List<Edge>::Item* start) : current(start) {}

        bool hasNext() const {
            return current != nullptr;
        }

        int next() {
            if (!current) throw std::runtime_error("No more neighbors");
            int neighbor = current->data().to_vertex;
            auto next_item = current->next();
            current = next_item;
            return neighbor;
        }

        EdgeLabel getEdgeLabel() const {
            if (!current) throw std::runtime_error("No current edge");
            return current->data().label;
        }
    };
    Graph(size_t initial_vertices = 0) : vertex_count(0) {
        for (size_t i = 0; i < initial_vertices; ++i) {
            addVertex();
        }
    }
    size_t addVertex() {
        VertexData data;
        data.label = VertexLabel();
        vertices.insert(data);
        return vertex_count++;
    }
    size_t addVertex(const VertexLabel& label) {
        VertexData data;
        data.label = label;
        vertices.insert(data);
        return vertex_count++;
    }
    bool setVertexLabel(size_t vertex, const VertexLabel& label) {
        if (vertex >= vertex_count) return false;

        auto vertex_item = getVertexItem(vertex);
        if (!vertex_item) return false;

        vertex_item->data().label = label;
        delete vertex_item;
        return true;
    }
    VertexLabel getVertexLabel(size_t vertex) const {
        if (vertex >= vertex_count) return VertexLabel();

        auto vertex_item = getVertexItem(vertex);
        if (!vertex_item) return VertexLabel();

        VertexLabel label = vertex_item->data().label;
        delete vertex_item;
        return label;
    }



    bool addEdge(size_t from, size_t to, const EdgeLabel& label = EdgeLabel()) {
        if (from >= vertex_count || to >= vertex_count) {
            return false;
        }

        auto vertex_item = getVertexItem(from);
        if (!vertex_item) return false;

        auto edge_item = vertex_item->data().edges.first();
        while (edge_item) {
            if (edge_item->data().to_vertex == to) {
                delete edge_item;
                delete vertex_item;
                return false;
            }
            auto next_edge = edge_item->next();
            delete edge_item;
            edge_item = next_edge;
        }

        vertex_item->data().edges.insert(Edge(to, label));
        delete vertex_item;
        return true;
    }

    bool removeEdge(size_t from, size_t to) {
        if (from >= vertex_count || to >= vertex_count) {
            return false;
        }

        auto vertex_item = getVertexItem(from);
        if (!vertex_item) return false;

        auto& edges_list = vertex_item->data().edges;
        auto prev_edge = edges_list.first();

        if (!prev_edge) {
            delete vertex_item;
            return false;
        }

        if (prev_edge->data().to_vertex == to) {
            edges_list.erase_first();
            delete vertex_item;
            return true;
        }

        auto current_edge = prev_edge->next();
        while (current_edge) {
            if (current_edge->data().to_vertex == to) {
                edges_list.erase_next(prev_edge);
                delete vertex_item;
                return true;
            }
            prev_edge = current_edge;
            current_edge = current_edge->next();
        }

        delete vertex_item;
        return false;
    }

    bool removeVertex(size_t vertex) {
        if (vertex >= vertex_count) return false;

        vertex_count--;
        return true;
    }

    bool hasEdge(size_t from, size_t to) const {
        if (from >= vertex_count || to >= vertex_count) {
            return false;
        }

        auto vertex_item = getVertexItem(from);
        if (!vertex_item) return false;

        auto edge_item = vertex_item->data().edges.first();
        while (edge_item) {
            if (edge_item->data().to_vertex == to) {
                delete edge_item;
                delete vertex_item;
                return true;
            }
            auto next_edge = edge_item->next();
            delete edge_item;
            edge_item = next_edge;
        }

        delete vertex_item;
        return false;
    }

    bool setEdgeLabel(size_t from, size_t to, const EdgeLabel& label) {
        if (from >= vertex_count || to >= vertex_count) return false;

        auto vertex_item = getVertexItem(from);
        if (!vertex_item) return false;

        auto edge_item = vertex_item->data().edges.first();
        while (edge_item) {
            if (edge_item->data().to_vertex == to) {
                edge_item->data().label = label;
                delete edge_item;
                delete vertex_item;
                return true;
            }
            auto next_edge = edge_item->next();
            delete edge_item;
            edge_item = next_edge;
        }

        delete vertex_item;
        return false;
    }

    EdgeLabel getEdgeLabel(size_t from, size_t to) const {
        if (from >= vertex_count || to >= vertex_count) return EdgeLabel();

        auto vertex_item = getVertexItem(from);
        if (!vertex_item) return EdgeLabel();

        auto edge_item = vertex_item->data().edges.first();
        while (edge_item) {
            if (edge_item->data().to_vertex == to) {
                EdgeLabel label = edge_item->data().label;
                delete edge_item;
                delete vertex_item;
                return label;
            }
            auto next_edge = edge_item->next();
            delete edge_item;
            edge_item = next_edge;
        }

        delete vertex_item;
        return EdgeLabel();
    }

    std::vector<VertexLabel> getAllVertexLabels() const {
        std::vector<VertexLabel> labels;
        auto item = vertices.first();
        while (item) {
            labels.push_back(item->data().label);
            auto next = item->next();
            delete item;
            item = next;
        }
        return labels;
    }

    NeighborIterator getNeighbors(size_t vertex) const {
        if (vertex >= vertex_count) {
            return NeighborIterator(nullptr);
        }

        auto vertex_item = getVertexItem(vertex);
        if (!vertex_item) return NeighborIterator(nullptr);

        auto edges_item = vertex_item->data().edges.first();
        delete vertex_item;
        return NeighborIterator(edges_item);
    }

    size_t getVertexCount() const { return vertex_count; }

    std::vector<std::vector<int>> findAllShortestPaths(int start, int end) const;

    ~Graph() {

        auto item = vertices.first();
        while (item) {
            auto next = item->next();

            auto edge_item = item->data().edges.first();
            while (edge_item) {
                auto next_edge = edge_item->next();
                delete edge_item;
                edge_item = next_edge;
            }
            delete item;
            item = next;
        }
    }
};

#endif