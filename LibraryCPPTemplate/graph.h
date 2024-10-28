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
        vertex.push({ vertex.size() + 1, Data() });

        quantity++;
        Vector<bool> new_v(quantity, 0);
        relations.push(new_v);

        for (size_t i = 0; i < relations.size(); i++) {
            while (relations[i].size() != quantity)
                relations[i].push(0);
        }
    }

    void add_vertex(Data vertex_mark) {
        Vertex<Data> new_vertex = { vertex.size() + 1, vertex_mark };
        vertex.push(new_vertex);

        quantity++;
        Vector<bool> new_v(quantity, 0);
        relations.push(new_v);

        for (size_t i = 0; i < relations.size(); i++) {
            while(relations[i].size() != quantity)
                relations[i].push(0);
        }
    }

    void delete_vertex(Data a) {
        int a_num = number_by_mark(a);
        if (a_num != -1) {
            for (size_t i = a_num; i < quantity - 1; i++) {
                vertex[i] = vertex[i + 1];
                for (size_t j = 0; j < quantity; j++) {
                    relations[i][j] = relations[i + 1][j];
                }
            }
            quantity--;

            relations.resize(quantity);
            for (size_t i = 0; i < quantity; i++) {
                relations[i].resize(quantity);
            }
        }
    }

    void add_edge(Data a, Data b) {
        int a_num = number_by_mark(a);
        int b_num = number_by_mark(b);
        if (a_num != -1 && b_num != -1) {
                relations[a_num][b_num] = 1;
        }
    }

    void add_edge(size_t a, size_t b) {
        if (a < quantity && b < quantity) {
            relations[a][b] = 1;
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

    Vector<Data> get_marks() {
        Vector<Data> marks;
        for (size_t i = 0; i < quantity; i++) {
            marks.push(vertex[i].mark);
        }
        return marks;
    }

    Vector<Vector<bool>> get_matrix() {
        return relations;
    }

private:
    size_t number_by_mark(Data mark) {
        for (size_t i = 0; i < vertex.size(); i++) {
            if (vertex[i].mark == mark)
                return vertex[i].number;
        }
        return -1;
    }

    Vector<Vector<bool>> relations;
    Vector<Vertex<Data>> vertex;
    uint quantity = 0;
};

#endif
