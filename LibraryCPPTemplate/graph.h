#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <istream>
#include <map>
#include <stdexcept>
#include "vector.h"

template <typename EdgeLabel, typename VertexLabel> class Graph
{
public:
    class NeighborIterator
    {
    public:
        NeighborIterator(const Graph *graph, size_t vertex, size_t neighbor)
            : graph_(graph), vertex_(vertex), neighbor_(neighbor) { skip_missing_edges(); }

        size_t operator*() const { return neighbor_; }

        NeighborIterator &operator++()
        {
            ++neighbor_;
            skip_missing_edges();
            return *this;
        }

        bool operator!=(const NeighborIterator &other) const
        {
            return graph_ != other.graph_ || vertex_ != other.vertex_ || neighbor_ != other.neighbor_;
        }

    private:
        void skip_missing_edges()
        {
            while (neighbor_ < graph_->size()
                   && !graph_->has_edge(vertex_, neighbor_)
                   && !graph_->has_edge(neighbor_, vertex_))
                ++neighbor_;
        }

        const Graph *graph_;
        size_t vertex_;
        size_t neighbor_;
    };

    Graph() : size_(0) {}
    explicit Graph(size_t count) : size_(0) { resize(count); }
    Graph(size_t rows, size_t columns) : size_(0) { resize_grid(rows, columns); }

    size_t size() const { return size_; }

    void resize(size_t count)
    {
        if (count != 0 && count > static_cast<size_t>(-1) / count)
            throw std::length_error("Graph is too large");

        Matrix new_matrix;
        new_matrix.resize(count * count);
        size_t preserved = count < size_ ? count : size_;
        for (size_t i = 0; i < preserved; ++i)
            for (size_t j = 0; j < preserved; ++j)
                new_matrix.set(i * count + j, matrix_.get(i * size_ + j));

        vertices_.resize(count);
        matrix_.swap(new_matrix);
        size_ = count;
    }

    void resize_grid(size_t rows, size_t columns)
    {
        if (columns != 0 && rows > static_cast<size_t>(-1) / columns)
            throw std::length_error("Graph grid is too large");
        resize(rows * columns);
    }

    size_t add_vertex()
    {
        if (size_ == static_cast<size_t>(-1))
            throw std::length_error("Graph is too large");
        size_t index = size_;
        resize(size_ + 1);
        return index;
    }

    size_t add_vertex(const VertexLabel &label)
    {
        size_t index = add_vertex();
        set_vertex_label(index, label);
        return index;
    }

    void remove_vertex(size_t vertex)
    {
        check_vertex(vertex);
        Matrix new_matrix;
        new_matrix.resize((size_ - 1) * (size_ - 1));

        for (size_t i = 0, new_i = 0; i < size_; ++i)
        {
            if (i == vertex)
                continue;
            for (size_t j = 0, new_j = 0; j < size_; ++j)
            {
                if (j == vertex)
                    continue;
                new_matrix.set(new_i * (size_ - 1) + new_j, matrix_.get(i * size_ + j));
                ++new_j;
            }
            ++new_i;
        }

        for (size_t i = vertex; i + 1 < size_; ++i)
            vertices_.set(i, vertices_.get(i + 1));
        vertices_.resize(size_ - 1);
        matrix_.swap(new_matrix);
        --size_;
    }

    void add_edge(size_t from, size_t to, const EdgeLabel &label)
    {
        check_vertex(from);
        check_vertex(to);
        Cell cell(label);
        matrix_.set(from * size_ + to, cell);
    }

    void remove_edge(size_t from, size_t to)
    {
        check_vertex(from);
        check_vertex(to);
        matrix_.set(from * size_ + to, Cell());
    }

    bool has_edge(size_t from, size_t to) const
    {
        check_vertex(from);
        check_vertex(to);
        return matrix_.get(from * size_ + to).label != nullptr;
    }

    EdgeLabel edge_label(size_t from, size_t to) const
    {
        check_vertex(from);
        check_vertex(to);
        Cell cell = matrix_.get(from * size_ + to);
        if (cell.label == nullptr)
            throw std::logic_error("Edge does not exist");
        return *cell.label;
    }

    void set_edge_label(size_t from, size_t to, const EdgeLabel &label)
    {
        check_vertex(from);
        check_vertex(to);
        Cell cell = matrix_.get(from * size_ + to);
        if (cell.label == nullptr)
            throw std::logic_error("Edge does not exist");
        *cell.label = label;
        matrix_.set(from * size_ + to, cell);
    }

    void set_vertex_label(size_t vertex, const VertexLabel &label)
    {
        check_vertex(vertex);
        vertices_.set(vertex, label);
    }

    VertexLabel vertex_label(size_t vertex) const
    {
        check_vertex(vertex);
        return vertices_.get(vertex);
    }

    Vector<VertexLabel> vertex_labels() const { return vertices_; }

    NeighborIterator begin(size_t vertex) const
    {
        check_vertex(vertex);
        return NeighborIterator(this, vertex, 0);
    }

    NeighborIterator end(size_t vertex) const
    {
        check_vertex(vertex);
        return NeighborIterator(this, vertex, size_);
    }

    bool read(std::istream &input)
    {
        size_t count;
        size_t edge_count;
        if (!(input >> count >> edge_count))
            return false;

        Graph parsed(count);
        typedef std::map<VertexLabel, size_t> NameIndex;
        NameIndex name_index;
        for (size_t i = 0; i < count; ++i)
        {
            VertexLabel label;
            if (!(input >> label) || name_index.count(label) != 0)
                return false;
            parsed.set_vertex_label(i, label);
            name_index[label] = i;
        }

        for (size_t i = 0; i < edge_count; ++i)
        {
            VertexLabel from_label;
            VertexLabel to_label;
            EdgeLabel label;
            if (!(input >> from_label >> to_label >> label))
                return false;
            typename NameIndex::const_iterator from = name_index.find(from_label);
            typename NameIndex::const_iterator to = name_index.find(to_label);
            if (from == name_index.end() || to == name_index.end())
                return false;
            parsed.add_edge(from->second, to->second, label);
        }

        *this = parsed;
        return true;
    }

private:
    struct Cell
    {
        Cell() : label(nullptr) {}
        explicit Cell(const EdgeLabel &value) : label(new EdgeLabel(value)) {}
        Cell(const Cell &other)
            : label(other.label == nullptr ? nullptr : new EdgeLabel(*other.label)) {}
        Cell &operator=(const Cell &other)
        {
            if (this != &other)
            {
                EdgeLabel *new_label = other.label == nullptr ? nullptr : new EdgeLabel(*other.label);
                delete label;
                label = new_label;
            }
            return *this;
        }
        ~Cell() { delete label; }

        EdgeLabel *label;
    };

    typedef Vector<Cell> Matrix;

    void check_vertex(size_t vertex) const
    {
        if (vertex >= size_)
            throw std::out_of_range("Graph vertex out of range");
    }

    size_t size_;
    Vector<VertexLabel> vertices_;
    Vector<Cell> matrix_;
};

#endif
