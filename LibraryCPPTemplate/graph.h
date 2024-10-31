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
        V to;       
        E mark;

        Edge(V edgeTo, E edgeMark) : to(edgeTo), mark(edgeMark) {}
    };

    Graph(int vertices) : vertex_count(vertices) {
        for (int i = 1; i <= vertices; ++i) {
            adjacency_list[i] = List<Edge>();
        }
    }

    void add_edge(V from, V to, E mark) {
        if (adjacency_list.find(from) == adjacency_list.end() || adjacency_list.find(to) == adjacency_list.end()) {
            throw std::invalid_argument("[add_edge] Graph does not have specified vertex.");
        }
        if(!has_edge(from, to)) {
            adjacency_list[from].insert(Edge(to, mark));
        } else {
            throw std::invalid_argument("[add_edge] Graph already have this edge.");
        }
        
    }

    void remove_edge(V from, V to) {
        if (adjacency_list.find(from) == adjacency_list.end()) {
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

    void add_vertex(V vertex) {
        adjacency_list[vertex] = List<Edge>();
    }

    void remove_vertex(V vertex) {
        if (adjacency_list.find(vertex) == adjacency_list.end()) {
            throw std::invalid_argument("[remove_vertex] Graph does not have specified vertex.");
        }

        adjacency_list.erase(vertex);
        for (auto& [v, adj_list] : adjacency_list) {
            auto* current = adj_list.first();
            typename List<Edge>::Item* prev = nullptr;
            while (current) {
                if (current->data().to == vertex) {
                    if(prev) 
                        current = adj_list.erase_next(prev);
                    else 
                        current = adj_list.erase_first();
                } else {
                    prev = current;
                    current = current->next();
                } 
            }
        }

    }

    bool has_edge(V from, V to) {
        if (adjacency_list.find(from) == adjacency_list.end()) {
            return false;
        }

        auto& edges = adjacency_list.at(from);
        auto* current = edges.first();
        while (current) {
            if (current->data().to == to) {
                return true;
            }
            current = current->next();
        }
        return false;
    }

    E get_edge_mark(V from, V to) {
        if (adjacency_list.find(from) == adjacency_list.end()) {
            throw std::invalid_argument("[get_edge_mark] Graph does not have specified vertex.");
        }

        auto& edges = adjacency_list.at(from);
        auto* current = edges.first();
        while (current) {
            if (current->data().to == to) {
                return current->data().mark;
            }
            current = current->next();
        }
        throw std::invalid_argument("[get_edge_mark] Edge does not exist.");
    }

    void set_edge_mark(V from, V to, E mark) {
        if (adjacency_list.find(from) == adjacency_list.end()) {
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
                }
                return;
            }
            prev = current;
            current = current->next();
        }
    }

    V get_vertex_mark(V vertex) {
        if (adjacency_list.find(vertex) == adjacency_list.end()) {
            throw std::invalid_argument("[get_vertex_mark] Graph does not have specified vertex.");
        }
        
        return vertex;
    }

    void set_vertex_mark(V vertex, V new_vertex) {
        if (adjacency_list.find(vertex) == adjacency_list.end()) {
            throw std::invalid_argument("[set_vertex_mark] Graph does not have specified vertex.");
        }

        auto edges = std::move(adjacency_list[vertex]);
        adjacency_list.erase(vertex);
        adjacency_list[new_vertex] = std::move(edges);

        for (auto& [v, adj_list] : adjacency_list) {
            auto* current = adj_list.first();
            typename List<Edge>::Item* prev = nullptr;
            while (current) {
                if (current->data().to == vertex) {
                    V save_mark = current->data().mark;
                    if(prev){
                        current = adj_list.erase_next(prev);
                        adj_list.insert_after(prev, Edge(new_vertex, save_mark));
                    }  else  {
                        current = adj_list.erase_first();
                        adj_list.insert(Edge(new_vertex, save_mark));
                    }     
                } else {
                    prev = current;
                    current = current->next();
                } 
            }
        }
    }

    std::vector<V> get_all_vertex_marks() const {
        std::vector<V> res;
        for (const auto& [vertex, _] : adjacency_list) {
            res.push_back(vertex);
        }
        return res;
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

    Iterator begin(V vertex) {
        if (adjacency_list.find(vertex) == adjacency_list.end()) {
            throw std::invalid_argument("[begin] Graph does not have specified vertex.");
        }
        return Iterator(adjacency_list[vertex].first());
    }

    Iterator end(V vertex) {
        return Iterator(nullptr);
    }

private:
    size_t vertex_count;
    std::unordered_map<V, List<Edge>> adjacency_list;
};

#endif
