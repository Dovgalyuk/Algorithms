#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <istream>
#include <map>
#include <stdexcept>
#include <utility>
#include <string>

#include "vector.h"

template <typename VertexLabel, typename EdgeLabel>
class Graph
{
public:
    using IndexType = std::size_t;
    using IndexMap = std::map<VertexLabel, IndexType>;
    using Labels = Vector<VertexLabel>;

    class NeighborIterator
    {
    public:
        using value_type = std::pair<IndexType, EdgeLabel>;

        NeighborIterator() : graph_(nullptr), vertex_(0), current_(0) {}
        NeighborIterator(const Graph* g, IndexType v, IndexType start) 
            : graph_(g), vertex_(v), current_(start) 
        {
            skip_empty();
        }

        bool operator!=(const NeighborIterator& other) const { return current_ != other.current_; }
        bool operator==(const NeighborIterator& other) const { return current_ == other.current_; }

        NeighborIterator& operator++()
        {
            ++current_;
            skip_empty();
            return *this;
        }

        value_type operator*() const
        {
            return value_type(current_, graph_->edge_labels_.get(vertex_).get(current_));
        }

    private:
        void skip_empty()
        {
            while (current_ < graph_->vertex_count() && !graph_->has_edge(vertex_, current_))
                ++current_;
        }

        const Graph* graph_;
        IndexType vertex_;
        IndexType current_;
    };

    Graph() = default;
    explicit Graph(IndexType vertex_count) { resize(vertex_count); }
    Graph(IndexType rows, IndexType cols) : Graph(rows * cols) { build_grid(rows, cols); }

    IndexType vertex_count() const { return names_.size(); }

    void resize(IndexType new_count)
    {
        IndexType old_count = names_.size();
        if (new_count <= old_count) return;

        names_.resize(new_count);
        has_edge_.resize(new_count);
        edge_labels_.resize(new_count);

        for (IndexType i = 0; i < new_count; ++i)
        {
            has_edge_.get(i).resize(new_count);
            edge_labels_.get(i).resize(new_count);
            
            for (IndexType j = 0; j < new_count; ++j)
            {
                has_edge_.get(i).set(j, false);
                edge_labels_.get(i).set(j, EdgeLabel());
            }
        }
    }

    IndexType add_vertex(const VertexLabel& name, const VertexLabel& label = VertexLabel())
    {
        IndexType id = names_.size();
        resize(id + 1);
        names_.set(id, name);
        return id;
    }

    void remove_vertex(IndexType vertex)
    {
        check_vertex(vertex);
        IndexType n = names_.size();
        if (n == 0) return;

        for (IndexType i = vertex; i < n - 1; ++i)
        {
            names_.set(i, names_.get(i + 1));
            for (IndexType j = 0; j < n; ++j)
            {
                has_edge_.get(i).set(j, has_edge_.get(i + 1).get(j));
                edge_labels_.get(i).set(j, edge_labels_.get(i + 1).get(j));
            }
        }

        for (IndexType j = vertex; j < n - 1; ++j)
        {
            for (IndexType i = 0; i < n - 1; ++i)
            {
                has_edge_.get(i).set(j, has_edge_.get(i).get(j + 1));
                edge_labels_.get(i).set(j, edge_labels_.get(i).get(j + 1));
            }
        }

        names_.resize(n - 1);
        has_edge_.resize(n - 1);
        edge_labels_.resize(n - 1);
        for (IndexType i = 0; i < n - 1; ++i)
        {
            has_edge_.get(i).resize(n - 1);
            edge_labels_.get(i).resize(n - 1);
        }
    }

    void add_edge(IndexType from, IndexType to, const EdgeLabel& label = EdgeLabel())
    {
        check_vertex(from);
        check_vertex(to);
        has_edge_.get(from).set(to, true);
        edge_labels_.get(from).set(to, label);
    }

    void remove_edge(IndexType from, IndexType to)
    {
        check_vertex(from);
        check_vertex(to);
        has_edge_.get(from).set(to, false);
        edge_labels_.get(from).set(to, EdgeLabel());
    }

    bool has_edge(IndexType from, IndexType to) const
    {
        check_vertex(from);
        check_vertex(to);
        return has_edge_.get(from).get(to);
    }

    EdgeLabel edge_label(IndexType from, IndexType to) const
    {
        check_vertex(from);
        check_vertex(to);
        if (!has_edge(from, to)) throw std::logic_error("Edge does not exist");
        return edge_labels_.get(from).get(to);
    }

    void set_edge_label(IndexType from, IndexType to, const EdgeLabel& label)
    {
        check_vertex(from);
        check_vertex(to);
        if (!has_edge(from, to)) throw std::logic_error("Edge does not exist");
        edge_labels_.get(from).set(to, label);
    }

    void set_vertex_label(IndexType vertex, const VertexLabel& label)
    {
        check_vertex(vertex);
        names_.set(vertex, label);
    }

    VertexLabel vertex_label(IndexType vertex) const
    {
        check_vertex(vertex);
        return names_.get(vertex);
    }

    Labels vertex_labels() const { return names_; }

    NeighborIterator begin(IndexType vertex) const
    {
        check_vertex(vertex);
        return NeighborIterator(this, vertex, 0);
    }

    NeighborIterator end(IndexType) const 
    { 
        return NeighborIterator(this, 0, vertex_count()); 
    }

    bool read(std::istream& input)
    {
        IndexType n = 0;
        if (!(input >> n)) return false;

        Graph parsed(n);
        IndexMap index;
        for (IndexType i = 0; i < n; ++i)
        {
            VertexLabel name;
            if (!(input >> name)) return false;
            if (index.count(name)) return false;
            index[name] = i;
            parsed.set_vertex_label(i, name);
        }

        IndexType m = 0;
        if (!(input >> m)) return false;
        for (IndexType i = 0; i < m; ++i)
        {
            VertexLabel from_name, to_name;
            EdgeLabel label;
            if (!(input >> from_name >> to_name >> label)) return false;
            auto from_it = index.find(from_name);
            auto to_it   = index.find(to_name);
            if (from_it == index.end() || to_it == index.end()) return false;
            parsed.add_edge(from_it->second, to_it->second, label);
        }

        *this = parsed;
        return true;
    }

private:
    void check_vertex(IndexType vertex) const
    {
        if (vertex >= names_.size())
            throw std::out_of_range("Vertex index out of range");
    }

    void build_grid(IndexType rows, IndexType cols)
    {
        for (IndexType r = 0; r < rows; ++r)
            for (IndexType c = 0; c < cols; ++c)
            {
                IndexType u = r * cols + c;
                if (c + 1 < cols) add_edge(u, u + 1, EdgeLabel());
                if (r + 1 < rows) add_edge(u, u + cols, EdgeLabel());
            }
    }

    Vector<VertexLabel> names_;
    Vector<Vector<bool>> has_edge_;
    Vector<Vector<EdgeLabel>> edge_labels_;
};

#endif