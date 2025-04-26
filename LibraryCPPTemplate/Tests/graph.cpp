#include "graph.h"

template <typename V, typename E>
Graph<V, E>::Graph() {}

template <typename V, typename E>
Graph<V, E>::~Graph() {}

template <typename V, typename E>
size_t Graph<V, E>::add_Vertex(const V& mark) {
    size_t index = vertices.size();
    vertices.push(Vertex<V>{mark});
    
    resize_Adjacency_Matrix();
    return index;
}

template <typename V, typename E>
void Graph<V, E>::remove_Vertex(size_t index) {
    if (index >= vertices.size()) throw std::out_of_range("Index out of range");

    for (size_t i = 0; i < vertices.size(); ++i) {
        adjacencyMatrix.get(i).set(index, Edge<E>{});
        adjacencyMatrix.get(index).set(i, Edge<E>{});
    }

    vertices.erase(index);
    resize_Adjacency_Matrix();
}

template <typename V, typename E>
void Graph<V, E>::add_Edge(size_t start, size_t end, const E& mark) {
    if (start >= vertices.size() || end >= vertices.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    adjacencyMatrix.get(start).set(end, Edge<E>{mark});
}

template <typename V, typename E>
void Graph<V, E>::remove_Edge(size_t start, size_t end) {
    if (start >= vertices.size() || end >= vertices.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    adjacencyMatrix.get(start).set(end, Edge<E>{});
}

template <typename V, typename E>
bool Graph<V, E>::is_Edge_Exist(size_t start, size_t end) const {
    return adjacencyMatrix.get(start).get(end).mark != E{};
}

template <typename V, typename E>
const V& Graph<V, E>::get_Vertex_Mark(size_t index) const {
    if (index >= vertices.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    return vertices.get(index).mark;
}

template <typename V, typename E>
void Graph<V, E>::set_Vertex_Mark(size_t index, const V& mark) {
    if (index >= vertices.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    vertices.get(index).mark = mark;
}

template <typename V, typename E>
const E& Graph<V, E>::get_Edge_Mark(size_t start, size_t end) const {
    if (start >= vertices.size() || end >= vertices.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    return adjacencyMatrix.get(start).get(end).mark;
}

template <typename V, typename E>
void Graph<V, E>::set_Edge_Mark(size_t start, size_t end, const E& mark) {
    if (start >= vertices.size() || end >= vertices.size()) {
        throw std::out_of_range("Vertex index out of range");
    }
    adjacencyMatrix.get(start).set(end, Edge<E>{mark});
}

template <typename V, typename E>
std::vector<V> Graph<V, E>::get_All_Vertex_Marks() const {
    std::vector<V> marks;
    for (size_t i = 0; i < vertices.size(); ++i) {
        marks.push_back(vertices.get(i).mark);
    }
    return marks;
}

template <typename V, typename E>
typename Graph<V, E>::Iterator Graph<V, E>::get_Iterator(size_t vertex) const {
    return Iterator(this, vertex);
}

template <typename V, typename E>
Graph<V, E>::Iterator::Iterator(const Graph* graph, size_t vertex)
    : graph(graph), vertex(vertex), currentNeighbor(0) {}

template <typename V, typename E>
bool Graph<V, E>::Iterator::hasNext() const {
    for (size_t i = currentNeighbor; i < graph->vertices.size(); ++i) {
        if (graph->is_Edge_Exist(vertex, i)) {
            return true;
        }
    }
    return false;
}

template <typename V, typename E>
size_t Graph<V, E>::Iterator::next() {
    if (!hasNext()) throw std::out_of_range("No more neighbors");
    return currentNeighbor++;
}

template <typename V, typename E>
void Graph<V, E>::resize_Adjacency_Matrix() {
    for (size_t i = 0; i < vertices.size(); ++i) {
        adjacencyMatrix.get(i).resize(vertices.size());
    }
}