#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include <vector>
#include <utility>
#include "vector.h"

template <typename EdgeLabel, typename VertexLabel>
class Graph
{
public:
    using size_type = std::size_t;

    struct NeighborIterator
    {
        const Graph *graph;
        size_type vertex;
        size_type index;

        NeighborIterator(const Graph *g, size_type v, size_type i);
        size_type operator*() const;
        NeighborIterator &operator++();
        bool operator!=(const NeighborIterator &other) const;
    };

    Graph(size_type vertexCount = 0);

    size_type vertexCount() const;

    size_type addVertex(const VertexLabel &label = VertexLabel());
    void removeVertex(size_type v);

    void addEdge(size_type from, size_type to, const EdgeLabel &label = EdgeLabel());
    void removeEdge(size_type from, size_type to);
    bool hasEdge(size_type from, size_type to) const;

    void setEdgeLabel(size_type from, size_type to, const EdgeLabel &label);
    EdgeLabel getEdgeLabel(size_type from, size_type to) const;

    void setVertexLabel(size_type v, const VertexLabel &label);
    VertexLabel getVertexLabel(size_type v) const;

    std::vector<VertexLabel> getAllVertexLabels() const;

    NeighborIterator neighborsBegin(size_type v) const;
    NeighborIterator neighborsEnd(size_type v) const;

private:
    struct EdgeData
    {
        bool exists;
        EdgeLabel label;
        EdgeData() : exists(false), label() {}
    };

    size_type n_;
    Vector<EdgeData> edges_;
    Vector<VertexLabel> vertexLabels_;

    size_type index(size_type from, size_type to) const
    {
        return from * n_ + to;
    }
};

template <typename E, typename V>
Graph<E, V>::Graph(std::size_t vertexCount)
    : n_(vertexCount)
{
    edges_.resize(n_ * n_);
    vertexLabels_.resize(n_);
}

template <typename E, typename V>
std::size_t Graph<E, V>::vertexCount() const
{
    return n_;
}

template <typename E, typename V>
std::size_t Graph<E, V>::addVertex(const V &label)
{
    std::size_t oldN = n_;
    std::size_t newN = oldN + 1;

    Vector<typename Graph<E, V>::EdgeData> newEdges;
    newEdges.resize(newN * newN);
    for (std::size_t i = 0; i < oldN; ++i)
    {
        for (std::size_t j = 0; j < oldN; ++j)
        {
            newEdges.get(i * newN + j) = edges_.get(i * oldN + j);
        }
    }
    edges_ = std::move(newEdges);

    vertexLabels_.resize(newN);
    vertexLabels_.get(newN - 1) = label;

    n_ = newN;
    return newN - 1;
}

template <typename E, typename V>
void Graph<E, V>::removeVertex(size_type v)
{
    if (v >= n_ || n_ == 0)
    {
        return;
    }

    std::size_t oldN = n_;
    std::size_t newN = oldN - 1;

    if (newN == 0)
    {
        n_ = 0;
        edges_.resize(0);
        vertexLabels_.resize(0);
        return;
    }

    Vector<typename Graph<E, V>::EdgeData> newEdges;
    newEdges.resize(newN * newN);
    for (std::size_t i = 0; i < oldN; ++i)
    {
        if (i == v)
        {
            continue;
        }
        for (std::size_t j = 0; j < oldN; ++j)
        {
            if (j == v)
            {
                continue;
            }
            std::size_t newI = i < v ? i : i - 1;
            std::size_t newJ = j < v ? j : j - 1;
            newEdges.get(newI * newN + newJ) = edges_.get(i * oldN + j);
        }
    }
    edges_ = std::move(newEdges);

    for (std::size_t i = v + 1; i < oldN; ++i)
    {
        vertexLabels_.get(i - 1) = std::move(vertexLabels_.get(i));
    }
    vertexLabels_.resize(newN);

    n_ = newN;
}

template <typename E, typename V>
void Graph<E, V>::addEdge(size_type from, size_type to, const E &label)
{
    if (from >= n_ || to >= n_)
    {
        return;
    }
    typename Graph<E, V>::EdgeData &e = edges_.get(index(from, to));
    e.exists = true;
    e.label = label;
}

template <typename E, typename V>
void Graph<E, V>::removeEdge(size_type from, size_type to)
{
    if (from >= n_ || to >= n_)
    {
        return;
    }
    typename Graph<E, V>::EdgeData &e = edges_.get(index(from, to));
    e.exists = false;
}

template <typename E, typename V>
bool Graph<E, V>::hasEdge(size_type from, size_type to) const
{
    if (from >= n_ || to >= n_)
    {
        return false;
    }
    const typename Graph<E, V>::EdgeData &e = edges_.get(index(from, to));
    return e.exists;
}

template <typename E, typename V>
void Graph<E, V>::setEdgeLabel(size_type from, size_type to, const E &label)
{
    if (from >= n_ || to >= n_)
    {
        return;
    }
    typename Graph<E, V>::EdgeData &e = edges_.get(index(from, to));
    e.label = label;
    e.exists = true;
}

template <typename E, typename V>
E Graph<E, V>::getEdgeLabel(size_type from, size_type to) const
{
    if (from >= n_ || to >= n_)
    {
        return E();
    }
    const typename Graph<E, V>::EdgeData &e = edges_.get(index(from, to));
    return e.label;
}

template <typename E, typename V>
void Graph<E, V>::setVertexLabel(size_type v, const V &label)
{
    if (v >= n_)
    {
        return;
    }
    vertexLabels_.get(v) = label;
}

template <typename E, typename V>
V Graph<E, V>::getVertexLabel(size_type v) const
{
    if (v >= n_)
    {
        return V();
    }
    return vertexLabels_.get(v);
}

template <typename E, typename V>
std::vector<V> Graph<E, V>::getAllVertexLabels() const
{
    std::vector<V> result;
    result.reserve(n_);
    for (std::size_t i = 0; i < n_; ++i)
    {
        result.push_back(vertexLabels_.get(i));
    }
    return result;
}

template <typename E, typename V>
Graph<E, V>::NeighborIterator::NeighborIterator(const Graph *g,
                                                size_type v,
                                                size_type i)
    : graph(g), vertex(v), index(i)
{
}

template <typename E, typename V>
typename Graph<E, V>::size_type Graph<E, V>::NeighborIterator::operator*() const
{
    return index;
}

template <typename E, typename V>
typename Graph<E, V>::NeighborIterator &Graph<E, V>::NeighborIterator::operator++()
{
    if (!graph)
    {
        return *this;
    }
    ++index;
    while (index < graph->n_ && !graph->hasEdge(vertex, index))
    {
        ++index;
    }
    return *this;
}

template <typename E, typename V>
bool Graph<E, V>::NeighborIterator::operator!=(const NeighborIterator &other) const
{
    return graph != other.graph || vertex != other.vertex || index != other.index;
}

template <typename E, typename V>
typename Graph<E, V>::NeighborIterator Graph<E, V>::neighborsBegin(size_type v) const
{
    if (v >= n_)
    {
        return NeighborIterator(this, v, n_);
    }
    size_type i = 0;
    while (i < n_ && !hasEdge(v, i))
    {
        ++i;
    }
    return NeighborIterator(this, v, i);
}

template <typename E, typename V>
typename Graph<E, V>::NeighborIterator Graph<E, V>::neighborsEnd(size_type v) const
{
    return NeighborIterator(this, v, n_);
}

#endif
