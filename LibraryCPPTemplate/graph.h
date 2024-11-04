#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include <unordered_map>
#include <vector>
#include <stdexcept>

template <typename V, typename E>
class Graph {
public:
    struct Edge {
        int to;      
        E mark;

        Edge(int edgeTo, E edgeMark) : to(edgeTo), mark(edgeMark) {}
    };

    Graph(int vertices) : vertex_count(vertices){
        adjacency_list.resize(vertices);
        vertices_marks.resize(vertices);
        for (int i = 0; i < vertices; ++i) {
            adjacency_list[i] = List<Edge>();
        }
    }

    void add_edge(int from, int to, E mark) {
        if (from >= vertex_count || from < 0) {
            throw std::invalid_argument("[add_edge] Graph does not have specified vertex.");
        }
        if(!has_edge(from, to)) {
            adjacency_list[from].insert(Edge(to, mark));
        } else {
            throw std::invalid_argument("[add_edge] Graph already have this edge.");
        }
        
    }

    void remove_edge(int from, int to) {
        if (from >= vertex_count || from < 0
            || to >= vertex_count || to < 0) {
            throw std::invalid_argument("[remove_edge] Graph does not have specified vertex.");
        }

        auto& edges = adjacency_list[from];
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
        adjacency_list.push_back(List<Edge>());
        vertices_marks.push_back(0);
        vertex_count++;
    }

    void remove_vertex(int vertex) {
        if (vertex >= vertex_count || vertex < 0) {
            throw std::invalid_argument("[remove_vertex] Graph does not have specified vertex.");
        }

        adjacency_list.erase(adjacency_list.begin() + vertex);
        vertices_marks.erase(vertices_marks.begin() + vertex);
        for (auto& adj_list : adjacency_list) {
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
        //vertex_count--;

    }

    bool has_edge(int from, int to) {
        if (from >= vertex_count || from < 0
            || to >= vertex_count || to < 0) {
            return false;
        }

        auto& edges = adjacency_list[from];
        auto* current = edges.first();
        while (current) {
            if (current->data().to == to) {
                return true;
            }
            current = current->next();
        }
        return false;
    }

    E get_edge_mark(int from, int to) {
        if (from >= vertex_count || from < 0
            || to >= vertex_count || to < 0) {
            throw std::invalid_argument("[get_edge_mark] Graph does not have specified vertex.");
        }

        auto& edges = adjacency_list[from];
        auto* current = edges.first();
        while (current) {
            if (current->data().to == to) {
                return current->data().mark;
            }
            current = current->next();
        }
        throw std::invalid_argument("[get_edge_mark] Edge does not exist.");
    }

    void set_edge_mark(int from, int to, E mark) {
        if (from >= vertex_count || from < 0
            || to >= vertex_count || to < 0) {
            throw std::invalid_argument("[set_edge_mark] Graph does not have specified vertex.");
        }

        auto& edges = adjacency_list[from];
        auto* current = edges.first();
        typename List<Edge>::Item* prev = nullptr;

        while (current) {
            if (current->data().to == to) {
                if (prev) {
                    edges.erase_next(prev);
                    edges.insert_after(prev, Edge(to, mark));
                } else {
                    edges.erase_first();
                    edges.insert(Edge(to, mark));
                }
                return;
            }
            prev = current;
            current = current->next();
        }
    }

    V get_vertex_mark(int vertex) {
        if (vertex >= vertex_count || vertex < 0) {
            throw std::invalid_argument("[get_vertex_mark] Graph does not have specified vertex.");
        }
        
        return vertices_marks[vertex];
    }

    void set_vertex_mark(int vertex, V new_mark) {
        if (vertex >= vertex_count || vertex < 0) {
            throw std::invalid_argument("[set_vertex_mark] Graph does not have specified vertex.");
        }

        vertices_marks[vertex] = new_mark;
    }

    std::vector<V> get_all_vertex_marks() const {
        return vertices_marks;
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

    Iterator begin(int vertex) {
        if (vertex >= vertex_count || vertex < 0) {
            throw std::invalid_argument("[begin] Graph does not have specified vertex.");
        }
        return Iterator(adjacency_list[vertex].first());
    }

    Iterator end(int vertex) {
        return Iterator(nullptr);
    }

private:
    int vertex_count;
    std::vector<List<Edge>> adjacency_list;
    std::vector<V> vertices_marks;
};

#endif
