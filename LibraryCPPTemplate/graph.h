#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include "vector.h"

template <typename VertexLabel, typename EdgeLabel>
class Graph {
private:
    size_t num_vertices_;
    Vector<VertexLabel> vertex_labels_;
    Vector<Vector<std::optional<EdgeLabel>>> adjacency_matrix_;

public:
    Graph(size_t num_vertices = 0) : num_vertices_(num_vertices) {
        vertex_labels_.resize(num_vertices_);
        adjacency_matrix_.resize(num_vertices_);
        for (size_t i = 0; i < num_vertices_; ++i) {
            adjacency_matrix_[i].resize(num_vertices_);
        }
    }

    void addVertex() {
        ++num_vertices_;
        vertex_labels_.resize(num_vertices_);
        adjacency_matrix_.resize(num_vertices_);
        for (size_t i = 0; i < num_vertices_; ++i) {
            adjacency_matrix_[i].resize(num_vertices_);
        }
    }

    void addVertex(const VertexLabel& label) {
        addVertex();
        vertex_labels_[num_vertices_ - 1] = label;
    }

    void setVertexLabel(size_t v, const VertexLabel& label) {
        if (v >= num_vertices_) {
            throw std::out_of_range("Vertex index out of range");
        }
        vertex_labels_[v] = label;
    }

    void removeVertex(size_t v) {
        if (v >= num_vertices_) {
            throw std::out_of_range("Vertex index out of range");
        }

        for (size_t i = v; i < num_vertices_ - 1; ++i) {
            vertex_labels_[i] = vertex_labels_[i + 1];
        }

        for (size_t i = v; i < num_vertices_ - 1; ++i) {
            for (size_t j = 0; j < num_vertices_; ++j) {
                adjacency_matrix_[i][j] = adjacency_matrix_[i + 1][j];
            }
        }

        for (size_t i = 0; i < num_vertices_; ++i) {
            for (size_t j = v; j < num_vertices_ - 1; ++j) {
                adjacency_matrix_[i][j] = adjacency_matrix_[i][j + 1];
            }
        }

        --num_vertices_;
        vertex_labels_.resize(num_vertices_);
        adjacency_matrix_.resize(num_vertices_);
        for (size_t i = 0; i < num_vertices_; ++i) {
            adjacency_matrix_[i].resize(num_vertices_);
        }
    }

    void addEdge(size_t u, size_t v, const EdgeLabel& label) {
        if (u >= num_vertices_ || v >= num_vertices_) {
            throw std::out_of_range("Vertex index out of range");
        }
        adjacency_matrix_[u][v] = std::optional<EdgeLabel>(label);
    }

    void removeEdge(size_t u, size_t v) {
        if (u >= num_vertices_ || v >= num_vertices_) {
            throw std::out_of_range("Vertex index out of range");
        }
        adjacency_matrix_[u][v] = std::nullopt;
    }

    bool hasEdge(size_t u, size_t v) const {
        if (u >= num_vertices_ || v >= num_vertices_) {
            return false;
        }
        return adjacency_matrix_[u][v].has_value();
    }

    std::optional<EdgeLabel> getEdgeLabel(size_t u, size_t v) const {
        if (u >= num_vertices_ || v >= num_vertices_) {
            return std::nullopt;
        }
        return adjacency_matrix_[u][v];
    }

    size_t numVertices() const {
        return num_vertices_;
    }

    VertexLabel getVertexLabel(size_t v) const {
        if (v >= num_vertices_) {
            throw std::out_of_range("Vertex index out of range");
        }
        return vertex_labels_[v];
    }

    std::vector<VertexLabel> getAllVertexLabels() const {
        std::vector<VertexLabel> labels;
        for (size_t i = 0; i < num_vertices_; ++i) {
            labels.push_back(vertex_labels_[i]);
        }
        return labels;
    }

    class NeighborIterator {
    private:
        const Graph& graph_;
        size_t vertex_;
        size_t current_;

    public:
        NeighborIterator(const Graph& graph, size_t vertex, bool end = false)
            : graph_(graph), vertex_(vertex), current_(end ? graph.num_vertices_ : 0) {
            if (!end) {
                advanceToNext();
            }
        }

        void advanceToNext() {
            while (current_ < graph_.num_vertices_ &&
                !graph_.adjacency_matrix_[vertex_][current_].has_value()) {
                ++current_;
            }
        }

        bool operator==(const NeighborIterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const NeighborIterator& other) const {
            return !(*this == other);
        }

        NeighborIterator& operator++() {
            ++current_;
            advanceToNext();
            return *this;
        }

        size_t operator*() const {
            return current_;
        }

        std::optional<EdgeLabel> getEdgeLabel() const {
            if (current_ < graph_.num_vertices_) {
                return graph_.adjacency_matrix_[vertex_][current_];
            }
            return std::nullopt;
        }
    };

    NeighborIterator beginNeighbors(size_t vertex) const {
        if (vertex >= num_vertices_) {
            throw std::out_of_range("Vertex index out of range");
        }
        return NeighborIterator(*this, vertex);
    }

    NeighborIterator endNeighbors(size_t vertex) const {
        if (vertex >= num_vertices_) {
            throw std::out_of_range("Vertex index out of range");
        }
        return NeighborIterator(*this, vertex, true);
    }
};

#endif