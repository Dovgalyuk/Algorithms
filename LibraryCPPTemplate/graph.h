#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"
#include <vector>
#include <stdexcept>
#include <limits>

template <typename V>
struct Vertex {
    Vertex() {}
    Vertex(size_t number, V mark) : number(number), mark(mark) {}
    size_t number = std::numeric_limits<size_t>::max();
    V mark = V();
};

template <typename E>
struct Edge {
    Edge() {}
    Edge(E mark) : mark(mark) {}
    E mark = E();
};

template<typename V, typename E>
class Graph {
public:
    Graph();
    ~Graph();
    Graph& operator=(const Graph& other);
    void add_Edge(size_t startIv, size_t endIv, E edge_mark);
    void remove_Edge(size_t startIv, size_t endIv);
    Edge<E>* get_Edge(size_t startIv, size_t endIv) const;
    bool isEdgeExist(size_t startIv, size_t endIv) const;
    Vertex<V>& get_Vertex(size_t index);
    size_t get_VertexAmount() const;
    size_t add_Vertex(V vertex_mark);
    void remove_Vertex(size_t index);
    std::vector<V> get_AllVertexData() const;

    struct Iterator {
    private:
        const Graph* graph;
        size_t start;
        size_t end;

        size_t get_index_Vertex_near();
    public:
        Iterator(const Graph* graph, size_t start);
        bool hasNext() const;
        size_t next();
        size_t get_Index() const;
        int get_Start() const;
    };

    Iterator get_Iterator(size_t start) const;

private:
    void clearEdges();

    Vector<Vertex<V>> vertices;
    Vector<Edge<E>*> edgeMatrix;
};

#include "graph.cpp"

#endif