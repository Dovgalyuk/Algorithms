#ifndef GRAPH_H
#define GRAPH_H

#include "Vector.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

template <typename VertexMark, typename EdgeMark>
class Graph
{
public:
    Graph() {}

    explicit Graph(size_t vertex_count)
    {
        for (size_t i = 0; i < vertex_count; ++i)
            addVertex(std::to_string(i));
    }

    Graph(size_t rows, size_t cols)
    {
        for (size_t r = 0; r < rows; ++r)
            for (size_t c = 0; c < cols; ++c)
                addVertex(std::to_string(r) + "_" + std::to_string(c));

        for (size_t r = 0; r < rows; ++r)
            for (size_t c = 0; c < cols; ++c)
            {
                size_t idx = r * cols + c;
                if (r + 1 < rows) addEdge(getName(idx), getName((r + 1) * cols + c), EdgeMark());
                if (c + 1 < cols) addEdge(getName(idx), getName(r * cols + (c + 1)), EdgeMark());
            }
    }

    void addVertex(const std::string &name)
    {
        if (findIndexNoThrow(name) != names_.size())
            throw std::invalid_argument("Vertex already exists: " + name);

        size_t n = names_.size();
        names_.resize(n + 1);
        names_.set(n, name);
        vertex_marks_.resize(n + 1);
        expandMatrix(n + 1);
    }

    void removeVertex(const std::string &name)
    {
        size_t idx = findIndex(name);
        size_t n = names_.size();

        shrinkMatrix(idx, n - 1);

        Vector<std::string> new_names;
        Vector<VertexMark> new_marks;
        new_names.resize(n - 1);
        new_marks.resize(n - 1);

        size_t new_idx = 0;
        for (size_t i = 0; i < n; ++i)
        {
            if (i == idx) continue;
            new_names.set(new_idx, names_.get(i));
            new_marks.set(new_idx, vertex_marks_.get(i));
            ++new_idx;
        }
        names_ = new_names;
        vertex_marks_ = new_marks;
    }

    void addEdge(const std::string &from, const std::string &to, const EdgeMark &mark)
    {
        size_t i = findIndex(from);
        size_t j = findIndex(to);
        
        Vector<EdgeMark> row = matrix_.get(i);
        row.set(j, mark);
        matrix_.set(i, row);

        Vector<bool> h_row = has_edge_.get(i);
        h_row.set(j, true);
        has_edge_.set(i, h_row);
    }

    void removeEdge(const std::string &from, const std::string &to)
    {
        size_t i = findIndex(from);
        size_t j = findIndex(to);
        Vector<bool> h_row = has_edge_.get(i);
        h_row.set(j, false);
        has_edge_.set(i, h_row);
    }

    bool hasEdge(const std::string &from, const std::string &to) const
    {
        size_t i = findIndexNoThrow(from);
        size_t j = findIndexNoThrow(to);
        if (i == names_.size() || j == names_.size())
            return false;
        return has_edge_.get(i).get(j);
    }

    void setEdgeMark(const std::string &from, const std::string &to, const EdgeMark &mark)
    {
        if (!hasEdge(from, to)) throw std::runtime_error("Edge does not exist");
        size_t i = findIndex(from);
        size_t j = findIndex(to);
        Vector<EdgeMark> row = matrix_.get(i);
        row.set(j, mark);
        matrix_.set(i, row);
    }

    EdgeMark getEdgeMark(const std::string &from, const std::string &to) const
    {
        if (!hasEdge(from, to)) throw std::runtime_error("Edge does not exist");
        size_t i = findIndex(from);
        size_t j = findIndex(to);
        return matrix_.get(i).get(j);
    }

    void setVertexMark(const std::string &name, const VertexMark &mark)
    {
        size_t idx = findIndex(name);
        vertex_marks_.set(idx, mark);
    }

    VertexMark getVertexMark(const std::string &name) const
    {
        size_t idx = findIndex(name);
        return vertex_marks_.get(idx);
    }

