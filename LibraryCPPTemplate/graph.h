#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "../LibraryCPPTemplate/vector.h"

template <typename Data>
class Iterator;

template <typename Data>
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
        vertex.push({ vertex.size(), Data() });

        v_quantity++;
        Vector<bool> new_v(v_quantity, 0);
        relations.push(new_v);

        for (size_t i = 0; i < relations.size(); i++) {
            while (relations[i].size() != v_quantity)
                relations[i].push(0);
        }

        if (e_quantity > 0) {
            Vector<int> new_e(e_quantity, 0);
            edges.push(new_e);
            for (size_t i = 0; i < edges.size(); i++) {
                while (edges[i].size() != e_quantity)
                    edges[i].push(0);
            }
        }
    }

    void add_vertex(Data vertex_mark) {
        if (!mark_exist(vertex_mark)) {
            vertex.push({ vertex.size(), vertex_mark });

            v_quantity++;
            Vector<bool> new_v(v_quantity, 0);
            relations.push(new_v);

            for (size_t i = 0; i < relations.size(); i++) {
                while (relations[i].size() != v_quantity)
                    relations[i].push(0);
            }

            if (e_quantity > 0) {
                Vector<int> new_e(e_quantity, 0);
                edges.push(new_e);
                for (size_t i = 0; i < edges.size(); i++) {
                    while (edges[i].size() != e_quantity)
                        edges[i].push(0);
                }
            }
        }
    }

    void delete_vertex(Data a) {
        int a_num = number_by_mark(a);
        if (a_num != -1) {
            for (size_t i = a_num; i < v_quantity - 1; i++) {
                vertex[i] = vertex[i + 1];
                for (size_t j = 0; j < v_quantity; j++) {
                    relations[i][j] = relations[i + 1][j];
                }
            }
            v_quantity--;

            relations.resize(v_quantity);
            for (size_t i = 0; i < v_quantity; i++) {
                relations[i].resize(v_quantity);
            }

            if (a_num < (int)edges.size()) {
                for (size_t i = a_num; i < e_quantity; i++) {
                    for (size_t j = 0; j < e_quantity; j++) {
                        edges[i][j] = edges[i + 1][j];
                    }
                }
                e_quantity--;
            }
        }
    }

    void add_edge(Data a, Data b, int edge_mark) {
        int a_num = number_by_mark(a);
        int b_num = number_by_mark(b);
        if (a_num != -1 && b_num != -1) {
            relations[a_num][b_num] = 1;

            e_quantity++;         
            for (size_t i = 0; edges.size() != v_quantity; i++) {
                Vector<int> temp(1, 0);
                edges.push(temp);
            }

            for (size_t i = 0; i < edges.size(); i++) {
                while (edges[i].size() != e_quantity) {
                    edges[i].push(0);
                }
            }
            edges[a_num][edges[0].size() - 1] = edge_mark;
            edges[b_num][edges[0].size() - 1] = (-1) * edge_mark;
        }
    }

    void add_edge(size_t a, size_t b, int edge_mark) {
        if (a < v_quantity && b < v_quantity) {          
            relations[a][b] = 1;

            e_quantity++;
            for (size_t i = 0; edges.size() != v_quantity; i++) {
                Vector<int> temp(1, 0);
                edges.push(temp);
            }

            for (size_t i = 0; i < edges.size(); i++) {
                while (edges[i].size() != e_quantity) {
                    edges[i].push(0);
                }
            }
            edges[a][edges[0].size() - 1] = edge_mark;
            edges[b][edges[0].size() - 1] = (-1) * edge_mark;
        }
    }

    void delete_edge(Data a, Data b) {
        int a_num = number_by_mark(a);
        int b_num = number_by_mark(b);
        if (a_num != -1 && b_num != -1) {
            relations[a_num][b_num] = 0;
        }

        int index = edge_index(a, b);
        if (index != -1) {
            e_quantity--;
            for (size_t i = 0; i < edges.size(); i++) {
                for (size_t j = index; j < edges[i].size() - 1; j++) {
                    edges[i][j] = edges[i][j + 1];
                }
            }

            for (size_t i = 0; i < edges.size(); i++) {
                edges[i].resize(e_quantity);
            }
        }
    }

    size_t edge_index(Data a, Data b) {
        int a_num = number_by_mark(a);
        int b_num = number_by_mark(b);
        if (a_num != -1 && b_num != -1) {
            for (size_t i = 0; i < edges[a_num].size(); i++) {
                if (edges[a_num][i] != 0 && edges[b_num][i] != 0)
                    return i;
            }
        }
        return -1;
    }

    bool is_bounded(Data a, Data b) {
        int a_num = number_by_mark(a);
        int b_num = number_by_mark(b);
        if (a_num != -1 && b_num != -1) {
            if (relations[a_num][b_num] == 1)
                return true;
        }
        return false;
    }

    void add_mark(size_t a, Data mark) {
        if (!mark_exist(mark)) {
            vertex[a].mark = mark;
        }
    }

    Vector<Vector<bool>> get_matrix() {
        return relations;
    }

    Vector<Data> get_marks() {
        Vector<Data> marks;
        for (size_t i = 0; i < v_quantity; i++) {
            marks.push(vertex[i].mark);
        }
        return marks;
    }

    Vector<Vector<int>> get_edges() {
        return edges;
    }

    size_t number_by_mark(Data mark) {
        for (size_t i = 0; i < vertex.size(); i++) {
            if (vertex[i].mark == mark)
                return vertex[i].number;
        }
        return -1;
    }

    Vertex<Data> get_vertex_by_index(size_t index) {
        return vertex[index];
    }

    class Iterator {
    public:
        Iterator(Graph<Data>* graph, Data v_mark, size_t neib)
            : graph(graph), mark(v_mark), neib_index(neib) {}

        Iterator& operator++() {
            Vector<bool> v_neib = graph->get_matrix()[graph->number_by_mark(mark)];
            for (size_t i = neib_index + 1; i < v_neib.size(); i++) {
                if (v_neib[i]) {
                    neib_index = i;
                    return *this;
                }
            }
            neib_index = v_neib.size();
            return *this;
        }

        bool operator!=(const Iterator& iterator) const {
            return neib_index != iterator.neib_index;
        }

        Vertex<Data> operator*() const {
            return graph->get_vertex_by_index(neib_index);
        }

    private:
        Graph<Data>* graph;
        Data mark;
        size_t neib_index;
    };

    Iterator begin(Data mark) {
        size_t v_num = number_by_mark(mark);
        size_t first_neib = 0;
        for (size_t i = 0; i < relations[v_num].size() && !first_neib; i++) {
            if (relations[v_num][i] == 1)
                first_neib = i;
        }

        return Iterator(this, mark, first_neib);
    }

    Iterator end(Data mark) {
        size_t v_num = number_by_mark(mark);
        return Iterator(this, mark, relations[v_num].size());
    }

private:
    bool mark_exist(Data mark) {
        for (size_t i = 0; i < vertex.size(); i++) {
            if (vertex[i].mark == mark)
                return true;
        }
        return false;
    }

    size_t v_quantity = 0;
    size_t e_quantity = 0;
    Vector<Vector<int>> edges;
    Vector<Vertex<Data>> vertex;
    Vector<Vector<bool>> relations;
};

#endif