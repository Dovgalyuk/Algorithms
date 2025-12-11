#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <cstddef>
#include "vector.h"

template <typename V, typename E>
class Graph
{
public:
    using VertexLabel = V;
    using EdgeLabel = E;

    struct NeighborIterator
    {
        const Graph* g;
        size_t v;
        size_t current;

        NeighborIterator(const Graph* graph, size_t vertex);

        bool HasNext() const;

        size_t Next();
    };
    explicit Graph(size_t vertexCount);


    size_t VertexCount() const;

    size_t AddVertex(const V& label);

    void RemoveVertex(size_t index);

    void SetVertexLabel(size_t index, const V& label);

    const V& GetVertexLabel(size_t index) const;

    Vector<V> GetAllVertexLabels() const;

    void AddEdge(size_t from, size_t to, const E& label);

    void RemoveEdge(size_t from, size_t to);

    bool HasEdge(size_t from, size_t to) const;

    void SetEdgeLabel(size_t from, size_t to, const E& label);

    const E& GetEdgeLabel(size_t from, size_t to) const;

    NeighborIterator Neighbors(size_t vertex) const;

private:

    struct EdgeCell
    {
        bool exists;
        E    label;

        EdgeCell() : exists(false), label() {}
    };

    Vector<V> vertexLabels;

    Vector< Vector<EdgeCell> > matrix;

};

template <typename V, typename E>
Graph<V, E>::NeighborIterator::NeighborIterator(const Graph* graph, size_t vertex)
    : g(graph), v(vertex), current(0)
{
    while (current < g->VertexCount() && !g->HasEdge(v, current))
        ++current;
}

template <typename V, typename E>
bool Graph<V, E>::NeighborIterator::HasNext() const
{
    return current < g->VertexCount();
}

template <typename V, typename E>
size_t Graph<V, E>::NeighborIterator::Next()
{
    size_t result = current;

    ++current;
    while (current < g->VertexCount() && !g->HasEdge(v, current))
        ++current;
    return result;
}

template <typename V, typename E>
Graph<V, E>::Graph(size_t vertexCount)
{
    vertexLabels.resize(vertexCount);
    matrix.resize(vertexCount);
    for (size_t i = 0; i < vertexCount; ++i)
    {
        matrix[i].resize(vertexCount);
    }
}


template <typename V, typename E>
size_t Graph<V, E>::VertexCount() const
{
    return vertexLabels.size();
}

template <typename V, typename E>
size_t Graph<V, E>::AddVertex(const V& label)
{
    size_t oldN = VertexCount();
    size_t newN = oldN + 1;

    vertexLabels.resize(newN);
    vertexLabels[oldN] = label;

    matrix.resize(newN);

    for (size_t i = 0; i < oldN; ++i)
        matrix[i].resize(newN);

    matrix[oldN].resize(newN);

    return oldN;

}

template <typename V, typename E>
void Graph<V, E>::RemoveVertex(size_t index)
{
    size_t n = VertexCount();
    if (index >= n) return;

    for (size_t i = index; i + 1 < n; ++i)
        vertexLabels[i] = vertexLabels[i + 1];
    vertexLabels.resize(n - 1);

    for (size_t i = index; i + 1 < n; ++i)
        matrix[i] = matrix[i + 1];
    matrix.resize(n - 1);

    for (size_t i = 0; i < n - 1; ++i)
    {
        Vector<EdgeCell>& row = matrix[i];
        for (size_t j = index; j + 1 < n; ++j)
            row[j] = row[j + 1];
        row.resize(n - 1);
    }
}

template <typename V, typename E>
void Graph<V, E>::SetVertexLabel(size_t index, const V& label)
{
    vertexLabels[index] = label;
}

template <typename V, typename E>
const V& Graph<V, E>::GetVertexLabel(size_t index) const
{
    return vertexLabels[index];
}

template <typename V, typename E>
Vector<V> Graph<V, E>::GetAllVertexLabels() const
{
    return vertexLabels;
}

template <typename V, typename E>
void Graph<V, E>::AddEdge(size_t from, size_t to, const E& label)
{
    EdgeCell& cell = matrix[from][to];
    cell.exists = true;
    cell.label = label;
}

template <typename V, typename E>
void Graph<V, E>::RemoveEdge(size_t from, size_t to)
{
    matrix[from][to].exists = false;
}

template <typename V, typename E>
bool Graph<V, E>::HasEdge(size_t from, size_t to) const
{
    return matrix[from][to].exists;
}

template <typename V, typename E>
void Graph<V, E>::SetEdgeLabel(size_t from, size_t to, const E& label)
{
    EdgeCell& cell = matrix[from][to];
    cell.exists = true;
    cell.label = label;
}

template <typename V, typename E>
const E& Graph<V, E>::GetEdgeLabel(size_t from, size_t to) const
{
    return matrix[from][to].label;
}

template <typename V, typename E>
typename Graph<V, E>::NeighborIterator Graph<V, E>::Neighbors(size_t vertex) const
{
    return NeighborIterator(this, vertex);
}

#endif
