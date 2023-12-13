#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <iostream>
#include <list>
#include <vector>

template <typename Data> class Graph {
public:
    explicit Graph(size_t numVertices);
    void addVertex();
    void addEdge(size_t from, size_t to);
    void removeVertex(size_t vertex);
    void removeEdge(size_t from, size_t to);
    size_t vertexCount();
    bool hasEdge(size_t from, size_t to);
    void setEdgeLabel(size_t from, size_t to, const std::string& label);
    std::string getEdgeLabel(size_t from, size_t to);
    void setVertexLabel(size_t vertex, const std::string& label);
    std::string getVertexLabel(size_t vertex);

    struct NeighborIterator {
        NeighborIterator(const Graph* graph, size_t vertex);
        size_t operator*() const;
        NeighborIterator& operator++();
        bool operator!=(const NeighborIterator& other) const;

    private:
        const Graph* m_graph;
        size_t m_vertex;
        typename std::list<size_t>::const_iterator m_current;
    };

    NeighborIterator begin(size_t vertex) const;
    NeighborIterator end(size_t vertex) const;

private:
    size_t m_numVertices;
    std::vector<std::list<size_t>> m_adjList;
    std::vector<std::vector<std::string>> m_edgeLabels;
    std::vector<std::string> m_vertexLabels;
};
size_t Graph::vertexCount() {
    return m_numVertices;
}

Graph::Graph(size_t numVertices)
    : m_numVertices(numVertices), m_adjList(numVertices),
    m_edgeLabels(numVertices, std::vector<std::string>(numVertices)),
    m_vertexLabels(numVertices) {}

void Graph::addVertex() {
    ++m_numVertices;
    m_adjList.resize(m_numVertices);
    m_edgeLabels.resize(m_numVertices, std::vector<std::string>(m_numVertices));
    m_vertexLabels.resize(m_numVertices);
}

void Graph::addEdge(size_t from, size_t to) {
    m_adjList[from].push_back(to);
}

void Graph::removeVertex(size_t vertex) {
    m_adjList[vertex].clear();
    for (auto& list : m_adjList) {
        list.remove(vertex);
    }
    m_edgeLabels[vertex].clear();
    m_vertexLabels[vertex].clear();
}

void Graph::removeEdge(size_t from, size_t to) {
    m_adjList[from].remove(to);
    m_edgeLabels[from][to].clear();
}

bool Graph::hasEdge(size_t from, size_t to) {
    for (const auto& neighbor : m_adjList[from]) {
        if (neighbor == to) {
            return true;
        }
    }
    return false;
}

void Graph::setEdgeLabel(size_t from, size_t to, const std::string& label) {
    m_edgeLabels[from][to] = label;
}


std::string Graph::getEdgeLabel(size_t from, size_t to) {
    return m_edgeLabels[from][to];
}

void Graph::setVertexLabel(size_t vertex, const std::string& label) {
    m_vertexLabels[vertex] = label;
}

std::string Graph::getVertexLabel(size_t vertex) {
    return m_vertexLabels[vertex];
}

Graph::NeighborIterator::NeighborIterator(const Graph* graph, size_t vertex)
    : m_graph(graph), m_vertex(vertex), m_current(graph->m_adjList[vertex].begin()) {}

size_t Graph::NeighborIterator::operator*() const {
    return *m_current;
}

Graph::NeighborIterator& Graph::NeighborIterator::operator++() {
    ++m_current;
    return *this;
}

bool Graph::NeighborIterator::operator!=(const NeighborIterator& other) const {
    return m_current != other.m_current;
}

Graph::NeighborIterator Graph::begin(size_t vertex) const {
    return NeighborIterator(this, vertex);
}

Graph::NeighborIterator Graph::end(size_t vertex) const {
    return NeighborIterator(this, vertex);
}
#endif
