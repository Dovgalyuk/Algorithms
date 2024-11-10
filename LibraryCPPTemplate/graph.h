#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include "vector.h"
#include <unordered_map>
#include <vector>
#include <stdexcept>

template <typename V, typename E>
class Graph {
public:
    struct Edge {
        size_t to;      
        E mark;

        Edge(int edgeTo, E edgeMark) : to(edgeTo), mark(edgeMark) {}
    };

    Graph(size_t vertices) : vertex_count(vertices){
        adjacency_list.resize(vertices);
        vertices_marks.resize(vertices);
        for (size_t i = 0; i < vertices; ++i) {
            adjacency_list.set(i, List<Edge>());
        }
    }

    void add_edge(size_t from, size_t to, E mark) {
        if (from >= vertex_count) {
            throw std::invalid_argument("[add_edge] Graph does not have specified vertex.");
        }
        if(!has_edge(from, to)) {
            adjacency_list.get(from).insert(Edge(to, mark));
        } else {
            throw std::invalid_argument("[add_edge] Graph already have this edge.");
        }
        
    }

    void remove_edge(size_t from, size_t to) {
        if (from >= vertex_count
            || to >= vertex_count) {
            throw std::invalid_argument("[remove_edge] Graph does not have specified vertex.");
        }

        auto& edges = adjacency_list.get(from);
        auto* current = edges.first();
        typename List<Edge>::Item* prev = nullptr;

        while (current) {
            if (current->data().to == to) {
                if (prev) {
                    edges.erase_next(prev);
                } else {
                    edges.erase_first();
                }
                return;
            }
            prev = current;
            current = current->next();
        }
    }

    void add_vertex() {
        adjacency_list.resize(vertex_count+1);
        vertices_marks.resize(vertex_count+1);
        adjacency_list.set(vertex_count, List<Edge>());
        vertices_marks.set(vertex_count, 0);
        vertex_count++;
    }

    void remove_vertex(size_t vertex) {
        if (vertex >= vertex_count) {
            throw std::invalid_argument("[remove_vertex] Graph does not have specified vertex.");
        }

        for(size_t i = vertex; i < vertex_count - 1; i++) {
            adjacency_list.set(i, adjacency_list.get(i+1));
            vertices_marks.set(i, vertices_marks.get(i+1));
        }
        vertex_count--;
        adjacency_list.resize(vertex_count);
        vertices_marks.resize(vertex_count);

        for (size_t i = 0; i < vertex_count; i++) {
            auto& adj_list = adjacency_list.get(i);
            auto* current = adj_list.first();
            typename List<Edge>::Item* prev = nullptr;
            while (current) {
                if (current->data().to == vertex) {
                    if(prev) 
                        adj_list.erase_next(prev);
                    else 
                        adj_list.erase_first();
                } else {
                    prev = current;
                    current = current->next();
                } 
            }
        }

    }

    bool has_edge(size_t from, size_t to) {
        if (from >= vertex_count
            || to >= vertex_count) {
            return false;
        }

        auto& edges = adjacency_list.get(from);
        auto* current = edges.first();
        while (current) {
            if (current->data().to == to) {
                return true;
            }
            current = current->next();
        }
        return false;
    }

    E get_edge_mark(size_t from, size_t to) {
        if (from >= vertex_count
            || to >= vertex_count) {
            throw std::invalid_argument("[get_edge_mark] Graph does not have specified vertex.");
        }

        auto& edges = adjacency_list.get(from);
        auto* current = edges.first();
        while (current) {
            if (current->data().to == to) {
                return current->data().mark;
            }
            current = current->next();
        }
        throw std::invalid_argument("[get_edge_mark] Edge does not exist.");
    }

    void set_edge_mark(size_t from, size_t to, E mark) {
        if (from >= vertex_count
            || to >= vertex_count) {
            throw std::invalid_argument("[set_edge_mark] Graph does not have specified vertex.");
        }

        auto& edges = adjacency_list.get(from);
        auto* current = edges.first();

        while (current) {
            if (current->data().to == to) {
                current->data() = Edge(to, mark);
                return;
            }
            current = current->next();
        }
    }

    V get_vertex_mark(size_t vertex) {
        if (vertex >= vertex_count) {
            throw std::invalid_argument("[get_vertex_mark] Graph does not have specified vertex.");
        }
        
        return vertices_marks.get(vertex);
    }

    void set_vertex_mark(size_t vertex, V new_mark) {
        if (vertex >= vertex_count) {
            throw std::invalid_argument("[set_vertex_mark] Graph does not have specified vertex.");
        }

        vertices_marks.set(vertex, new_mark);
    }

    Vector<V> get_all_vertex_marks() const {
        return vertices_marks;
    }

    size_t get_size() {
        return vertex_count;
    }

    class Iterator {
    public:
        Iterator(typename List<Edge>::Item* start) : currentItem_(start) {}

        bool operator==(const Iterator& other) const { return currentItem_ == other.currentItem_; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }

        Iterator& operator++() {
            if (currentItem_) {
                currentItem_ = currentItem_->next();
            }
            return *this;
        }

        Edge operator*() const {
            return currentItem_->data();
        }

    private:
        typename List<Edge>::Item* currentItem_;
    };

    Iterator begin(size_t vertex) {
        if (vertex >= vertex_count) {
            throw std::invalid_argument("[begin] Graph does not have specified vertex.");
        }
        return Iterator(adjacency_list.get(vertex).first());
    }

    Iterator end(size_t vertex) {
        return Iterator(nullptr);
    }

private:
    size_t vertex_count;
    Vector<List<Edge>> adjacency_list;
    Vector<V> vertices_marks;
};

#endif
