#ifndef LIBRARYCPP_TEMPLATE_GRAPH_H
#define LIBRARYCPP_TEMPLATE_GRAPH_H

#include <stdexcept>
#include <string>
#include <limits>
#include <utility>

#include "vector.h"

template <typename V, typename E>
class Graph
{
public:

    class Iterator
    {
    public:
        Iterator(const Graph* g, size_t from, size_t pos)
            : graph(g), from_vertex(from), pos(pos)
        {
            advance();
        }

        size_t operator*() const { return pos; }

        Iterator& operator++()
        {
            ++pos;
            advance();
            return *this;
        }

        bool operator!=(const Iterator& other) const
        {
            return pos != other.pos;
        }

    private:
        void advance()
        {
            while (pos < graph->m_v &&
                   !graph->m_adj.get(from_vertex).get(pos))
                ++pos;
        }

        const Graph* graph;
        size_t from_vertex;
        size_t pos;
    };

    explicit Graph(size_t n = 0)
        : m_v(n)
    {
        m_VertexLabels.resize(m_v);
        m_adj.resize(m_v);
        m_EdgesLabels.resize(m_v);
        for (size_t i = 0; i < m_v; ++i) {
            m_adj.get(i).resize(m_v);
            m_EdgesLabels.get(i).resize(m_v);
            for (size_t j = 0; j < m_v; ++j) {
                m_adj.get(i).set(j, false);
            }
        }
    }

    // Количество вершин
    size_t size() const { return m_v; }

    // Добавить вершину
    // Возвращает индекс новой вершины
    size_t addVertex()
    {
        size_t old_size = m_v;
        size_t new_size = m_v + 1;

        std::cout << m_adj.size() << std::endl;

        m_VertexLabels.resize(new_size);
        m_adj.resize(new_size);
        m_EdgesLabels.resize(new_size);

        for (size_t i = 0; i < old_size; ++i) {
            m_adj.get(i).resize(new_size);
            m_EdgesLabels.get(i).resize(new_size);
            m_adj.get(i).set(old_size, false);
        }

        m_adj.get(old_size).resize(new_size);
        m_EdgesLabels.get(old_size).resize(new_size);  

        for (size_t i = 0; i < new_size; ++i)
            m_adj.get(old_size).set(i, false);

        m_v = new_size;
        return old_size;
    }

    // Добавить ребро
    void addEdge(size_t from, size_t to, const E& label = E())
    {
        check_vertex(from);
        check_vertex(to);
        m_adj.get(from).set(to, true);
        m_EdgesLabels.get(from).set(to, label);
    }

    // Удалить ребро
    void removeEdge(size_t from, size_t to)
    {
        check_vertex(from);
        check_vertex(to);
        m_adj.get(from).set(to, false);
    }

    // Существует ли ребро
    bool edgeExists(size_t from, size_t to) const
    {
        check_vertex(from);
        check_vertex(to);
        return m_adj.get(from).get(to);
    }

    // Задать пометку ребра
    void setEdgeLabel(size_t from, size_t to, const E& label)
    {
        check_vertex(from);
        check_vertex(to);
        m_adj.get(from).set(to, true);
        m_EdgesLabels.get(from).set(to, label);
    }

    // Считать пометку ребра
    E getEdgeLabel(size_t from, size_t to) const
    {
        check_vertex(from);
        check_vertex(to);
        return m_EdgesLabels.get(from).get(to);
    }

    // Задать пометку вершины
    void setVertexLabel(size_t v, const V& label)
    {
        check_vertex(v);
        m_VertexLabels.set(v, label);
    }

    // Считать пометку вершины
    V getVertexLabel(size_t v) const
    {
        check_vertex(v);
        return m_VertexLabels.get(v);
    }

    // Удалить вершину
    void removeVertex(size_t idx)
    {
        check_vertex(idx);
        size_t new_size = m_v - 1;

        Vector<Vector<bool>> new_adj;
        Vector<Vector<E>> new_edges;
        Vector<V> new_vertexEdges;

        new_adj.resize(new_size);
        new_edges.resize(new_size);
        new_vertexEdges.resize(new_size);

        for (size_t i = 0, oi = 0; i < m_v; ++i) {
            if (i == idx) continue;
            new_vertexEdges.set(oi, m_VertexLabels.get(i));
            new_adj.get(oi).resize(new_size);
            new_edges.get(oi).resize(new_size);
            for (size_t j = 0, oj = 0; j < m_v; ++j) {
                if (j == idx) continue;
                new_adj.get(oi).set(oj, m_adj.get(i).get(j));
                new_edges.get(oi).set(oj, m_EdgesLabels.get(i).get(j));
                ++oj;
            }
            ++oi;
        }

        m_adj = new_adj;
        m_EdgesLabels = new_edges;
        m_VertexLabels = new_vertexEdges;
        m_v = new_size;
    }

    // Получить пометки всех вершин в виде вектора
    Vector<V> getAllVertexLabels() const
    {
        return m_VertexLabels;
    }

    Iterator neighbors_begin(size_t v) const
    {
        check_vertex(v);
        return Iterator(this, v, 0);
    }

    Iterator neighbors_end(size_t v) const
    {
        check_vertex(v);
        return Iterator(this, v, m_v);
    }

private:
    void check_vertex(size_t vertex) const
    {
        if (vertex >= m_v) {
            throw std::out_of_range("Vertex out of range");
        }
    }

    size_t m_v = 0;
    Vector<Vector<bool>> m_adj;
    Vector<Vector<E>> m_EdgesLabels;
    Vector<V> m_VertexLabels;
};

#endif // LIBRARYCPP_TEMPLATE_GRAPH_H
