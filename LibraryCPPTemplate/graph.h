#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include "vector.h"
#include <cstddef>

template<typename VertexLabel, typename EdgeLabel>
class Graph {
public:
    Graph(size_t count) {
        vertex_count = count;
        vertex_labels.resize(count);
        exists.resize(count);
        edges.resize(count);

        for (size_t i = 0; i < count; ++i) {
            exists.set(i, true);
            Vector<EdgeLabel>& row = edges.get(i);
            row.resize(count);
            for (size_t j = 0; j < count; ++j) {
                row.set(j, EdgeLabel());
            }
        }
    }

    Graph(const Graph& g) {
        vertex_count = g.vertex_count;
        vertex_labels = g.vertex_labels;
        exists = g.exists;
        edges = g.edges;
    }

    Graph& operator=(const Graph& g) {
        if (this != &g) {
            vertex_count = g.vertex_count;
            vertex_labels = g.vertex_labels;
            exists = g.exists;
            edges = g.edges;
        }
        return *this;
    }

    size_t get_vertex_count() const {
        return vertex_count;
    }

    size_t add_vertex(VertexLabel value) {
        size_t new_index = vertex_count;
        vertex_count++;

        vertex_labels.resize(vertex_count);
        vertex_labels.set(new_index, value);

        exists.resize(vertex_count);
        exists.set(new_index, true);

        edges.resize(vertex_count);

        for (size_t i = 0; i < vertex_count - 1; ++i) {
            Vector<EdgeLabel>& row = edges.get(i);
            row.resize(vertex_count);
        }

        Vector<EdgeLabel>& new_row = edges.get(new_index);
        new_row.resize(vertex_count);
        for (size_t j = 0; j < vertex_count; ++j) {
            new_row.set(j, EdgeLabel());
        }

        return new_index;
    }

    void remove_vertex(size_t vertex_id) {
        if (vertex_id >= vertex_count || !exists.get(vertex_id)) {
            return;
        }

        exists.set(vertex_id, false);
        vertex_labels.set(vertex_id, VertexLabel());

        for (size_t i = 0; i < vertex_count; ++i) {
            Vector<EdgeLabel>& row = edges.get(vertex_id);
            row.set(i, EdgeLabel());

            Vector<EdgeLabel>& new_row = edges.get(i);
            new_row.set(vertex_id, EdgeLabel());
        }
    }

    void set_vertex_label(size_t vertex_id, VertexLabel value) {
        if (vertex_id < vertex_count && exists.get(vertex_id)) {
            vertex_labels.set(vertex_id, value);
        }
    }

    VertexLabel get_vertex_label(size_t vertex_id) const {
        if (vertex_id < vertex_count && exists.get(vertex_id)) {
            return vertex_labels.get(vertex_id);
        }
        return VertexLabel();
    }

    Vector<VertexLabel> get_all_vertex_labels() const {
        Vector<VertexLabel> result;
        result.resize(vertex_count);
        for (size_t i = 0; i < vertex_count; ++i) {
            result.set(i, vertex_labels.get(i));
        }
        return result;
    }

    void add_edge(size_t from, size_t to, EdgeLabel value) {
        if (from < vertex_count && to < vertex_count &&
            exists.get(from) && exists.get(to)) {
            Vector<EdgeLabel>& row = edges.get(from);
            row.set(to, value);
        }
    }

    void remove_edge(size_t from, size_t to) {
        if (from < vertex_count && to < vertex_count &&
            exists.get(from) && exists.get(to)) {
            Vector<EdgeLabel>& row = edges.get(from);
            row.set(to, EdgeLabel());
        }
    }

    bool has_edge(size_t from, size_t to) const {
        if (from < vertex_count && to < vertex_count &&
            exists.get(from) && exists.get(to)) {
            Vector<EdgeLabel> row = edges.get(from);
            EdgeLabel value = row.get(to);
            EdgeLabel default_value = EdgeLabel();
            return !(value == default_value);
        }
        return false;
    }

    void set_edge_label(size_t from, size_t to, EdgeLabel value) {
        if (from < vertex_count && to < vertex_count &&
            exists.get(from) && exists.get(to) && has_edge(from, to)) {
            Vector<EdgeLabel>& row = edges.get(from);
            row.set(to, value);
        }
    }

    EdgeLabel get_edge_label(size_t from, size_t to) const {
        if (from < vertex_count && to < vertex_count &&
            exists.get(from) && exists.get(to) && has_edge(from, to)) {
            Vector<EdgeLabel> row = edges.get(from);
            return row.get(to);
        }
        return EdgeLabel();
    }

    class NeighborIterator {
    public:
        NeighborIterator() {
            graph = 0;
            current = 0;
            from_vertex = 0;
        }

        bool valid() const {
            return graph != 0 && current < graph->vertex_count;
        }

        void next() {
            if (graph == 0) return;

            current++;
            while (current < graph->vertex_count) {
                if (current != from_vertex &&
                    graph->exists.get(from_vertex) &&
                    graph->exists.get(current) &&
                    graph->has_edge(from_vertex, current)) {
                    break;
                }
                current++;
            }
        }

        size_t vertex_id() const {
            return current;
        }

        EdgeLabel edge_label() const {
            if (valid()) {
                return graph->get_edge_label(from_vertex, current);
            }
            return EdgeLabel();
        }

    private:
        const Graph* graph;
        size_t current;
        size_t from_vertex;

        NeighborIterator(const Graph* g, size_t from) {
            graph = g;
            from_vertex = from;
            current = 0;

            while (current < graph->vertex_count) {
                if (current != from_vertex &&
                    graph->exists.get(from_vertex) &&
                    graph->exists.get(current) &&
                    graph->has_edge(from_vertex, current)) {
                    break;
                }
                current++;
            }
        }

        friend class Graph<VertexLabel, EdgeLabel>;
    };

    NeighborIterator neighbors(size_t from) const {
        return NeighborIterator(this, from);
    }

private:
    size_t vertex_count;
    Vector<VertexLabel> vertex_labels;
    Vector<bool> exists;
    Vector<Vector<EdgeLabel>> edges;
};

#endif