    Vector<VertexMark> getVertexMarks() const { return vertex_marks_; }

    Vector<std::string> getVertexNames() const { return names_; }

    class NeighborIterator
    {
    public:
        NeighborIterator(const Vector<bool>& row, const Vector<std::string>& names, size_t start_idx)
            : row_(row), names_(names), current_idx_(start_idx) { advance(); }

        std::string operator*() const { return names_.get(current_idx_); }

        NeighborIterator& operator++() { ++current_idx_; advance(); return *this; }

        bool operator!=(const NeighborIterator& other) const { return current_idx_ != other.current_idx_; }

    private:
        void advance() {
            while (current_idx_ < row_.size() && !row_.get(current_idx_)) ++current_idx_;
        }
        Vector<bool> row_;
        Vector<std::string> names_;
        size_t current_idx_;
    };

    NeighborIterator neighborsBegin(const std::string &name) const
    {
        size_t idx = findIndex(name);
        return NeighborIterator(has_edge_.get(idx), names_, 0);
    }

    NeighborIterator neighborsEnd(const std::string &name) const
    {
        size_t idx = findIndex(name);
        return NeighborIterator(has_edge_.get(idx), names_, has_edge_.get(idx).size());
    }

    friend std::istream &operator>>(std::istream &is, Graph &g)
    {
        Graph temp;
        size_t v_count;
        if (!(is >> v_count)) return is;

        for (size_t i = 0; i < v_count; ++i) {
            std::string name;
            is >> name;
            temp.addVertex(name);
        }

        size_t e_count;
        if (!(is >> e_count)) return is;

        for (size_t i = 0; i < e_count; ++i) {
            std::string from, to;
            EdgeMark mark;
            is >> from >> to >> mark;
            temp.addEdge(from, to, mark);
        }

        g = temp;
        return is;
    }

private:
    Vector<std::string> names_;
    Vector<VertexMark> vertex_marks_;
    Vector<Vector<EdgeMark>> matrix_;
    Vector<Vector<bool>> has_edge_;

    size_t findIndexNoThrow(const std::string &name) const
    {
        for (size_t i = 0; i < names_.size(); ++i)
            if (names_.get(i) == name) return i;
        return names_.size();
    }

    size_t findIndex(const std::string &name) const
    {
        size_t idx = findIndexNoThrow(name);
        if (idx == names_.size())
            throw std::invalid_argument("Vertex not found: " + name);
        return idx;
    }

    std::string getName(size_t index) const { return names_.get(index); }

    void expandMatrix(size_t new_size)
    {
        matrix_.resize(new_size);
        has_edge_.resize(new_size);
        for (size_t i = 0; i < new_size; ++i)
        {
            Vector<EdgeMark> row = matrix_.get(i);
            row.resize(new_size);
            matrix_.set(i, row);

            Vector<bool> h_row = has_edge_.get(i);
            h_row.resize(new_size);
            has_edge_.set(i, h_row);
        }
    }

    void shrinkMatrix(size_t remove_idx, size_t new_size)
    {
        Vector<Vector<EdgeMark>> new_matrix;
        Vector<Vector<bool>> new_has_edge;
        new_matrix.resize(new_size);
        new_has_edge.resize(new_size);

        size_t new_i = 0;
        for (size_t i = 0; i < matrix_.size(); ++i)
        {
            if (i == remove_idx) continue;
            Vector<EdgeMark> new_row;
            Vector<bool> new_h_row;
            new_row.resize(new_size);
            new_h_row.resize(new_size);

            size_t new_j = 0;
            for (size_t j = 0; j < matrix_.get(i).size(); ++j)
            {
                if (j == remove_idx) continue;
                new_row.set(new_j, matrix_.get(i).get(j));
                new_h_row.set(new_j, has_edge_.get(i).get(j));
                ++new_j;
            }
            new_matrix.set(new_i, new_row);
            new_has_edge.set(new_i, new_h_row);
            ++new_i;
        }
        matrix_ = new_matrix;
        has_edge_ = new_has_edge;
    }
};

#endif