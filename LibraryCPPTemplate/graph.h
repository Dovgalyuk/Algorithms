#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "vector.h"
#include "Vertex.h"
#include "Edge.h"

template <typename V_type>
class Iterator;

template <typename V_type, typename E_type>
class Graph {
public:
    Graph() {}

    Graph(size_t q) {
        for (size_t i = 0; i < q; i++) {
            add_vertex();
        }
    }

    ~Graph() {}

    void add_vertex() {
        vertex.push({ vertex.size(), V_type() });

        vertex_q++;
        relations.push(Vector<unsigned int>(vertex_q, 0));

        for (size_t i = 0; i < relations.size(); i++) {
            while (relations[i].size() != vertex_q)
                relations[i].push(0);
        }
    }

    void add_vertex(V_type vertex_mark) {
        vertex.push({ vertex.size(), vertex_mark });

        vertex_q++;
        relations.push(Vector<unsigned int>(vertex_q, 0));

        for (size_t i = 0; i < relations.size(); i++) {
            while (relations[i].size() != vertex_q)
                relations[i].push(0);
        }
    }

    void delete_vertex(size_t a) {
        if (a >= vertex_q)
            return;

        relations.erase(a);
        for (size_t i = 0; i < relations.size(); i++) {
            relations[i].erase(a);
        }

        for (size_t i = 0; i < edges.size(); i++) {
            if (edges[i].start == a || edges[i].destination == a) {
                edges.erase(i);
                i--;
            }
        }
    }

    void add_edge(size_t a, size_t b, E_type edge_mark) {
        if (a < vertex_q && b < vertex_q) {
            edges.push(Edge<E_type>(a, b, edge_mark));
        }
    }

    void delete_edge(size_t a, size_t b) {
        if (a < vertex_q && b < vertex_q) {
            edges.erase(edge_index(a, b));
        }
    }

    int edge_index(size_t a, size_t b) {
        if (a < vertex_q && b < vertex_q) {
            for (size_t i = 0; i < edges.size(); i++) {
                if (edges[i].start == a && edges[i].destination == b)
                    return i;
            }
        }
        return -1;
    }

    void set_mark(size_t a, V_type mark) {
        vertex[a].mark = mark;
    }

    Vector<Vector<unsigned int>> get_matrix() {
        return relations;
    }

    Vector<V_type> get_marks() {
        Vector<V_type> marks;
        for (size_t i = 0; i < vertex_q; i++) {
            marks.push(vertex[i].mark);
        }
        return marks;
    }

    Vector<Vertex<V_type>> get_vertex() {
        return vertex;
    }

    Vector<Edge<E_type>> get_edges() {
        return edges;
    }

    Vertex<V_type> get_vertex_by_index(size_t index) {
        return vertex[index];
    }

    class Iterator {
    public:
        Iterator(Graph<V_type, E_type>* graph, size_t index, size_t neib)
            : graph(graph), start_index(start_index), next_index(neib) {}

        Iterator& operator++() {
            Vector<unsigned int> v_neib = graph->get_matrix()[start_index];
            for (size_t i = next_index + 1; i < v_neib.size(); i++) {
                if (v_neib[i]) {
                    next_index = i;
                    return *this;
                }
            }
            next_index = v_neib.size();
            return *this;
        }

        const bool operator!=(const Iterator iterator) {
            return next_index != iterator.next_index;
        }

        const Vertex<V_type> operator*() {
            return graph->get_vertex_by_index(next_index);
        }

    private:
        Graph<V_type, E_type>* graph;
        size_t start_index;
        size_t next_index;
    };

    Iterator begin(size_t index) {
        size_t neib = relations[index].size();
        for (size_t i = 0; i < relations[index].size(); i++) {
            if (relations[index][i] != 0) {
                neib = i;
                break;
            }
        }

        return Iterator(this, index, neib);
    }

    Iterator end(size_t index) {
        return Iterator(this, index, relations[index].size());
    }

private:
    bool mark_exist(V_type mark) {
        for (size_t i = 0; i < vertex.size(); i++) {
            if (vertex[i].mark == mark)
                return true;
        }
        return false;
    }

    size_t vertex_q = 0;
    size_t edge_q = 0;
    Vector<Edge<E_type>> edges;
    Vector<Vertex<V_type>> vertex;
    Vector<Vector<unsigned int>> relations;
};

#endif