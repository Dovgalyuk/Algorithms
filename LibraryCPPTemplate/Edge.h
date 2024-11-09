#pragma once

template <typename E_type>
struct Edge {

    Edge() {}
    Edge(size_t a, size_t b, E_type edge_mark) : start(a), destination(b), mark(mark) {}

    size_t start = std::numeric_limits<size_t>::max();
    size_t destination = std::numeric_limits<size_t>::max();
    E_type mark = E_type();
};