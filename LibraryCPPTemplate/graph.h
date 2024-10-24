#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

template <typename Data>
class Graph {
public:
    Graph() {}

    ~Graph() {}

    void add_vertex(uint mark) {
        Vertex vertex_v = { quantity, mark };
        vertex.push(vertex_v);

        for (size_t i = 0; i < relations.size(); i++) {
            relations[i].push(0);
        }

        Vector<int> new_v(quantity + 1);
        relations.push(new_v);
        quantity++;
    }

    void add_edge(Vertex a, Vertex b) {
        if (a.mark < quantity && b.mark < quantity) {
            relations[a.mark][b.mark] = 1;
        }
    }

    void delete_vertex(Vertex a) {
        if (a.mark < quantity) {
            for (size_t i = a.mark; i < quantity - 1; i++) {
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

    void delete_edge(Vertex a, Vertex b) {
        if (a.mark < quantity && b.mark < quantity) {
            relations[a.mark][b.mark] = 0;
        }
    }

    bool is_bounded(Vertex a, Vertex b) {
        if (a.mark < quantity && b.mark < quantity) {
            return relations[a.mark][b.mark] == 1;
        }
        return false;
    }

    void add_mark(Vertex a, uint mark) {
        if (a.mark < quantity) {
            vertex[a.mark].mark = mark;
        }
    }

    Vector<int> get_marks() {
        Vector<int> marks;
        for (size_t i = 0; i < quantity; i++) {
            marks.push(vertex[i].mark);
        }
        return marks;
    }

private:
    Vector<Vector<int>> relations;
    Vector<Vertex> vertex;
    uint quantity = 0;
};

#endif
