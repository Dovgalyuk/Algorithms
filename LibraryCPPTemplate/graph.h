#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"

template<typename Vertex, typename Edge>
class Graph 
{
    typedef Vector<Vertex> VertexContainer;
    typedef Vector<Vector<Edge>> Matrix;
    typedef Vector<Vector<bool>> Exist;

    VertexContainer vers;
    Matrix matrix;
    Exist ex;

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
        {
            matrix[i].push_back(Edge{});
            ex[i].push_back(false);
        }
        Vector<Edge> new_row;
        Vector<bool> new_row_ex;
        for(size_t i = 0; i < vers.size(); i++)
        {
            new_row.push_back(Edge{});
            new_row_ex.push_back(false);
        }
        matrix.push_back(new_row);
        ex.push_back(new_row_ex);

        return vers.size() - 1;
    }

    void rem_vertex(size_t index)
    {
        size_t n = vers.size();
        if(index >= n) throw std::out_of_range("Ver index out of range");

        matrix.erase(index);
        ex.erase(index);

        for(size_t i = 0; i < matrix.size(); i++)
        {
            matrix[i].erase(index);
            ex[i].erase(index);
        }

        vers.erase(index);
    }

    Vertex& get_vertex(size_t index) { return vers[index]; }

    const Vertex& get_vertex(size_t index) const { return vers[index]; }

    void set_vertex(size_t index, const Vertex& a) { vers[index] = a; }

    size_t vertex_count() const { return vers.size(); }

    VertexContainer get_all_vertex() const { return vers; }

    void rem_edge(size_t from, size_t to)
    {
        if(from >= vers.size() || to >= vers.size())
            throw std::out_of_range("index out of range");

        ex[from][to] = false;
    }

    bool has_edge(size_t from, size_t to) const
    {
        if(from >= vers.size() || to >= vers.size())
            return false;

        return ex[from][to];
    }

    Edge& get_edge(size_t from, size_t to)
    {
        if(from >= vers.size() || to >= vers.size()) 
            throw std::out_of_range("index out of range");

        if(!ex[from][to])
            throw std::logic_error("Not exist");

        return matrix[from][to];
    }

    void set_edge(size_t from, size_t to, const Edge& a)
    {
        if(from >= vers.size() || to >= vers.size()) 
            throw std::out_of_range("index out of range");

        matrix[from][to] = a;
        ex[from][to] = true;
    }

    class NIterator 
    {
        const Exist& exists;
        size_t row;
        size_t col;

        void skip()
        {
            while(col < exists[row].size() && !exists[row][col])
                ++col;
        }

    public: 
        NIterator(const Exist& a, size_t r, size_t c) : exists(a), row(r), col(c)
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
            return row!= a.row || col != a.col;
        }
    };

    NIterator begin_neig(size_t v) const 
    {
        return NIterator(ex, v, 0);
    }

    NIterator end_neig(size_t v) const 
    {
        return NIterator(ex, v, ex[v].size());
    }
};

#endif