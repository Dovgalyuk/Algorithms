#include "graph.h"
#include "vector.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Structure for graph edge representation
template <typename V, typename E>
struct Edge_Expanded {
    V u, v; // вершины ребра
    E weight; // вес ребра (стоимость соединения)

    Edge_Expanded() {}
    Edge_Expanded(V u, V v, E weight) : u(u), v(v), weight(weight) {}
};

// Function for comparing edges by weight
template <typename V, typename E>
bool compare_edges(const Edge_Expanded<V, E>& a, const Edge_Expanded<V, E>& b) {
    return a.weight < b.weight;
}

// Function for finding the root of a connectivity component
template <typename V>
V find(V v, Vector<V>& parent, Vector<V>& vertices_labels) {
    size_t pos = vertices_labels.find(v);
    if (parent.get(pos) == v) return v;
    parent.set(pos, find(parent.get(pos), parent, vertices_labels));
    return parent.get(pos);
}

// Function for combining connectivity components
template <typename V>
void union_sets(V u, V v, Vector<V>& parent, Vector<V>& vertices_labels) {
    u = find(u, parent, vertices_labels);
    v = find(v, parent, vertices_labels);
    size_t pos = vertices_labels.find(u);
    parent.set(pos, v);
}

// Kruskal's Algorithm
template <typename V, typename E>
Vector<Edge_Expanded<V, E>> kruskal(Graph<V, E> graph, int n) {
    Vector<Vector<typename Graph<V, E>::Edge>> adjacency_matrix = graph.get_adjacency_matrix();
    Vector<V> vertices_labels = graph.get_vertices_labels();
    size_t vertices_count = vertices_labels.size();

    // Get vector of all edges
    Vector<Edge_Expanded<V, E>> edges;
    for (size_t i = 0; i < vertices_count; i++) {
        for (size_t j = 1; j < vertices_count; j++) {
            if ((graph.graph_type == Graph<V, E>::Graph_Type::Undirected && j < i) || i == j) continue;

            E label = adjacency_matrix.get(i).get(j).label;
                
            if (label != E()) {
                edges.push(Edge_Expanded<V, E>(vertices_labels.get(i), vertices_labels.get(j), label));
            }
        }
    }

    Vector<Edge_Expanded<V, E>> result;
    Vector<V> parent(n);
    for (int i = 0; i < n; i++) parent.set(i, vertices_labels.get(i));

    sort(edges.begin(), edges.end(), compare_edges<V, E>);

    for (const Edge_Expanded<V, E>& e : edges) {
        V u = find<V>(e.u, parent, vertices_labels);
        V v = find<V>(e.v, parent, vertices_labels);
        if (u != v) {
            result.push(e);
            union_sets<V>(u, v, parent, vertices_labels);
        }
    }

    return result;
}