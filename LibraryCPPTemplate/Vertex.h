#ifndef VERTEX_H
#define VERTEX_H

typedef unsigned int uint;

template <typename Data>
struct Vertex {
    size_t number = 0;
    Data mark = Data();
};

#endif