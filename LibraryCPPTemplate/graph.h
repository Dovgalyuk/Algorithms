#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include "vector.h"

template <typename VertexData, typename EdgeData> class Graph
{
public:
    struct Iterator
    {
        const Graph* graph;
        size_t from;
        size_t index;

        Iterator(const Graph* g, size_t v) : graph(g), from(v), index(0)
        {
            move_to_next();
        }

        bool valid() const
        {
            return (graph != nullptr) && (index < graph->verticesCount());
        }

        void next()
        {
            if (graph == nullptr)
                return;
            index++;
            move_to_next();
        }

        size_t vertex() const
        {
            return index;
        }

        EdgeData edgeData() const
        {
            return graph->getEdgeData(from, index);
        }

    private:
        void move_to_next()
        {
            if (!graph)
                return;
            while (index < graph->verticesCount() && !graph->hasEdge(from, index))
            {
                index++;
            }
        }
    };

    explicit Graph(size_t verticesCount = 0) : m_vertexCount(0)
    {
        init(verticesCount);
    }

    Graph(const Graph& other)
        : m_vertexCount(other.m_vertexCount),
        m_vertexData(other.m_vertexData),
        m_adj(other.m_adj),
        m_edgeData(other.m_edgeData)
    {
    }

    Graph& operator=(const Graph& other)
    {
        if (this != &other)
        {
            m_vertexCount = other.m_vertexCount;
            m_vertexData = other.m_vertexData;
            m_adj = other.m_adj;
            m_edgeData = other.m_edgeData;
        }
        return *this;
    }

    ~Graph() {}

    size_t verticesCount() const
    {
        return m_vertexCount;
    }

    size_t addVertex()
    {
        size_t oldN = m_vertexCount;
        size_t newN = oldN + 1;

        Vector<bool> newAdj;
        newAdj.resize(newN * newN);
        for (size_t i = 0; i < newN * newN; i++)
        {
            newAdj.set(i, false);
        }

        Vector<EdgeData> newEdgeData;
        newEdgeData.resize(newN * newN);

        for (size_t i = 0; i < oldN; i++)
        {
            for (size_t j = 0; j < oldN; j++)
            {
                bool has = m_adj.get(i * oldN + j);
                newAdj.set(i * newN + j, has);
                if (has)
                {
                    newEdgeData.set(i * newN + j, m_edgeData.get(i * oldN + j));
                }
            }
        }

        m_adj = newAdj;
        m_edgeData = newEdgeData;

        m_vertexData.resize(newN);
        m_vertexCount = newN;

        return oldN;
    }

    void removeVertex(size_t v)
    {
        if (v >= m_vertexCount)
            return;

        size_t oldN = m_vertexCount;
        size_t newN = oldN - 1;

        Vector<bool> newAdj;
        Vector<EdgeData> newEdgeData;
        newAdj.resize(newN * newN);
        newEdgeData.resize(newN * newN);

        for (size_t i = 0; i < oldN; i++)
        {
            if (i == v)
                continue;
            size_t new_i = (i < v) ? i : (i - 1);
            for (size_t j = 0; j < oldN; j++)
            {
                if (j == v)
                    continue;
                size_t new_j = (j < v) ? j : (j - 1);
                bool has = m_adj.get(i * oldN + j);
                newAdj.set(new_i * newN + new_j, has);
                if (has)
                {
                    newEdgeData.set(new_i * newN + new_j,
                        m_edgeData.get(i * oldN + j));
                }
            }
        }

        Vector<VertexData> newVertexData;
        newVertexData.resize(newN);
        size_t idx = 0;
        for (size_t i = 0; i < oldN; i++)
        {
            if (i == v)
                continue;
            newVertexData.set(idx, m_vertexData.get(i));
            idx++;
        }

        m_adj = newAdj;
        m_edgeData = newEdgeData;
        m_vertexData = newVertexData;
        m_vertexCount = newN;
    }

    void addEdge(size_t from, size_t to)
    {
        if (from >= m_vertexCount || to >= m_vertexCount)
            return;
        m_adj.set(index(from, to), true);
    }

    void removeEdge(size_t from, size_t to)
    {
        if (from >= m_vertexCount || to >= m_vertexCount)
            return;
        m_adj.set(index(from, to), false);
    }

    bool hasEdge(size_t from, size_t to) const
    {
        if (from >= m_vertexCount || to >= m_vertexCount)
            return false;
        return m_adj.get(index(from, to));
    }

    void setEdgeData(size_t from, size_t to, const EdgeData& data)
    {
        if (from >= m_vertexCount || to >= m_vertexCount)
            return;
        m_adj.set(index(from, to), true);
        m_edgeData.set(index(from, to), data);
    }

    EdgeData getEdgeData(size_t from, size_t to) const
    {
        return m_edgeData.get(index(from, to));
    }

    void setVertexData(size_t v, const VertexData& data)
    {
        if (v >= m_vertexCount)
            return;
        m_vertexData.set(v, data);
    }

    VertexData getVertexData(size_t v) const
    {
        return m_vertexData.get(v);
    }

    Vector<VertexData> getAllVertexData() const
    {
        return m_vertexData;
    }

    Iterator getIterator(size_t vertex) const
    {
        return Iterator(this, vertex);
    }

private:
    size_t index(size_t from, size_t to) const
    {
        return from * m_vertexCount + to;
    }

    void init(size_t n)
    {
        m_vertexCount = n;
        m_vertexData.resize(n);

        m_adj.resize(n * n);
        for (size_t i = 0; i < n * n; i++)
        {
            m_adj.set(i, false);
        }

        m_edgeData.resize(n * n);
    }

    size_t m_vertexCount;
    Vector<VertexData> m_vertexData;
    Vector<bool> m_adj;
    Vector<EdgeData> m_edgeData;
};

#endif
