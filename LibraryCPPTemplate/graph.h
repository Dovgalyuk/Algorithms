#ifndef GRAPH_H
#define GRAPH_H

#include "Vector.h"
#include <iostream>

class Edge {
public:
    size_t from, to;
    double weight;

    Edge(size_t f = 0, size_t t = 0, double w = 0.0) : from(f), to(t), weight(w) {}
};

class DSU {
private:
    Vector<size_t> parent;
    Vector<size_t> rank;

public:
    DSU(size_t n) {
        for (size_t i = 0; i < n; ++i) {
            parent.push_back(i);
            rank.push_back(0);
        }
    }

    size_t find(size_t a) {
        if (parent.get(a) != a) {
            parent.set(a, find(parent.get(a)));
        }
        return parent.get(a);
    }

    void union_sets(size_t a, size_t b) {
        size_t rootA = find(a);
        size_t rootB = find(b);
        if (rootA != rootB) {
            if (rank.get(rootA) < rank.get(rootB)) {
                parent.set(rootA, rootB);
            } else if (rank.get(rootA) > rank.get(rootB)) {
                parent.set(rootB, rootA);
            } else {
                parent.set(rootB, rootA);
                rank.set(rootA, rank.get(rootA) + 1);
            }
        }
    }
};

class Graph {
private:
    size_t vertices_count;
    Vector<Vector<Edge>> adjacencyMatrix;
    Vector<Edge> edges;

public:
    Graph(size_t vertices_count) : vertices_count(vertices_count) {
        adjacencyMatrix = Vector<Vector<Edge>>(vertices_count);
        for (size_t i = 0; i < vertices_count; ++i) {
            adjacencyMatrix.get(i) = Vector<Edge>();
        }
    }

    void add_edge(size_t from, size_t to, double weight) {
        adjacencyMatrix.get(from).push_back(Edge(from, to, weight));
        adjacencyMatrix.get(to).push_back(Edge(to, from, weight));
        edges.push_back(Edge(from, to, weight));
    }

    class Iterator {
    private:
        Graph& graph;
        size_t currentVertex;
        size_t currentNeighbor;

    public:
        Iterator(Graph& g, size_t vertex) : graph(g), currentVertex(vertex), currentNeighbor(0) {}

        bool has_next() {
            return currentNeighbor < graph.adjacencyMatrix.get(currentVertex).size();
        }

        size_t next() {
            size_t result = currentNeighbor++;
            return graph.adjacencyMatrix.get(currentVertex).get(result).to;
        }
    };

    Iterator iterator(size_t vertex) {
        return Iterator(*this, vertex);
    }

    Vector<Edge>& get_edges() {
        return edges;
    }

    size_t get_vertices_count() const {
        return vertices_count;
    }

    void remove_Vertex(size_t index) {
        for (size_t i = 0; i < vertices_count; ++i) {
            if (i != index) {
                adjacencyMatrix.get(i).erase(index);
            }
        }
        adjacencyMatrix.erase(index);
    }

    void resize_Adjacency_Matrix() {
        adjacencyMatrix.resize(vertices_count - 1);
    }

    void print_graph() {
        for (size_t i = 0; i < vertices_count; ++i) {
            std::cout << "Vertex " << i << ": ";
            for (size_t j = 0; j < adjacencyMatrix.get(i).size(); ++j) {
                std::cout << adjacencyMatrix.get(i).get(j).to << " ";
            }
            std::cout << std::endl;
        }
    }
};

#endif
