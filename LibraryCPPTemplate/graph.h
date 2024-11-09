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

    Vertex<V_type> add_vertex() {
        vertices.push({ vertices.size(), V_type() });

        vertices_q++;
        relations.push(Vector<unsigned int>(vertices_q, 0));

        for (size_t i = 0; i < relations.size(); i++) {
            while (relations[i].size() != vertices_q)
                relations[i].push(0);
        }

        return vertices[vertices.size() - 1];
    }

    Vertex<V_type> add_vertex(V_type vertex_mark) {
        vertices.push({ vertices.size(), vertex_mark });

        vertices_q++;
        relations.push(Vector<unsigned int>(vertices_q, 0));

        for (size_t i = 0; i < relations.size(); i++) {
            while (relations[i].size() != vertices_q)
                relations[i].push(0);
        }

        return vertices[vertices.size() - 1];
    }

    Vertex<V_type> delete_vertex(size_t a) {
        if (a >= vertices_q)
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

        return vertices.erase(a);
    }

    Edge<E_type> add_edge(size_t a, size_t b, E_type edge_mark) {
        if (a >= vertices_q && b >= vertices_q)
            return Edge<E_type>();

        edges.push(Edge<E_type>(a, b, edge_mark));
        relations[a][b]++;
        return edges[edges.size() - 1];
    }

    Edge<E_type> delete_edge(size_t a, size_t b) {
        if ((a >= vertices_q && b >= vertices_q) || relations[a][b] <= 0)
            return Edge<E_type>();

        relations[a][b]--;
        return edges.erase(edge_index(a, b));
    }

    int edge_index(size_t a, size_t b) {
        if (a >= vertices_q && b >= vertices_q)
            return -1;

        for (size_t i = 0; i < edges.size(); i++) {
            if (edges[i].start == a && edges[i].destination == b)
                return i;
        }
    }

    Vertex<V_type> set_mark(size_t a, V_type mark) {
        if (a < vertices_q)
            vertices[a].mark = mark;
        return vertices[a];
    }


    Vertex<V_type> get_vertex_by_index(size_t index) {
        return vertices[index];
    }

    Vector<V_type> get_vertices_marks() {
        Vector<V_type> marks;
        for (size_t i = 0; i < vertices_q; i++) {
            marks.push(vertices[i].mark);
        }
        return marks;
    }

    Vector<Vector<unsigned int>> get_matrix();
    Vector<Vertex<V_type>> get_vertices();
    Vector<Edge<E_type>> get_edges();
    class Iterator;
    Iterator begin(size_t index);
    Iterator end(size_t index);

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
    size_t vertices_q = 0;
    size_t edge_q = 0;
    Vector<Edge<E_type>> edges;
    Vector<Vertex<V_type>> vertices;
    Vector<Vector<unsigned int>> relations;
};

template <typename V_type, typename E_type>
Vector<Vector<unsigned int>> Graph<V_type, E_type>::get_matrix() {
    return relations;
}

template <typename V_type, typename E_type>
Vector<Vertex<V_type>> Graph<V_type, E_type>::get_vertices() {
    return vertices;
}

template <typename V_type, typename E_type>
Vector<Edge<E_type>> Graph<V_type, E_type>::get_edges() {
    return edges;
}

template <typename V_type, typename E_type>
class Graph<V_type, E_type>::Iterator {
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

template <typename V_type, typename E_type>
typename Graph<V_type, E_type>::Iterator Graph<V_type, E_type>::begin(size_t index) {
    size_t neib = relations[index].size();
    for (size_t i = 0; i < relations[index].size(); i++) {
        if (relations[index][i] != 0) {
            neib = i;
            break;
        }
    }

    return Iterator(this, index, neib);
}

template <typename V_type, typename E_type>
typename Graph<V_type, E_type>::Iterator Graph<V_type, E_type>::end(size_t index) {
    return Iterator(this, index, relations[index].size());
}

template <typename V_type, typename E_type>
std::ostream& operator<<(std::ostream& out, Graph<V_type, E_type> graph) {
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

#endif