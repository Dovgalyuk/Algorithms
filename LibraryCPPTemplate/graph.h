#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

#include "list.h"
#include "vector.h"

template <typename VertexLabel, typename EdgeLabel> class Graph
{
public:
    using Vertex = std::size_t;

    struct Edge
    {
        Vertex to;
        EdgeLabel label;
    };

    class NeighbourIterator
    {
    public:
        explicit NeighbourIterator(typename List<Edge>::Item* item)
            : m_item(item)
        {}

        bool valid() const { return m_item != nullptr; }

        void next()
        {
            if (m_item)
            {
                m_item = m_item->next();
            }
        }

        Vertex vertex() const
        {
            if (!m_item)
            {
                throw std::out_of_range("Iterator is not valid");
            }
            return m_item->data().to;
        }

        const EdgeLabel& edgeLabel() const
        {
            if (!m_item)
            {
                throw std::out_of_range("Iterator is not valid");
            }
            return m_item->data().label;
        }

    private:
        typename List<Edge>::Item* m_item;
    };

    explicit Graph(Vertex vertexCount = 0)
        : m_vertices(vertexCount)
        , m_adjacency(vertexCount)
    {
    }

    Vertex addVertex(const VertexLabel& label = VertexLabel())
    {
        const Vertex index = m_vertices.size();
        m_vertices.resize(index + 1);
        m_vertices.set(index, label);

        m_adjacency.resize(index + 1);
        return index;
    }

    void addEdge(Vertex from, Vertex to, const EdgeLabel& label = EdgeLabel())
    {
        checkVertex(from);
        checkVertex(to);

        Edge* existing = findEdge(from, to);
        if (existing)
        {
            existing->label = label;
            return;
        }

        m_adjacency[from].insert({ to, label });
    }

    void removeEdge(Vertex from, Vertex to)
    {
        checkVertex(from);
        checkVertex(to);

        auto& adjacency = m_adjacency[from];
        typename List<Edge>::Item* prev = nullptr;
        for (auto* item = adjacency.first(); item; item = item->next())
        {
            if (item->data().to == to)
            {
                adjacency.erase_next(prev);
                return;
            }
            prev = item;
        }
    }

    bool hasEdge(Vertex from, Vertex to) const
    {
        checkVertex(from);
        checkVertex(to);
        return findEdgeConst(from, to) != nullptr;
    }

    void setEdgeLabel(Vertex from, Vertex to, const EdgeLabel& label)
    {
        checkVertex(from);
        checkVertex(to);
        Edge* edge = findEdge(from, to);
        if (!edge)
        {
            throw std::out_of_range("Edge not found");
        }
        edge->label = label;
    }

    EdgeLabel getEdgeLabel(Vertex from, Vertex to) const
    {
        checkVertex(from);
        checkVertex(to);
        const Edge* edge = findEdgeConst(from, to);
        if (!edge)
        {
            throw std::out_of_range("Edge not found");
        }
        return edge->label;
    }

    void setVertexLabel(Vertex vertex, const VertexLabel& label)
    {
        checkVertex(vertex);
        m_vertices[vertex] = label;
    }

    VertexLabel getVertexLabel(Vertex vertex) const
    {
        checkVertex(vertex);
        return m_vertices[vertex];
    }

    void removeVertex(Vertex vertex)
    {
        checkVertex(vertex);

        for (Vertex i = 0; i < m_adjacency.size(); ++i)
        {
            removeEdgesTo(m_adjacency[i], vertex);
        }

        const Vertex lastIndex = m_vertices.size() - 1;
        if (vertex != lastIndex)
        {
            for (Vertex i = 0; i < m_adjacency.size(); ++i)
            {
                replaceDestination(m_adjacency[i], lastIndex, vertex);
            }

            List<Edge> moved = m_adjacency[lastIndex];
            adjustSelfReferences(moved, lastIndex, vertex);
            m_adjacency[vertex] = moved;
            m_vertices[vertex] = m_vertices[lastIndex];
        }

        m_vertices.resize(lastIndex);
        m_adjacency.resize(lastIndex);
    }

    Vector<VertexLabel> getAllVertexLabels() const
    {
        Vector<VertexLabel> result(m_vertices.size());
        for (Vertex i = 0; i < m_vertices.size(); ++i)
        {
            result.set(i, m_vertices[i]);
        }
        return result;
    }

    NeighbourIterator neighbours(Vertex vertex)
    {
        checkVertex(vertex);
        return NeighbourIterator(m_adjacency[vertex].first());
    }

    NeighbourIterator neighbours(Vertex vertex) const
    {
        checkVertex(vertex);
        return NeighbourIterator(m_adjacency[vertex].first());
    }

    Vertex verticesCount() const
    {
        return m_vertices.size();
    }

private:
    void checkVertex(Vertex vertex) const
    {
        if (vertex >= m_vertices.size())
        {
            throw std::out_of_range("Vertex index out of range");
        }
    }

    Edge* findEdge(Vertex from, Vertex to)
    {
        auto& adjacency = m_adjacency[from];
        for (auto* item = adjacency.first(); item; item = item->next())
        {
            if (item->data().to == to)
            {
                return &item->data();
            }
        }
        return nullptr;
    }

    const Edge* findEdgeConst(Vertex from, Vertex to) const
    {
        const auto& adjacency = m_adjacency[from];
        for (auto* item = adjacency.first(); item; item = item->next())
        {
            if (item->data().to == to)
            {
                return &item->data();
            }
        }
        return nullptr;
    }

    static void removeEdgesTo(List<Edge>& adjacency, Vertex target)
    {
        typename List<Edge>::Item* prev = nullptr;
        for (auto* item = adjacency.first(); item;)
        {
            if (item->data().to == target)
            {
                item = adjacency.erase_next(prev);
            }
            else
            {
                prev = item;
                item = item->next();
            }
        }
    }

    static void replaceDestination(List<Edge>& adjacency, Vertex from, Vertex to)
    {
        for (auto* item = adjacency.first(); item; item = item->next())
        {
            if (item->data().to == from)
            {
                item->data().to = to;
            }
        }
    }

    static void adjustSelfReferences(List<Edge>& adjacency, Vertex from, Vertex to)
    {
        replaceDestination(adjacency, from, to);
    }

    Vector<VertexLabel> m_vertices;
    Vector<List<Edge>> m_adjacency;
};

#endif