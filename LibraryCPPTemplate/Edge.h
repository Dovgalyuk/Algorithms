#pragma once

template <typename E_type>
struct Edge {
    Edge(size_t a, size_t b, E_type edge_mark) {
        start = a;
        destination = b;
        mark = edge_mark;
    }

    size_t start = 0;
    size_t destination = 0;
    E_type mark = E_type();
};