#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "graph.h"

template<typename V, typename E>
Graph<V, E>::Graph() = default;

template<typename V, typename E>
Graph<V, E>::~Graph() {
    clearEdges();
}

template<typename V, typename E>
Graph<V, E>& Graph<V, E>::operator=(const Graph<V, E>& other) {
    if (this == &other) {
        return *this;
    }
    clearEdges();
    vertices = other.vertices;
    edgeMatrix.resize(other.edgeMatrix.size());
    for (size_t i = 0; i < other.edgeMatrix.size(); ++i) {
        if (other.edgeMatrix[i] != nullptr) {
            edgeMatrix[i] = new Edge<E>(*other.edgeMatrix[i]);
        }
        else {
            edgeMatrix[i] = nullptr;
        }
    }
    return *this;
}

template<typename V, typename E>
void Graph<V, E>::add_Edge(size_t startIv, size_t endIv, E edge_mark) {
    if (startIv >= get_VertexAmount() || endIv >= get_VertexAmount()) {
        throw std::out_of_range("The index is out of range!");
    }
    Edge<E>*& exists_edge = edgeMatrix[startIv * get_VertexAmount() + endIv];
    if (exists_edge != nullptr) {
        delete exists_edge;
    }
    exists_edge = new Edge<E>(edge_mark);
}

template<typename V, typename E>
void Graph<V, E>::remove_Edge(size_t startIv, size_t endIv) {
    if (startIv >= get_VertexAmount() || endIv >= get_VertexAmount()) {
        throw std::out_of_range("Vertex index out of range.");
    }
    size_t index = startIv * get_VertexAmount() + endIv;
    delete edgeMatrix[index];
    edgeMatrix[index] = nullptr;
}

template<typename V, typename E>
Edge<E>* Graph<V, E>::get_Edge(size_t startIv, size_t endIv) const {
    return edgeMatrix[startIv * get_VertexAmount() + endIv];
}

template<typename V, typename E>
bool Graph<V, E>::isEdgeExist(size_t startIv, size_t endIv) const {
    return get_Edge(startIv, endIv) != nullptr;
}

template<typename V, typename E>
Vertex<V>& Graph<V, E>::get_Vertex(size_t index) {
    if (index >= vertices.size()) {
        throw std::out_of_range("The index is out of range!");
    }
    return vertices[index];
}

template<typename V, typename E>
size_t Graph<V, E>::get_VertexAmount() const {
    return vertices.size();
}

template<typename V, typename E>
size_t Graph<V, E>::add_Vertex(V vertex_mark) {
    size_t index = vertices.size();
    vertices.push(Vertex<V>(index, vertex_mark));
    size_t qty_vertex = get_VertexAmount();
    Vector<Edge<E>*> newEdgeMatrix;
    for (size_t i = 0; i < qty_vertex; ++i) {
        for (size_t j = 0; j < qty_vertex; ++j) {
            newEdgeMatrix.push(nullptr);
        }
    }
    edgeMatrix.swap_data(newEdgeMatrix);
    return index;
}

template<typename V, typename E>
void Graph<V, E>::remove_Vertex(size_t index) {
    size_t qty_vertex = get_VertexAmount();
    if (index >= qty_vertex) {
        return;
    }
    for (size_t i = 0; i < qty_vertex; ++i) {
        Edge<E>* edge = edgeMatrix.get(index * qty_vertex + i);
        if (edge) {
            delete edge;
            edgeMatrix.set(index * qty_vertex + i, nullptr);
        }
    }
    for (size_t i = index; i < qty_vertex - 1; i++) {
        vertices.set(i, vertices.get(i + 1));
    }
    vertices.resize(qty_vertex - 1);
    Vector<Edge<E>*> newEdgeMatrix;
    size_t newQtyVertex = get_VertexAmount();
    newEdgeMatrix.resize(newQtyVertex * newQtyVertex);
    for (size_t i = 0; i < newQtyVertex; i++) {
        for (size_t j = 0; j < newQtyVertex; j++) {
            Edge<E>* edge = edgeMatrix.get(((i + (i >= index)) * qty_vertex) + (j + (j >= index)));
            newEdgeMatrix.set((i * newQtyVertex) + j, edge);
        }
    }
    edgeMatrix.swap_data(newEdgeMatrix);
}

template<typename V, typename E>
std::vector<V> Graph<V, E>::get_AllVertexData() const {
    std::vector<V> allData;
    for (size_t i = 0; i < vertices.size(); i++) {
        allData.push_back(vertices[i].mark);
    }
    return allData;
}

template<typename V, typename E>
typename Graph<V, E>::Iterator Graph<V, E>::get_Iterator(size_t start) const {
    return Iterator(this, start);
}

template<typename V, typename E>
Graph<V, E>::Iterator::Iterator(const Graph* graph, size_t start) : graph(graph), start(start), end(static_cast<size_t>(-1)) {
    end = get_index_Vertex_near();
}

template<typename V, typename E>
size_t Graph<V, E>::Iterator::get_index_Vertex_near() {
    for (size_t i = end + 1; i < graph->get_VertexAmount(); i++) {
        if (graph->isEdgeExist(start, i)) {
            return i;
        }
    }
    return static_cast<size_t>(-1);
}

template<typename V, typename E>
bool Graph<V, E>::Iterator::hasNext() const {
    return end != static_cast<size_t>(-1);
}

template<typename V, typename E>
size_t Graph<V, E>::Iterator::next() {
    if (!hasNext()) {
        throw std::out_of_range("No more adjacent vertices");
    }
    size_t current = end;
    end = get_index_Vertex_near();
    return current;
}

template<typename V, typename E>
size_t Graph<V, E>::Iterator::get_Index() const {
    return end;
}

template<typename V, typename E>
int Graph<V, E>::Iterator::get_Start() const {
    return start;
}

template<typename V, typename E>
void Graph<V, E>::clearEdges() {
    for (size_t i = 0; i < edgeMatrix.size(); i++) {
        delete edgeMatrix.get(i);
        edgeMatrix.set(i, nullptr);
    }
}

#endif
