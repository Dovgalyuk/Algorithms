#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <istream>
#include "vector.h"

template <typename VertexLabel, typename EdgeLabel> class Graph
{
private:
    struct Edge
    {
        bool exists = false;
        EdgeLabel label = EdgeLabel();
    };

    size_t vertex_count_ = 0;
    Vector<VertexLabel> vertex_labels_;
    Vector<Edge> matrix_;

    void reset(size_t count)
    {
        vertex_count_ = count;
        vertex_labels_.resize(0);
        vertex_labels_.resize(count);
        matrix_.resize(0);
        matrix_.resize(count * count);
    }

public:
    struct NeighborIterator
    {
        const Graph *graph_;
        size_t from_;
        size_t current_;

        NeighborIterator(const Graph *graph, size_t from, size_t start)
            : graph_(graph), from_(from), current_(start)
        {
            advance_to_valid();
        }

        void advance_to_valid()
        {
            size_t n = graph_->vertex_count();
            if (from_ >= n)
            {
                current_ = n;
                return;
            }
            while (current_ < n && !graph_->has_edge(from_, current_))
            {
                ++current_;
            }
        }

        size_t operator*() const
        {
            return current_;
        }

        NeighborIterator &operator++()
        {
            if (current_ < graph_->vertex_count())
            {
                ++current_;
                advance_to_valid();
            }
            return *this;
        }

        bool operator!=(const NeighborIterator &other) const
        {
            return current_ != other.current_ || from_ != other.from_ || graph_ != other.graph_;
        }

        bool operator==(const NeighborIterator &other) const
        {
            return !(*this != other);
        }

        bool has_next() const
        {
            return current_ < graph_->vertex_count();
        }

        size_t vertex() const
        {
            return current_;
        }

        EdgeLabel edge_label() const
        {
            return graph_->get_edge_label(from_, current_);
        }
    };

    explicit Graph(size_t vertex_count = 0)
        : vertex_count_(vertex_count)
    {
        vertex_labels_.resize(vertex_count);
        matrix_.resize(vertex_count * vertex_count);
    }

    size_t vertex_count() const
    {
        return vertex_count_;
    }

    size_t add_vertex(const VertexLabel &label = VertexLabel())
    {
        size_t new_count = vertex_count_ + 1;
        Vector<Edge> new_matrix;
        new_matrix.resize(new_count * new_count);
        for (size_t r = 0; r < vertex_count_; ++r)
        {
            for (size_t c = 0; c < vertex_count_; ++c)
            {
                new_matrix.set(r * new_count + c, matrix_.get(r * vertex_count_ + c));
            }
        }
        matrix_ = new_matrix;
        vertex_labels_.resize(new_count);
        vertex_labels_.set(vertex_count_, label);
        size_t index = vertex_count_;
        vertex_count_ = new_count;
        return index;
    }

    void remove_vertex(size_t vertex)
    {
        if (vertex >= vertex_count_)
        {
            return;
        }
        size_t new_count = vertex_count_ - 1;
        Vector<Edge> new_matrix;
        new_matrix.resize(new_count * new_count);
        for (size_t r = 0; r < vertex_count_; ++r)
        {
            if (r == vertex)
            {
                continue;
            }
            size_t nr = (r < vertex) ? r : (r - 1);
            for (size_t c = 0; c < vertex_count_; ++c)
            {
                if (c == vertex)
                {
                    continue;
                }
                size_t nc = (c < vertex) ? c : (c - 1);
                new_matrix.set(nr * new_count + nc, matrix_.get(r * vertex_count_ + c));
            }
        }
        for (size_t i = vertex + 1; i < vertex_count_; ++i)
        {
            vertex_labels_.set(i - 1, vertex_labels_.get(i));
        }
        vertex_labels_.resize(new_count);
        matrix_ = new_matrix;
        vertex_count_ = new_count;
    }

    void add_edge(size_t from, size_t to, const EdgeLabel &label = EdgeLabel())
    {
        if (from >= vertex_count_ || to >= vertex_count_)
        {
            return;
        }
        Edge edge;
        edge.exists = true;
        edge.label = label;
        matrix_.set(from * vertex_count_ + to, edge);
    }

    void remove_edge(size_t from, size_t to)
    {
        if (from >= vertex_count_ || to >= vertex_count_)
        {
            return;
        }
        matrix_.set(from * vertex_count_ + to, Edge());
    }

    bool has_edge(size_t from, size_t to) const
    {
        if (from >= vertex_count_ || to >= vertex_count_)
        {
            return false;
        }
        return matrix_.get(from * vertex_count_ + to).exists;
    }

    void set_edge_label(size_t from, size_t to, const EdgeLabel &label)
    {
        if (!has_edge(from, to))
        {
            return;
        }
        Edge edge = matrix_.get(from * vertex_count_ + to);
        edge.label = label;
        matrix_.set(from * vertex_count_ + to, edge);
    }

    EdgeLabel get_edge_label(size_t from, size_t to) const
    {
        if (!has_edge(from, to))
        {
            return EdgeLabel();
        }
        return matrix_.get(from * vertex_count_ + to).label;
    }

    void set_vertex_label(size_t vertex, const VertexLabel &label)
    {
        if (vertex >= vertex_count_)
        {
            return;
        }
        vertex_labels_.set(vertex, label);
    }

    VertexLabel get_vertex_label(size_t vertex) const
    {
        if (vertex >= vertex_count_)
        {
            return VertexLabel();
        }
        return vertex_labels_.get(vertex);
    }

    Vector<VertexLabel> get_vertex_labels() const
    {
        return vertex_labels_;
    }

    size_t find_vertex(const VertexLabel &label) const
    {
        for (size_t i = 0; i < vertex_count_; ++i)
        {
            if (vertex_labels_.get(i) == label)
            {
                return i;
            }
        }
        return vertex_count_;
    }

    void read(std::istream &in)
    {
        size_t n = 0;
        size_t m = 0;
        if (!(in >> n >> m))
        {
            return;
        }
        reset(n);
        for (size_t i = 0; i < n; ++i)
        {
            VertexLabel label;
            if (!(in >> label))
            {
                return;
            }
            set_vertex_label(i, label);
        }
        for (size_t i = 0; i < m; ++i)
        {
            VertexLabel from_label;
            VertexLabel to_label;
            EdgeLabel edge_label;
            if (!(in >> from_label >> to_label >> edge_label))
            {
                return;
            }
            size_t from_idx = find_vertex(from_label);
            size_t to_idx = find_vertex(to_label);
            if (from_idx < vertex_count_ && to_idx < vertex_count_)
            {
                add_edge(from_idx, to_idx, edge_label);
            }
        }
    }

    NeighborIterator neighbors_begin(size_t vertex) const
    {
        return NeighborIterator(this, vertex, 0);
    }

    NeighborIterator neighbors_end(size_t vertex) const
    {
        return NeighborIterator(this, vertex, vertex_count_);
    }
};

#endif