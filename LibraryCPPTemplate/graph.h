#ifndef GRAPH_H
#define GRAPH_H

#include "vector.h"
#include "list.h"
#include <stdexcept>

using namespace std;

template <typename V, typename E> class Graph {
public:
    enum class Graph_Type {
		Directed,
		Undirected
	};

    struct Edge {
        E label;

        Edge() : label(E()) {}
        Edge(E edge_label) : label(edge_label) {}
    };

    // Constructor initializing a graph with a given number of vertices
    Graph(Graph_Type graph_type, size_t vertices_count) : graph_type(graph_type), vertices_count(vertices_count) {
        adjacency_matrix.resize(vertices_count);
        vertices_labels.resize(vertices_count);

        for (size_t i = 0; i < vertices_count; i++) {
            adjacency_matrix.set(i, Vector<Edge*>(vertices_count, nullptr));
        }
    }

    ~Graph() {
        clear_edges();
    }

    // Add a vertex
    void add_vertex(V label = V()) {
        vertices_count++;
        adjacency_matrix.resize(vertices_count);
        vertices_labels.resize(vertices_count);

        for (size_t i = 0; i < vertices_count - 1; i++) {
            adjacency_matrix.get(i).resize(vertices_count);
            adjacency_matrix.get(i).set(vertices_count - 1, nullptr);
        }

        adjacency_matrix.set(vertices_count - 1, Vector<Edge*>(vertices_count, nullptr));
        set_vertex_label(vertices_count - 1, label);
    }

    // Add an edge between the given vertices
    void add_edge(V from_label, V to_label, E label) {
        size_t from = get_vertex_index(from_label);
        size_t to = get_vertex_index(to_label);

        if (has_edge(from_label, to_label))
            throw invalid_argument("[add_edge] Graph already have this edge.");

        Edge* edge = new Edge(label);

        adjacency_matrix.get(from).set(to, edge);

        if (graph_type == Graph_Type::Undirected) {
            adjacency_matrix.get(to).set(from, edge);
        }
    }

    // Remove vertex
    void remove_vertex(V vertex_label) {
        size_t vertex = get_vertex_index(vertex_label);
    
        size_t new_size = vertices_count - 1;
        Vector<Vector<Edge*>> new_adjacency_matrix(new_size, Vector<Edge*>(new_size, nullptr));
        Vector<V> new_vertices_labels(new_size);

        for (size_t i = 0; i < vertices_count; i++) {
            if (i == vertex) continue; // Skip the vertex to be removed
            
            size_t new_row_index = i < vertex ? i : i - 1;
            for (size_t j = 0; j < vertices_count; j++) {
                if (j == vertex) continue; // Skip the vertex to be removed

                size_t new_col_index = j < vertex ? j : j - 1;
                Edge* edge = adjacency_matrix.get(i).get(j);

                if (edge != nullptr) {
                    new_adjacency_matrix.get(new_row_index).set(new_col_index, edge);
                }
            }
            new_vertices_labels.set(new_row_index, vertices_labels.get(i));
        }

        adjacency_matrix = new_adjacency_matrix;
        vertices_labels = new_vertices_labels;

        vertices_count--;
    }

    // Remove an edge between the given vertices
    void remove_edge(V from_label, V to_label) {
        size_t from = get_vertex_index(from_label);
        size_t to = get_vertex_index(to_label);

        if (!has_edge(from_label, to_label))
            throw invalid_argument("[remove_edge] Graph does not have this edge.");

        Edge* edge = adjacency_matrix.get(from).get(to);

        delete edge;
        adjacency_matrix.get(from).set(to, nullptr);

        if (graph_type == Graph_Type::Undirected) {
            adjacency_matrix.get(to).set(from, nullptr);
        }   
    }

    // Check if there exists an edge between the vertices
    bool has_edge(V from_label, V to_label) const {
        size_t from = get_vertex_index(from_label);
        size_t to = get_vertex_index(to_label);
        
        return adjacency_matrix.get(from).get(to) != nullptr;
    }

    // Set a label for the edge
    void set_edge_label(V from_label, V to_label, E label) {
        size_t from = get_vertex_index(from_label);
        size_t to = get_vertex_index(to_label);
        
        if (!has_edge(from_label, to_label))
            throw invalid_argument("[set_edge_label] Graph does not have this edge.");

        adjacency_matrix.get(from).get(to)->label = label;
    }

    // Get an edge label
    E& get_edge_label(V from_label, V to_label) const {
        size_t from = get_vertex_index(from_label);
        size_t to = get_vertex_index(to_label);

        if(!has_edge(from_label, to_label))
            throw invalid_argument("[get_edge_label] Graph does not have this edge.");

        return adjacency_matrix.get(from).get(to)->label;
    }

    // Set a label for the vertex by ordinal number
    void set_vertex_label(size_t vertex, V label) {
        if (vertex >= vertices_count) {
            throw invalid_argument("[set_vertex_label] Graph does not have a specified vertex.");
        }

        vertices_labels.set(vertex, label);
    }

    // Get vertex label by ordinal number
    V& get_vertex_label(size_t vertex) const {
        if (vertex >= vertices_count) {
            throw invalid_argument("[get_vertex_label] Graph does not have a specified vertex.");
        }

        return vertices_labels.get(vertex);
    }

    // Get index of a vertex
    size_t get_vertex_index(V label) const {
        int res = vertices_labels.find(label);

        if  (res != -1)
            return size_t(res);
        else
            throw invalid_argument("[get_vertex_index] Graph does not have a specified vertex.");
    }

    // Get labels of all vertices as a vector
    Vector<V>& get_vertices_labels() {
        return vertices_labels;
    }

    // Iterator for enumerating neighbors of a given vertex
    class Neighbor_Iterator {
    public:
        Neighbor_Iterator(const Graph& graph, size_t vertex, size_t index)
            : graph(graph), vertex(vertex), index(index) {
            // skip all vertices that are not neighbors
            skip_non_neighbors();
        }

        V operator*() const {
            return graph.get_vertex_label(index);
        }

        Neighbor_Iterator& operator++() {
            index++;
            skip_non_neighbors(); // Skipping non-neighbors after incrementing
            return *this;
        }

        bool operator!=(const Neighbor_Iterator& other) const {
            return index != other.index;
        }

    private:
        const Graph& graph;
        size_t vertex;
        size_t index;

        void skip_non_neighbors() {
            // skip all indexes until a neighbor is encountered
            while (index < graph.vertices_count && !graph.adjacency_matrix.get(vertex).get(index)) {
                index++;
            }
        }
    };

    Neighbor_Iterator neighbors_begin(V vertex_label) const {
        size_t vertex = get_vertex_index(vertex_label);
        return Neighbor_Iterator(*this, vertex, 0);
    }

    Neighbor_Iterator neighbors_end(V vertex_label) const {
        size_t vertex = get_vertex_index(vertex_label);
        return Neighbor_Iterator(*this, vertex, vertices_count);
    }

    Graph_Type graph_type;
private:
    void clear_edges() {
        for (size_t i = 0; i < vertices_count; i++) {
            for (size_t j = 0; j < vertices_count; j++) {
                if (has_edge(vertices_labels.get(i), vertices_labels.get(j))) {
                    if (graph_type == Graph_Type::Undirected && i >= j) continue;

                    Edge* edge = adjacency_matrix.get(i).get(j);

                    delete edge;
                    adjacency_matrix.get(i).set(j, nullptr);
                }
            }
        }
    }

    size_t vertices_count;
    Vector<Vector<Edge*>> adjacency_matrix;
    Vector<V> vertices_labels;
};

#endif