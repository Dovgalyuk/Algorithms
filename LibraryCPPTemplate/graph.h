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
        List<Edge*>* edges;
        size_t id_vertex;

        Vertex(V mark, size_t id_vertex) : mark(mark), edges(new List<Edge*>()), id_vertex(id_vertex) {}
        ~Vertex() { delete edges; }
    };

    struct Edge {
        E mark;
        Vertex* from;
        Vertex* to;
        size_t id_edge;

        Edge(E mark, Vertex* from, Vertex* to, size_t id_edge) : mark(mark), from(from), to(to), id_edge(id_edge) {}
    };

    Graph(size_t max_vertices) : max_vertex_count(max_vertices), next_edge_id(0) {}

    Graph(const Graph& other) : max_vertex_count(other.max_vertex_count), next_edge_id(other.next_edge_id) {
        for (const auto& v : other.vertices) {
            Vertex* new_vertex = new Vertex(v->mark, v->id_vertex);
            vertices.push_back(new_vertex);

            for (typename List<Edge*>::Item* item = v->edges->first(); item; item = item->next()) {
                Edge* new_edge = new Edge(item->data()->mark, new_vertex, vertices[item->data()->to->id_vertex], item->data()->id_edge);
                new_vertex->edges->insert(new_edge);
            }
        }
    }

    Graph& operator=(const Graph& other) {
        if (this != &other) {
            for (Vertex* v : vertices) {
                delete v;
            }
            vertices.clear();

            max_vertex_count = other.max_vertex_count;
            next_edge_id = other.next_edge_id;

            for (const auto& v : other.vertices) {
                Vertex* new_vertex = new Vertex(v->mark, v->id_vertex);
                vertices.push_back(new_vertex);
                for (typename List<Edge*>::Item* item = v->edges->first(); item; item = item->next()) {
                    Edge* new_edge = new Edge(item->data()->mark, new_vertex, vertices[item->data()->to->id_vertex], item->data()->id_edge);
                    new_vertex->edges->insert(new_edge);
                }
            }
        }
        return *this;
    }

    ~Graph() {
        for (Vertex* v : vertices) {
            delete v;
        }
    }

    void add_vertex_mark(V mark) {
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
                remove_edge(v, i);
            }
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
        vertices[from_vertex_ind]->edges->insert(new_edge);
        return new_edge->id_edge;
    }

    void delete_edge(size_t id) {
        Edge* e = find_edge(id);
        if (!e) {
            throw std::invalid_argument("The edge was not found");
        }

        remove_edge(e->from, e->id_edge);
        delete e;
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

    bool has_edge(size_t from_index, size_t to_index) {
        if (from_index >= vertices.size() || to_index >= vertices.size()) {
            throw std::out_of_range("Incorrect index");
        }

        typename List<Edge*>::Item* item = vertices[from_index]->edges->first();
        while (item) {
            if (item->data()->to == vertices[to_index]) {
                return true;
            }
            item = item->next();
        }
        return false;
    }

    struct iterator {
        Vertex* ver;
        typename List<Edge*>::Item* ptr;

        iterator(Vertex* ver) : ver(ver) {
            if (ver && ver->edges) {
                ptr = ver->edges->first();
            }
            else {
                ptr = nullptr;
            }
        }

        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        iterator& operator++() {
            if (ptr) ptr = ptr->next();
            return *this;
        }

        Vertex operator*() {
            if (!ptr) {
                throw std::runtime_error("Dereferencing a null iterator");
            }
            return *ptr->data()->to;
        }
    };

    iterator begin(size_t ver_ind) {
        if (ver_ind >= vertices.size()) {
            throw std::out_of_range("Incorrect index");
        }
        return iterator(vertices[ver_ind]);
    }

    iterator end(size_t ver_ind) {
        return iterator(nullptr);
    }

private:
    size_t max_vertex_count;
    size_t next_edge_id;
    std::vector<Vertex*> vertices;

    Edge* find_edge(size_t id) {
        for (Vertex* v : vertices) {
            typename List<Edge*>::Item* item = v->edges->first();
            while (item) {
                if (item->data()->id_edge == id) {
                    return item->data();
                }
                item = item->next();
            }
        }
        return nullptr;
    }

    void remove_edge(Vertex* ver, size_t id) {
        typename List<Edge*>::Item* item = ver->edges->first();
        while (item) {
            if (item->data()->id_edge == id) {
                if (item->prev()) {
                    ver->edges->erase_next(item->prev());
                }
                else {
                    ver->edges->erase_first();
                }
                break;
            }
            item = item->next();
        }
    }
};

#endif
