#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

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
        vertex.push({ vertex.size(), vertex_mark });

        v_quantity++;
        Vector<bool> new_v(v_quantity, 0);
        relations.push(new_v);

        for (size_t i = 0; i < relations.size(); i++) {
            while(relations[i].size() != v_quantity)
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

            for (size_t i = a_num; i < e_quantity - 1; i++) {
                for (size_t j = 0; j < e_quantity; j++) {
                    edges[i][j] = edges[i + 1][j];
                }
            }
            e_quantity--;

            edges.resize(e_quantity);
            for (size_t i = 0; i < e_quantity; i++) {
                edges[i].resize(e_quantity);
            }
        }
    }

    void add_edge(Data a, Data b, int edge_mark) {
        int a_num = number_by_mark(a);
        int b_num = number_by_mark(b);
        if (a_num != -1 && b_num != -1) {
            relations[a_num][b_num] = 1;

            e_quantity++;
            while (edges.size() != v_quantity) {
                Vector<int> temp(1, 0);
                edges.push(temp);
            }
            edges[a_num][edges[0].size() - 1] = edge_mark;
            edges[b_num][edges[0].size() - 1] = (-1) * edge_mark;
        }
    }

    void add_edge(size_t a, size_t b, int edge_mark) {
        if (a < v_quantity && b < v_quantity) {
            relations[a][b] = 1;
            for (size_t i = 0; i < edges.size(); i++) {
                edges[i].push(0);
            }
            edges[a][edges.size() - 1] = edge_mark;
            edges[b][edges.size() - 1] = (-1) * edge_mark;
        }
    }

    void delete_edge(Data a, Data b) {
        int a_num = number_by_mark(a);
        int b_num = number_by_mark(b);
        if (a_num != -1 && b_num != -1) {
            relations[a_num][b_num] = 0;
        }
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
        bool exist = false;
        for (size_t i = 0; i < vertex.size(); i++)
            if (vertex[i].mark == mark)
                exist = true;

        if(!exist)
            vertex[a].mark = mark;
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

private:
    uint v_quantity = 0;
    uint e_quantity = 0;
    Vector<Vector<int>> edges;
    Vector<Vertex<Data>> vertex;
    Vector<Vector<bool>> relations;
};

#endif
