#ifndef GRAPH_H
#define GRAPH_H
#include "vector.h"

template <typename VLabel, typename ELabel>
class Graph
{
public:
    struct Edge
    {
        bool exists;
        ELabel label;

        Edge(): exists(false), label(ELabel()) {}
    };
    
    explicit Graph(size_t vertex_count = 0)
    {
        vertex_labels_.resize(vertex_count);
        adj_matrix_.resize(vertex_count);

        for (size_t i = 0; i < vertex_count; ++i) 
        {
            Vector<Edge> row;
            row.resize(vertex_count);
            adj_matrix_.set(i, row);
        }
    }

    size_t vertex_count() const 
    {
        return vertex_labels_.size();
    }

    size_t add_vertex(const VLabel& label)
    {
        size_t new_index = vertex_labels_.size();
        size_t new_size = new_index + 1;
        vertex_labels_.resize(new_size);
        vertex_labels_.set(new_index, label);

        for (size_t i = 0; i < new_index; ++i)
        {
            Vector<Edge> row = adj_matrix_.get(i);
            row.resize(new_size);
            adj_matrix_.set(i, row);
        }

        Vector<Edge> new_row;
        new_row.resize(new_size);
        adj_matrix_.resize(new_size);
        adj_matrix_.set(new_index, new_row);

        return new_index;
    }

    void remove_vertex(size_t index)
    {
        size_t current_size = vertex_count();
        if (index >= current_size) return;

        for (size_t i = index; i < current_size - 1; ++i)
        {
            vertex_labels_.set(i, vertex_labels_.get(i + 1));
        }
        vertex_labels_.resize(current_size - 1);

        for (size_t i = index; i < current_size - 1; ++i)
        {
            adj_matrix_.set(i, adj_matrix_.get(i + 1));
        }
        adj_matrix_.resize(current_size - 1);

        for (size_t i = 0; i < adj_matrix_.size(); ++i)
        {
            Vector<Edge> row = adj_matrix_.get(i);
            for (size_t j = index; j < row.size() - 1; ++j)
            {
                row.set(j, row.get(j + 1));
            }
            row.resize(row.size() - 1);
            adj_matrix_.set(i, row);
        }
    }

    void add_edge(size_t from, size_t to, const ELabel& label)
    {
        if (from >= vertex_count() || to >= vertex_count()) return;

        Vector<Edge> row = adj_matrix_.get(from);
        Edge e;
        e.exists = true;
        e.label = label;
        row.set(to, e);
        adj_matrix_.set(from, row);
    }

    void remove_edge(size_t from, size_t to)
    {
        if (from >= vertex_count() || to >= vertex_count()) return;

        Vector<Edge> row = adj_matrix_.get(from);
        Edge e = row.get(to);
        e.exists = false;
        row.set(to, e);
        adj_matrix_.set(from, row);
    }

    bool has_edge(size_t from, size_t to) const
    {
        if (from >= vertex_count() || to >= vertex_count()) return false;
        return adj_matrix_.get(from).get(to).exists;
    }

    ELabel get_edge_label(size_t from, size_t to) const
    {
        if (from >= vertex_count() || to >= vertex_count()) return ELabel();
        return adj_matrix_.get(from).get(to).label;
    }

    void set_vertex_label(size_t index, const VLabel& label)
    {
        vertex_labels_.set(index, label);
    }

    VLabel get_vertex_label(size_t index) const
    {
        return vertex_labels_.get(index);
    }

    Vector<VLabel> get_all_vertex_labels() const
    {
        return vertex_labels_;
    }

    class NeighborIterator
    {
    public:
        NeighborIterator(const Graph* graph, size_t source_vertex)
            : graph_(graph), source_(source_vertex), current_index_(0)
        {
            if (source_ >= graph_->vertex_count())
            {
                current_index_ = graph_->vertex_count();
            }
            else
            {
                find_next_valid();
            }
        }

        bool has_next() const
        {
            return current_index_ < graph_->vertex_count();
        }

        size_t next()
        {
            size_t result = current_index_;
            current_index_++;
            find_next_valid();
            return result;
        }

        ELabel current_edge_label() const
        {
             return graph_->adj_matrix_.get(source_).get(current_index_).label;
        }

    private:
        const Graph* graph_;
        size_t source_;
        size_t current_index_;

        void find_next_valid()
        {   
            while (current_index_ < graph_->vertex_count())
            {
                if (graph_->has_edge(source_, current_index_))
                {
                    return;
                }
                current_index_++;
            }
        }
    };

    NeighborIterator get_neighbor_iterator(size_t vertex_index) const
    {
        return NeighborIterator(this, vertex_index);
    }

private:
    Vector<VLabel> vertex_labels_;
    Vector<Vector<Edge>> adj_matrix_;
};

#endif