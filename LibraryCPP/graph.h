#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "array.h"

template <typename Data>
class DirectedGraph {
public:
    struct Vertex {
        Data data;
        Vertex() {
            this->data = 0;
        }
        Vertex(Data data) {
            this->data = data;
        }
    };

    struct Edge {
        size_t cost;
        Edge() {
            cost = 0;
        }
        Edge(size_t cost) {
            this->cost = cost;
        }
    };
}

#endif