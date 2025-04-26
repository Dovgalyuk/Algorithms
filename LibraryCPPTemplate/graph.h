#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"
#include <vector>

template <typename V, typename E>
class Graph {
private:
    struct Vertex {
        V mark;
    };

    struct Edge {
        E mark;
    };

    Vector<Vertex> vertices;
    Vector<Vector<Edge>> adjacencyMatrix;

public:
    Graph();
    ~Graph();
    
    size_t add_Vertex(const V& mark);
    void remove_Vertex(size_t index);
    void add_Edge(size_t start, size_t end, const E& mark);
    void remove_Edge(size_t start, size_t end);
    bool is_Edge_Exist(size_t start, size_t end) const;
    const V& get_Vertex_Mark(size_t index) const;
    void set_Vertex_Mark(size_t index, const V& mark);
    const E& get_Edge_Mark(size_t start, size_t end) const;
    void set_Edge_Mark(size_t start, size_t end, const E& mark);
    std::vector<V> get_All_Vertex_Marks() const;

    class Iterator {
    public:
        Iterator(const Graph* graph, size_t vertex);
        bool hasNext() const;
        size_t next();
        
    private:
        const Graph* graph;
        size_t vertex;
        size_t currentNeighbor;
    };

    Iterator get_Iterator(size_t vertex) const;

private:
    void resize_Adjacency_Matrix();
};

#endif