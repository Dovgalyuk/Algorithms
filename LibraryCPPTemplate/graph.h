#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

template <typename Data>
class Graph {
public:
    Graph() {}

    ~Graph() {}

    void add_vertex() {
        vertex.push({ vertex.size() + 1, Data() });

        quantity++;
        Vector<int> new_v(quantity, 0);
        relations.push(new_v);

        for (size_t i = 0; i < relations.size(); i++) {
            while (relations[i].size() != quantity)
                relations[i].push(0);
        }
    }

    void add_vertex(Vertex<Data> vertex_v) {
        vertex.push(vertex_v);

        quantity++;
        Vector<int> new_v(quantity, 0);
        relations.push(new_v);

        for (size_t i = 0; i < relations.size(); i++) {
            while(relations[i].size() != quantity)
                relations[i].push(0);
        }
    }

    void add_edge(Data a, Data b) {

        if (a.mark < quantity && b.mark < quantity) {
            relations[a.mark][b.mark] = 1;
            a.degree++;
        }
    }

    void delete_vertex(Data a) {
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

    void delete_edge(Data a, Data b) {
        if (a.mark < quantity && b.mark < quantity) {
            relations[a.mark][b.mark] = 0;
        }
    }

    bool is_bounded(Data a, Data b) {
        if (a.mark < quantity && b.mark < quantity) {
            if (relations[a.mark][b.mark] == 1)
                return true;
        }
        return false;
    }

    void add_mark(uint a, Data mark) {
        if (a.mark < quantity) {
            vertex[a.mark].mark = mark;
        }
    }

    Vector<Data> get_marks() {
        Vector<Data> marks;
        for (size_t i = 0; i < quantity; i++) {
            marks.push(vertex[i].mark);
        }
        return marks;
    }

    void print_matrix() {
        for (size_t i = 0; i < relations.size(); i++) {
            for (size_t j = 0; j < relations[i].size(); j++) {
                std::cout << relations[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    size_t number_by_mark(Data mark) {
        for (size_t i = 0; i < vertex.size(); i++) {
            if (vertex[i].mark == mark)
                return vertex[i].number;
        }
        return -1;
    }

    Vector<Vector<int>> relations;
    Vector<Vertex<Data>> vertex;
    uint quantity = 0;
};

#endif
