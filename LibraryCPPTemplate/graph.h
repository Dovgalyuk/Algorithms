#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "vector.h"
#include "Vertex.h"
#include "Edge.h"
#include "GRAPH_EXIT_CODE.h"

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

    Vertex<V_type> add_vertex() {
        vertex.push({ vertex.size(), V_type() });

        vertex_q++;
        relations.push(Vector<unsigned int>(vertex_q, 0));

        for (size_t i = 0; i < relations.size(); i++) {
            while (relations[i].size() != vertex_q)
                relations[i].push(0);
        }

        return vertex[vertex.size() - 1];
    }

    Vertex<V_type> add_vertex(V_type vertex_mark) {
        vertex.push({ vertex.size(), vertex_mark });

        vertex_q++;
        relations.push(Vector<unsigned int>(vertex_q, 0));

        for (size_t i = 0; i < relations.size(); i++) {
            while (relations[i].size() != vertex_q)
                relations[i].push(0);
        }

        return vertex[vertex.size() - 1];
    }

    Vertex<V_type> delete_vertex(size_t a) {
        if (a >= vertex_q)
            Vertex<V_type>();

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

    Edge<E_type> add_edge(size_t a, size_t b, E_type edge_mark) {
        if (a < vertex_q && b < vertex_q) {
            edges.push(Edge<E_type>(a, b, edge_mark));
            relations[a][b]++;
            return Edge<E_type>(a, b, edge_mark);
        }
        return Edge<E_type>();
    }

    Edge<E_type> delete_edge(size_t a, size_t b) {
        if (a < vertex_q && b < vertex_q) {
            Edge<E_type> temp = edges[edge_index(a, b)];
            edges.erase(edge_index(a, b));
            return temp;
        }
        return Edge<E_type>();
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

    Vertex<V_type> set_mark(size_t a, V_type mark) {
        if (a < vertex_q) {
            vertex[a].mark = mark;
        }
        return vertex[a];
    }

    Vector<Vector<unsigned int>> get_matrix() {
        return relations;
    }

    Vector<V_type> get_vertices_marks() {
        Vector<V_type> marks;
        for (size_t i = 0; i < vertex_q; i++) {
            marks.push(vertex[i].mark);
        }
        return marks;
    }

    Vector<Vertex<V_type>> get_vertices() {
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
        size_t start_index = 0;
        size_t next_index = 0;
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

    friend std::ostream& operator<<(std::ostream& out, Graph<V_type, E_type> graph) {
        Vector<Vertex<V_type>> vertex = graph.get_vertices();
        Vector<Edge<E_type>> edges = graph.get_edges();
        Vector<Vector<unsigned int>> relations = graph.get_matrix();

        for (size_t i = 0; i < vertex.size(); i++) {
            out << "Index: " << vertex[i].number << ", mark: " << vertex[i].mark << std::endl;
            int count = 0;
            for (size_t k = 0; k < relations[i].size(); k++)
                relations[i][k] != 0 ? count += relations[i][k] : count;
            out << "\tRelations: " << count << "\n";
            auto it = graph.begin(vertex[i].number);
            if (it != graph.end(vertex[i].number)) {
                out << "\tNeighbours:\n";
                for (; it != graph.end(vertex[i].number); ++it) {
                    out << "\t\tIndex: " << (*it).number << ", mark: " << (*it).mark << std::endl;
                }
            }
            out << std::endl;
        }

        return out;
    }

private:
    size_t vertex_q = 0;
    size_t edge_q = 0;
    Vector<Edge<E_type>> edges;
    Vector<Vertex<V_type>> vertex;
    Vector<Vector<unsigned int>> relations;
};

#endif