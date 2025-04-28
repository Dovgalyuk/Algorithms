#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"
#include <algorithm>
#include <set>

template <typename E>
struct EdgeInfo {
    size_t vertex1;
    size_t vertex2;
    E weight;

    EdgeInfo() : vertex1(0), vertex2(0), weight(E()) {}  // Default constructor
    EdgeInfo(size_t v1, size_t v2, const E& w) : vertex1(v1), vertex2(v2), weight(w) {}
};

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
        if (parent[a] != a) {
            parent[a] = find(parent[a]);
        }
        return parent[a];
    }

    void union_sets(size_t a, size_t b) {
        size_t rootA = find(a);
        size_t rootB = find(b);
        if (rootA != rootB) {
            if (rank[rootA] < rank[rootB]) {
                parent[rootA] = rootB;
            } else if (rank[rootA] > rank[rootB]) {
                parent[rootB] = rootA;
            } else {
                parent[rootB] = rootA;
                rank[rootA] += 1;
            }
        }
    }
};

template <typename V, typename E>
class Graph {
public:
    Graph(size_t n) : vertices_count(n) {
        adj_list.resize(n);  // Инициализация списка смежности
    }

    // Добавление вершины
    void add_Vertex(const V& vertex) {
        vertices.push_back(vertex);
        adj_list.push_back({});
        ++vertices_count;
    }

    // Добавление ребра
    void add_Edge(size_t vertex1, size_t vertex2, const E& edge) {
        adj_list[vertex1].push_back({vertex1, vertex2, edge});
    }

    // Удаление ребра
    void remove_Edge(size_t vertex1, size_t vertex2) {
        adj_list[vertex1].erase(
            std::remove_if(adj_list[vertex1].begin(), adj_list[vertex1].end(),
                [vertex2](const EdgeInfo<E>& e) { return e.vertex2 == vertex2; }),
            adj_list[vertex1].end());
        adj_list[vertex2].erase(
            std::remove_if(adj_list[vertex2].begin(), adj_list[vertex2].end(),
                [vertex1](const EdgeInfo<E>& e) { return e.vertex2 == vertex1; }),
            adj_list[vertex2].end());
    }

    Vector<EdgeInfo<E>> get_edges() const {
        Vector<EdgeInfo<E>> edges;
        for (size_t i = 0; i < adj_list.size(); ++i) {
            for (const auto& edge : adj_list[i]) {
                if (i < edge.vertex2) { // Избегаем дублирующихся рёбер для неориентированного графа
                    edges.push_back(edge);
                }
            }
        }
        return edges;
    }

    // Удаление вершины
    void remove_Vertex(size_t index) {
        vertices.erase(vertices.begin() + index);
		adj_list.erase(adj_list.begin() + index);
        --vertices_count;
    }

    // Получение количества вершин
    size_t get_VertexAmount() const {
        return vertices_count;
    }

    // Итератор для перебора соседей вершины
    class Iterator {
    public:
        Iterator(Graph& g, size_t v) : graph(g), vertex(v), edge_idx(0) {}

        bool has_next() const {
            return edge_idx < graph.adj_list[vertex].size();
        }

        size_t next() {
            return graph.adj_list[vertex][edge_idx++].vertex2;
        }

    private:
        Graph& graph;
        size_t vertex;
        size_t edge_idx;
    };

    Iterator iterator(size_t v) {
        return Iterator(*this, v);
    }

private:
    size_t vertices_count;
    Vector<V> vertices;  // Using custom vector instead of std::vector
    Vector<Vector<EdgeInfo<E>>> adj_list;  // Using custom vector instead of std::vector
};

#endif
