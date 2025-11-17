#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

template<typename Vertex, typename Edge>
class Graph 
{
    Vector<Vertex> vers;
    Vector<Vector<Edge>> matrix;

    Edge empty_val{};

public: 
    Graph() = default;

    Graph(size_t n, const Vertex& def_vertex = Vertex()){
        for(size_t i = 0; i < n; i++)
            add_vertex(def_vertex);
    }

    size_t add_vertex(const Vertex& a)
    {
        vers.push_back(a);

        for(size_t i = 0; i < matrix.size(); i++)
            matrix[i].push_back(empty_val);

        Vector<Edge> new_row;
        for(size_t i = 0; i < vers.size(); i++)
            new_row.push_back(empty_val);

        matrix.push_back(new_row);

        return vers.size() - 1;
    }

    void rem_vertex(size_t index)
    {
        size_t n = vers.size();
        if(index >= n) throw std::out_of_range("Ver index out of range");

        matrix.erase(index);

        for(size_t i = 0; i < matrix.size(); i++)
            matrix[i].erase(index);

        vers.erase(index);
    }

    Vertex& get_vertex(size_t index) { return vers[index]; }

    const Vertex& get_vertex(size_t index) const { return vers[index]; }

    void set_vertex(size_t index, const Vertex& a) { vers[index] = a; }

    size_t vertex_count() const { return vers.size(); }

    Vector<Vertex> get_all_vertex() const { return vers; }

    void rem_edge(size_t from, size_t to)
    {
        if(from >= vers.size() || to >= vers.size())
            throw std::out_of_range("index out of range");
        matrix[from][to] = empty_val;
    }

    bool has_edge(size_t from, size_t to) const
    {
        if(from >= vers.size() || to >= vers.size())
            return false;
        return matrix[from][to] != empty_val;
    }

    Edge& get_edge(size_t from, size_t to)
    {
        if(from >= vers.size() || to >= vers.size()) 
            throw std::out_of_range("index out of range");
        return matrix[from][to];
    }

    void set_edge(size_t from, size_t to, const Edge& a)
    {
        if(from >= vers.size() || to >= vers.size()) 
            throw std::out_of_range("index out of range");
        matrix[from][to] = a;
    }

    class NIterator 
    {
        const Vector<Vector<Edge>>& matr;
        size_t row;
        size_t col;
        const Edge* empty;

        void skip()
        {
            while(col < matr[row].size() && matr[row][col] == *empty)
                ++col;
        }

    public: 
        NIterator(const Vector<Vector<Edge>>& a, size_t r, size_t c, const Edge* e) : matr(a), row(r), col(c), empty(e)
        {
            skip();
        }

        size_t operator*() const { return col; }

        NIterator& operator++()
        {
            ++col;
            skip();
            return *this;
        }

        bool operator!=(const NIterator& a) const
        {
            return row!= a.row || col != a.col || empty != a.empty;
        }
    };

    NIterator begin_neig(size_t v) const 
    {
        return NIterator(matrix, v, 0, &empty_val);
    }

    NIterator end_neig(size_t v) const 
    {
        return NIterator(matrix, v, matrix[v].size(), &empty_val);
    }
};

#endif