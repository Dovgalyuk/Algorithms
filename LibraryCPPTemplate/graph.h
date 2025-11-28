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
            List<VertexData>::Item::deleteItem(item);
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
        ~NeighborIterator() {
            if (current) {
                List<Edge>::Item::deleteItem(current);
            }
        }

        bool hasNext() const {
            return current != nullptr;
        }

        int next() {
            if (!current) throw std::runtime_error("No more neighbors");
            int neighbor = current->data().to_vertex;
            auto next_item = current->next();
            List<Edge>::Item::deleteItem(current);
            current = next_item;
            return neighbor;
        }

        EdgeLabel getEdgeLabel() const {
            if (!current) throw std::runtime_error("No current edge");
            return current->data().label;
        }

        NeighborIterator(const NeighborIterator&) = delete;
        NeighborIterator& operator=(const NeighborIterator&) = delete;

        NeighborIterator(NeighborIterator&& other) noexcept : current(other.current) {
            other.current = nullptr;
        }

        NeighborIterator& operator=(NeighborIterator&& other) noexcept {
            if (this != &other) {
                if (current) {
                    List<Edge>::Item::deleteItem(current);
                }
                current = other.current;
                other.current = nullptr;
            }
            return *this;
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
        List<VertexData>::Item::deleteItem(vertex_item);
        return true;
    }

    VertexLabel getVertexLabel(size_t vertex) const {
        if (vertex >= vertex_count) return VertexLabel();

        auto vertex_item = getVertexItem(vertex);
        if (!vertex_item) return VertexLabel();

        VertexLabel label = vertex_item->data().label;
        List<VertexData>::Item::deleteItem(vertex_item);
        return label;
    }

    bool addEdge(size_t from, size_t to, const EdgeLabel& label = EdgeLabel()) {
        if (from >= vertex_count || to >= vertex_count) {
            return false;
        }

        auto vertex_item = getVertexItem(from);
        if (!vertex_item) return false;

        bool edge_exists = false;
        auto edge_item = vertex_item->data().edges.first();
        while (edge_item && !edge_exists) {
            if (edge_item->data().to_vertex == to) {
                edge_exists = true;
            }
            auto next_edge = edge_item->next();
            List<Edge>::Item::deleteItem(edge_item);
            edge_item = next_edge;
        }

        if (edge_exists) {
            List<VertexData>::Item::deleteItem(vertex_item);
            return false;
        }

        vertex_item->data().edges.insert(Edge(to, label));
        List<VertexData>::Item::deleteItem(vertex_item);
        return true;
    }

    bool removeEdge(size_t from, size_t to) {
        if (from >= vertex_count || to >= vertex_count) {
            return false;
        }

        auto vertex_item = getVertexItem(from);
        if (!vertex_item) return false;

        auto& edges_list = vertex_item->data().edges;
        bool removed = false;

        auto first_edge = edges_list.first();
        if (!first_edge) {
            List<VertexData>::Item::deleteItem(vertex_item);
            return false;
        }

        if (first_edge->data().to_vertex == to) {
            edges_list.erase_first();
            removed = true;
            List<Edge>::Item::deleteItem(first_edge);
        }
        else {
            auto prev_edge = first_edge;
            auto current_edge = first_edge->next();

            while (current_edge && !removed) {
                if (current_edge->data().to_vertex == to) {
                    edges_list.erase_next(prev_edge);
                    removed = true;
                    List<Edge>::Item::deleteItem(current_edge);
                }
                else {
                    auto next_prev = current_edge;
                    auto next_current = current_edge->next();
                    List<Edge>::Item::deleteItem(prev_edge);
                    prev_edge = next_prev;
                    current_edge = next_current;
                }
            }
            if (prev_edge) List<Edge>::Item::deleteItem(prev_edge);
        }

        List<VertexData>::Item::deleteItem(vertex_item);
        return removed;
    }

    bool removeVertex(size_t vertex) {
        if (vertex >= vertex_count) return false;

        for (size_t i = 0; i < vertex_count; ++i) {
            if (i != vertex) {
                removeEdge(i, vertex);
            }
        }

        vertex_count--;
        return true;
    }

    bool hasEdge(size_t from, size_t to) const {
        if (from >= vertex_count || to >= vertex_count) {
            return false;
        }

        auto vertex_item = getVertexItem(from);
        if (!vertex_item) return false;

        bool found = false;
        auto edge_item = vertex_item->data().edges.first();
        while (edge_item && !found) {
            if (edge_item->data().to_vertex == to) {
                found = true;
            }
            auto next_edge = edge_item->next();
            List<Edge>::Item::deleteItem(edge_item);
            edge_item = next_edge;
        }

        List<VertexData>::Item::deleteItem(vertex_item);
        return found;
    }

    bool setEdgeLabel(size_t from, size_t to, const EdgeLabel& label) {
        if (from >= vertex_count || to >= vertex_count) return false;

        auto vertex_item = getVertexItem(from);
        if (!vertex_item) return false;

        bool found = false;
        auto edge_item = vertex_item->data().edges.first();
        while (edge_item && !found) {
            if (edge_item->data().to_vertex == to) {
                edge_item->data().label = label;
                found = true;
            }
            auto next_edge = edge_item->next();
            List<Edge>::Item::deleteItem(edge_item);
            edge_item = next_edge;
        }

        List<VertexData>::Item::deleteItem(vertex_item);
        return found;
    }

    EdgeLabel getEdgeLabel(size_t from, size_t to) const {
        if (from >= vertex_count || to >= vertex_count) return EdgeLabel();

        auto vertex_item = getVertexItem(from);
        if (!vertex_item) return EdgeLabel();

        EdgeLabel label = EdgeLabel();
        bool found = false;
        auto edge_item = vertex_item->data().edges.first();
        while (edge_item && !found) {
            if (edge_item->data().to_vertex == to) {
                label = edge_item->data().label;
                found = true;
            }
            auto next_edge = edge_item->next();
            List<Edge>::Item::deleteItem(edge_item);
            edge_item = next_edge;
        }

        List<VertexData>::Item::deleteItem(vertex_item);
        return label;
    }

    std::vector<VertexLabel> getAllVertexLabels() const {
        std::vector<VertexLabel> labels;
        auto item = vertices.first();
        while (item) {
            labels.push_back(item->data().label);
            auto next = item->next();
            List<VertexData>::Item::deleteItem(item);
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
        List<VertexData>::Item::deleteItem(vertex_item);
        return NeighborIterator(edges_item);
    }

    size_t getVertexCount() const { return vertex_count; }

    std::vector<std::vector<int>> findAllShortestPaths(int start, int end) const;

    ~Graph() = default;
};

#endif
 