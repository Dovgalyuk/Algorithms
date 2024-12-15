#ifndef GRAPH_TEMPLATE_H
#define GRAPH_TEMPLATE_H

#include <vector>
#include <stdexcept>
#include "list.h"

template <typename V, typename E>
class Graph {
public:
    struct Vertex;
    struct Edge;

    struct Vertex {
        V mark;
        List<Edge*> edges;
        size_t id_vertex;

        Vertex(V mark, size_t id_vertex) : mark(mark), edges(), id_vertex(id_vertex) {}
    };

    struct Edge {
        E mark;
        Vertex* from;
        Vertex* to;
        size_t id_edge;

        Edge(E mark, Vertex* from, Vertex* to, size_t id_edge) : mark(mark), from(from), to(to), id_edge(id_edge) {}
    };

    explicit Graph(size_t max_vertices) : max_vertex_count(max_vertices), next_edge_id(0) {}

    Graph(const Graph& other) : max_vertex_count(other.max_vertex_count), next_edge_id(0) {
        vertices.reserve(other.vertices.size());

        for (const auto& v : other.vertices) {
            Vertex* new_vertex = new Vertex(v->mark, v->id_vertex);
            vertices.push_back(new_vertex);

            for (const auto& edge : v->edges) {
                Edge* new_edge = new Edge(edge->mark, new_vertex, vertices[edge->to->id_vertex], edge->id_edge);
                new_vertex->edges.insert(new_edge);
            }
        }
    }

    Graph& operator=(const Graph& other) {
        if (this != &other) {
            clear();
            max_vertex_count = other.max_vertex_count;
            next_edge_id = 0;
            vertices.reserve(other.vertices.size());

            for (const auto& v : other.vertices) {
                Vertex* new_vertex = new Vertex(v->mark, v->id_vertex);
                vertices.push_back(new_vertex);

                for (const auto& edge : v->edges) {
                    Edge* new_edge = new Edge(edge->mark, new_vertex, vertices[edge->to->id_vertex], edge->id_edge);
                    new_vertex->edges.insert(new_edge);
                }
            }
        }
        return *this;
    }

    ~Graph() {
        clear();
    }

    void add_vertex(V mark) {
        if (vertices.size() >= max_vertex_count) {
            throw std::overflow_error("Maximum vertex limit reached");
        }

        vertices.push_back(new Vertex(mark, vertices.size()));
    }

    size_t get_vertex_count() const {
        return vertices.size();
    }

    void remove_vertex(size_t ind) {
        if (ind >= vertices.size()) {
            throw std::out_of_range("Incorrect index");
        }

        Vertex* v = vertices[ind];

        for (size_t i = 0; i < vertices.size(); ++i) {
            if (i != ind) {
                remove_edge(vertices[i], v);
            }
        }

        typename List<Edge*>::Item* item = v->edges.first();
        while (item) {
            Edge* edge = item->data();
            delete edge;
            item = item->next();
        }

        delete v;
        vertices.erase(vertices.begin() + ind);
    }

    void set_vertex_mark(size_t ind, V mark) {
        if (ind >= vertices.size()) {
            throw std::out_of_range("Incorrect index");
        }

        vertices[ind]->mark = mark;
    }

    Vertex* get_vertex(size_t ind) {
        if (ind >= vertices.size()) {
            throw std::out_of_range("Incorrect index");
        }

        return vertices[ind];
    }

    V get_vertex_mark(size_t ind) {
        if (ind >= vertices.size()) {
            throw std::out_of_range("Incorrect index");
        }
        return vertices[ind]->mark;
    }

    std::vector<V> get_all_vertex_marks() const {
        std::vector<V> marks;
        for (const auto& vertex : vertices) {
            marks.push_back(vertex->mark);
        }

        return marks;
    }

    size_t add_edge(size_t from_vertex_ind, size_t to_vertex_ind, E mark) {
        if (from_vertex_ind >= vertices.size() || to_vertex_ind >= vertices.size()) {
            throw std::out_of_range("Incorrect index");
        }
        if (has_edge(from_vertex_ind, to_vertex_ind)) {
            throw std::invalid_argument("Edge already exists");
        }

        Edge* new_edge = new Edge(mark, vertices[from_vertex_ind], vertices[to_vertex_ind], next_edge_id++);
        vertices[from_vertex_ind]->edges.insert(new_edge);
        return new_edge->id_edge;
    }

    void remove_edge(Vertex* from, Vertex* to) {
        if (from == nullptr || to == nullptr) {
            throw std::invalid_argument("One of the vertices is null");
        }

        typename List<Edge*>::Item* item = from->edges.first();
        typename List<Edge*>::Item* prev_item = nullptr;

        while (item != nullptr) {
            if (item->data()->to == to) {
                Edge* edge_deleted = item->data();
                if (prev_item) {
                    from->edges.erase_next(prev_item);
                }
                else {
                    from->edges.erase_first();
                }
                delete edge_deleted;
                return;
            }
            prev_item = item;
            item = item->next();
        }
    }


    void set_edge_mark(size_t id, E mark) {
        Edge* e = find_edge(id);
        if (!e) {
            throw std::out_of_range("Incorrect id");
        }
        e->mark = mark;
    }

    E get_edge_mark(size_t id) {
        Edge* e = find_edge(id);
        if (!e) {
            throw std::out_of_range("Incorrect id");
        }
        return e->mark;
    }

    E get_edge_weight(size_t from, size_t to) {
        if (from >= vertices.size() || to >= vertices.size()) {
            throw std::out_of_range("Incorrect index");
        }

        typename List<Edge*>::Item* item = vertices[from]->edges.first();
        while (item) {
            Edge* edge = item->data();
            if (edge->to == vertices[to]) {
                return edge->mark;
            }
            item = item->next();
        }
        throw std::invalid_argument("Edge does not exist");
    }

    bool has_edge(size_t from_index, size_t to_index) {
        if (from_index >= vertices.size() || to_index >= vertices.size()) {
            throw std::out_of_range("Incorrect index");
        }

        typename List<Edge*>::Item* item = vertices[from_index]->edges.first();
        while (item) {
            if (item->data()->to == vertices[to_index]) {
                return true;
            }
            item = item->next();
        }
        return false;
    }

    struct iterator {
        typename List<Edge*>::Item* ptr;

        iterator(typename List<Edge*>::Item* item) : ptr(item) {}

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }

        iterator& operator++() {
            if (ptr) ptr = ptr->next();
            return *this;
        }

        Vertex* operator*() {
            if (!ptr) {
                throw std::runtime_error("Dereferencing a null iterator");
            }
            return ptr->data()->to;
        }
    };


    iterator begin(size_t ver_ind) {
        if (ver_ind >= vertices.size()) {
            throw std::out_of_range("Incorrect index");
        }
        return iterator(vertices[ver_ind]->edges.first());
    }


    iterator end() {
        return iterator(nullptr);
    }

private:
    size_t max_vertex_count;
    size_t next_edge_id;
    std::vector<Vertex*> vertices;

    void clear() {
        for (Vertex* v : vertices) {
            typename List<Edge*>::Item* item = v->edges.first();
            while (item) {
                Edge* edge = item->data();
                delete edge;
                item = item->next();
            }
            delete v;
        }
        vertices.clear();
    }

    Edge* find_edge(size_t id) {
        for (Vertex* v : vertices) {
            typename List<Edge*>::Item* item = v->edges.first();
            while (item) {
                if (item->data()->id_edge == id) {
                    return item->data();
                }
                item = item->next();
            }
        }
        return nullptr;
    }
};

#endif
